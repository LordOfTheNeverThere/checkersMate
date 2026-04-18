#ifndef CHECKERSMATE_CONNECTOR_H
#define CHECKERSMATE_CONNECTOR_H
#include "Engine.h"
#include "socks/L4Socket.h"
#define LISTENING_BACKLOG_SIZE 10
#define ACCEPTING_TIMEOUT 30000
class HostEngine : public Engine {
    void createAndBindSocket(Socket &listeningSocket);
    std::string getIPAddrressFromConnection(sockaddr_storage clientAddress);

public:
    // binds a socket to a port on localhost, no connection is done!
    HostEngine(const std::string& hostname, const Int ipVersion = AF_INET)
    : Engine(hostname, ipVersion){}
    HostEngine() = delete;
    // Retrieves connecting socket by accepting it, accepting is non-blocking and used epoll
    bool bindListenAndAccept(const Int acceptTimeoutMillis = ACCEPTING_TIMEOUT);
};

class NoConnectionsToAcceptTimeoutException : public std::runtime_error {
public:
    NoConnectionsToAcceptTimeoutException(const std::string& hostname, const Int timeInMS) : std::runtime_error("No connection from " + hostname + "\nWaited for " + std::to_string(timeInMS) + " ms") {}

};

#endif //CHECKERSMATE_CONNECTOR_H