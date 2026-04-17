#include "checkersMate/networking/GuestEngine.h"
#include <bits/this_thread_sleep.h>
#include "socks/L4Socket.h"
#include "socks/NetworkListener.h"


Int GuestEngine::connectToGameHost(Int timeToRetryMillis) {
    Int timeToSleepPerCycle {500};
    NetworkListener client {};
    client.fetchInterfacesToConnect(m_hostname, PORT, m_ipVersion);
    while (timeToRetryMillis > 0) {
        try {
            L4Socket clientSocket {client, false};
            return  clientSocket.m_socket; // If it reaches this position without throwing anything we have reached the host and connected to it
        } catch (std::runtime_error&) {}
        std::this_thread::sleep_for(std::chrono::milliseconds(timeToSleepPerCycle));
        timeToRetryMillis = timeToRetryMillis - timeToSleepPerCycle;
    }
}
