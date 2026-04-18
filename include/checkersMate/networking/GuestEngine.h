#ifndef CHECKERSMATE_GUESTENGINE_H
#define CHECKERSMATE_GUESTENGINE_H
#include <stdexcept>

#include "Engine.h"
#include "socks/Exceptions.h"

#define CONNECTION_TIMEOUT_SECONDS 15
#define RETRIES 3
#define RETRY_WAIT_MS 500

class GuestEngine : public Engine{

    void createSocketAndConnect(Int timeoutSecs);
public:
    GuestEngine(const std::string& hostname, const Int ipVersion = AF_INET) : Engine(hostname, ipVersion){}
    GuestEngine() = delete;


    // Returns socket after connecting to the host
        // tries multiple times to connect to the host
    bool connectToGameHost(Int timeoutSecs = CONNECTION_TIMEOUT_SECONDS, Int retries = RETRIES);

};

class ConnectionTimeoutException : public SystemCallException {
public:
    ConnectionTimeoutException() : SystemCallException( "The connection to the host player timed-out.") {}
};

#endif //CHECKERSMATE_GUESTENGINE_H