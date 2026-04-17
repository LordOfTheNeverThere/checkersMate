#ifndef CHECKERSMATE_ENGINE_H
#define CHECKERSMATE_ENGINE_H
#include <string>
#include <bits/socket.h>
#include "socks/types.h"

#define PORT "63777"
class Engine {
public:
    std::string m_hostname {"localhost"};
    Int m_ipVersion {AF_INET};

    Engine(const std::string& hostname, const Int ipVersion = AF_INET)
    : m_hostname(hostname),
      m_ipVersion(ipVersion){}
    Engine() = delete;

};
#endif //CHECKERSMATE_ENGINE_H