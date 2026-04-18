#ifndef CHECKERSMATE_ENGINE_H
#define CHECKERSMATE_ENGINE_H
#include <string>
#include <sys/socket.h>

#include "socks/Socket.h"
#include "socks/Tools.h"
#include "socks/types.h"

#define PORT "63777"
class Engine {
public:
    std::string m_hostname {"127.0.0.1"};
    Int m_ipVersion {AF_INET};
    std::unique_ptr<Socket> m_socketPtr {};

    Engine(const std::string& hostname, const Int ipVersion = AF_INET)
    : m_ipVersion(ipVersion) {
    if (hostname != "localhost") {
        if ((ipVersion == AF_INET && Tools::isValidIPv4(hostname)) || (ipVersion == AF_INET6 && Tools::isValidIPv6(hostname))) {
        m_hostname = hostname;
        } else {
            throw ConversionToIPBinaryException(hostname);
        }
    }
    }
    Engine() = delete;

};
#endif //CHECKERSMATE_ENGINE_H