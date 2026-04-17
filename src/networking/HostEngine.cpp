#include "checkersMate/networking/HostEngine.h"

#include <sys/epoll.h>
#include <future>
#include <iostream>


Int HostEngine::listenAndAccept() {
    NetworkListener server{};
    server.fetchInterfacesToBind(PORT, m_ipVersion, SOCK_STREAM);
    L4Socket listeningSocket {server, true};
    listeningSocket.setSocketAsNonBlock();
    listeningSocket.makeSocketListen(LISTENING_BACKLOG_SIZE);

    // Accepting for ACCEPTING_TIMEOUT millisecs
    Int epollFD = epoll_create1(0);
    if (epollFD == -1) {
        throw EpollCreationException();
    }
    try {
        epoll_event ev {};
        ev.events = EPOLLIN;
        ev.data.fd = listeningSocket.m_socket;
        Int result = epoll_ctl(epollFD, EPOLL_CTL_ADD, listeningSocket.m_socket, &ev);
        if (result == -1) {
            throw EpollControllerException(EPOLL_CTL_ADD);
        }
        while (true) {
            result = epoll_wait(epollFD, &ev, 1,ACCEPTING_TIMEOUT);
            if (result == -1) {
                throw EpollWaitException();
            } else if (result == 0) {
                //timeout
                close(epollFD);
                throw NoConnectionsToAcceptTimeoutException(m_hostname, ACCEPTING_TIMEOUT);
            }
            if (ev.data.fd == listeningSocket.m_socket && ev.events & EPOLLIN) {
                sockaddr_storage clientAddress {};
                socklen_t sizeClientAddress = sizeof(clientAddress);
                Int connectedSocket = accept(listeningSocket.m_socket, reinterpret_cast<sockaddr*>(&clientAddress), &sizeClientAddress);
                if (errno == EAGAIN || errno == EWOULDBLOCK) {
                    continue; // Kernel removed message for some reason e.g corruption
                }
                std::string ipNameBuffer {""};
                if (reinterpret_cast<sockaddr*>(&clientAddress)->sa_family == AF_INET) {
                    inet_ntop(AF_INET, &reinterpret_cast<sockaddr_in*>(&clientAddress)->sin_addr, ipNameBuffer.data(), sizeof(struct sockaddr_in));
                } else {
                    inet_ntop(AF_INET6, &reinterpret_cast<sockaddr_in6*>(&clientAddress)->sin6_addr, ipNameBuffer.data(), sizeof(struct sockaddr_in6));
                }
                if (connectedSocket == -1) {
                    throw ServerAcceptingException(ipNameBuffer);
                } else if (ipNameBuffer == m_hostname) {
                    return connectedSocket; //return connected socket
                }
            }
        }
    } catch (std::runtime_error& e) {
        close(epollFD);
        std::cerr << e.what() << '\n';
    }
}
