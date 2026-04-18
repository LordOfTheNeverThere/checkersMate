#include "checkersMate/networking/HostEngine.h"

#include <sys/epoll.h>
#include <iostream>
#include <string>



void HostEngine::createAndBindSocket(Socket& listeningSocket) {
    NetworkListener server{};
    server.fetchInterfacesToBind(PORT, m_ipVersion, SOCK_STREAM);
    for (AddressInfo &interface: server.getInterfaces()) {
        Socket tempSocket {socket(interface.family, interface.socketType, interface.protocol)};
        if (tempSocket.m_socket == -1) {
            perror("Got an error while creating a socket");
            continue;
        }
        tempSocket.setSocketAsNonBlock();
        Int yes = 1;
        Int setSocketOption = setsockopt(tempSocket.m_socket, SOL_SOCKET, SO_REUSEADDR, &yes,sizeof(Int));
        // Allows usage of ports and addresses in less than 2 mins after their closure.
        if ( setSocketOption == -1) {
            exit(1);
        }
        Int binding = bind(tempSocket.m_socket, reinterpret_cast<sockaddr*>(&interface.addr), interface.ipLength);
        if (binding == -1) {
           tempSocket.closeSocket();
            continue;
        }
        listeningSocket = std::move(tempSocket);
        return;// all system calls were successful
    }
    throw BindingFailedException();
}

bool HostEngine::bindListenAndAccept(const Int acceptTimeoutMillis) {

    Int epollFD = epoll_create1(0);
    try {
        Socket listeningSocket {};
        createAndBindSocket(listeningSocket);
        Int listening = listen(listeningSocket.m_socket, LISTENING_BACKLOG_SIZE);
        if (listening == -1) {
            throw ServerListeningException();
        }

        if (epollFD == -1) {
            throw EpollCreationException();
        }
        // Accepting for ACCEPTING_TIMEOUT millisecs
        epoll_event ev {};
        ev.events = EPOLLIN;
        ev.data.fd = listeningSocket.m_socket;
        Int result = epoll_ctl(epollFD, EPOLL_CTL_ADD, listeningSocket.m_socket, &ev);
        if (result == -1) {
            throw EpollControllerException(EPOLL_CTL_ADD);
        }
        while (true) {
            result = epoll_wait(epollFD, &ev, 1,acceptTimeoutMillis);
            if (result == -1) {
                throw EpollWaitException();
            } else if (result == 0) {
                //timeout
                throw NoConnectionsToAcceptTimeoutException(m_hostname, acceptTimeoutMillis);
            }
            if (ev.data.fd == listeningSocket.m_socket && ev.events & EPOLLIN) {
                sockaddr_storage clientAddress {};
                socklen_t sizeClientAddress = sizeof(clientAddress);
                Socket connectedSocket = {accept(listeningSocket.m_socket, reinterpret_cast<sockaddr*>(&clientAddress), &sizeClientAddress)};
                if (errno == EAGAIN || errno == EWOULDBLOCK) {
                    continue; // Kernel removed message for some reason e.g corruption
                }

                std::string externalIPString = Tools::getIPAddrressFromConnection(clientAddress);
                if (connectedSocket.m_socket == -1) {
                    throw ServerAcceptingException(externalIPString);
                } else if (externalIPString == m_hostname) {
                    m_socketPtr = std::make_unique<Socket>(std::move(connectedSocket));
                    return true; // No need to wait for more connections, we only need one
                }
                //connected socket goes out of scope - resource deleted
            }
        }
    } catch (std::runtime_error& e) {
        close(epollFD);
        std::cerr << e.what() << '\n';
    }
    return false;
}
