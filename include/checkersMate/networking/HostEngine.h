#ifndef CHECKERSMATE_CONNECTOR_H
#define CHECKERSMATE_CONNECTOR_H
#include "Engine.h"
#include "socks/L4Socket.h"
#define LISTENING_BACKLOG_SIZE 10
#define ACCEPTING_TIMEOUT 30000
class HostEngine : public Engine {
public:
    // binds a socket to a port on localhost, no connection is done!
    HostEngine(const std::string& hostname, const Int ipVersion = AF_INET)
    : Engine(hostname, ipVersion){}
    HostEngine() = delete;

    // Retrieves connecting socket by accepting it, accepting is non-blocking and used epoll
    Int listenAndAccept();
};

class NoConnectionsToAcceptTimeoutException : public std::runtime_error {
public:
    NoConnectionsToAcceptTimeoutException(const std::string& hostname, const Int timeInMS) : std::runtime_error("No connection from " + hostname + "\nWaited for " + std::to_string(timeInMS) + " ms\n") {}

};

#endif //CHECKERSMATE_CONNECTOR_H