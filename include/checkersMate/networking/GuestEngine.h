#ifndef CHECKERSMATE_GUESTENGINE_H
#define CHECKERSMATE_GUESTENGINE_H
#include "Engine.h"

#define TIME_TO_RETRY_MS 30000

class GuestEngine : public Engine{
public:
    GuestEngine(const std::string& hostname, const Int ipVersion = AF_INET) : Engine(hostname, ipVersion){}
    GuestEngine() = delete;

    // Returns socket after connecting to the host
        // tries multiple times to connect to the host
    Int connectToGameHost(Int timeToRetryMillis = TIME_TO_RETRY_MS);

};

#endif //CHECKERSMATE_GUESTENGINE_H