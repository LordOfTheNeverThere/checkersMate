#include "checkersMate/networking/GuestEngine.h"

#include <bits/this_thread_sleep.h>

#include "socks/L4Socket.h"
#include "socks/NetworkListener.h"


void GuestEngine::createSocketAndConnect(Int timeoutSecs) {
    NetworkListener client {};
    client.fetchInterfacesToConnect(m_hostname, PORT, m_ipVersion, SOCK_STREAM);
    for (AddressInfo &interface: client.getInterfaces()) {
        Socket tempSocket {socket(interface.family, interface.socketType, interface.protocol)};
        if (tempSocket.m_socket == -1) {
            perror("Got an error while creating a socket");
            continue;
        }
        if (interface.socketType == SOCK_STREAM && timeoutSecs != 0) {
            timeval timeout {};
            timeout.tv_sec = timeoutSecs;
            tempSocket.setSocketSendTimeoutValue(timeout);
        }
        Int connecting = connect(tempSocket.m_socket, reinterpret_cast<sockaddr*>(&interface.addr), interface.ipLength);
        if (connecting == -1) {
            tempSocket.closeSocket();
            continue;
        }
        m_socketPtr = std::make_unique<Socket>(std::move(tempSocket));
        return;// all system calls were sucessful
    }
    throw ConnectionFailedException();
}

bool GuestEngine::connectToGameHost(Int timeoutSecs, Int retries) {
    try {
        createSocketAndConnect(timeoutSecs);
     } catch (std::runtime_error& e) {
        if (retries == 1) {
            std::cerr << "Connection to " << m_hostname << " failed after "<< RETRIES << " retries." << '\n';
        } else {
            std::this_thread::sleep_for(std::chrono::milliseconds(RETRY_WAIT_MS));
            return connectToGameHost(timeoutSecs, retries - 1);
        }
    }
    return m_socketPtr.get();
}
