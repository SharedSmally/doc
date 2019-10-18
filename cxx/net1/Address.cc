#include <Address.h>
#include <string.h>

IPv4Address::IPv4Address(uint16_t p)
{
    _init();
    addr_.sin_addr.s_addr = INADDR_ANY;
    port(p);
}
IPv4Address::IPv4Address(struct sockaddr_in && addr)
    : addr_(std::move(addr))
{
}

IPv4Address::IPv4Address(const struct sockaddr_in & addr)
{
    memcpy(&addr_, &addr, sizeof(addr_));
}
IPv4Address::IPv4Address(const IPv4Address & addr)
{
    memcpy(&addr_, &addr.addr_, sizeof(addr_));
}
IPv4Address::IPv4Address(IPv4Address && addr)
    : addr_(std::move(addr.addr_))
{
}

IPv4Address::IPv4Address(uint32_t i, uint16_t p)
{
    _init();
    ip(i);
    port(p);
}
IPv4Address::IPv4Address(const std::string & i, uint16_t p)
{
    _init();
    ip(i);
    port(p);
}

void IPv4Address::_init()
{
    ::memset(&addr_, '\0', sizeof(addr_));
    addr_.sin_family = AF_INET;
}

bool IPv4Address::ip(const std::string & p)
{
    return inet_aton(p.c_str(), &addr_.sin_addr);
}

std::string IPv4Address::ip() const
{
    char ip4[INET_ADDRSTRLEN];  // space to hold the IPv4 string
    inet_ntop(AF_INET, &(addr_.sin_addr), ip4, INET_ADDRSTRLEN);
    return std::string(ip4);
    //return std::string(inet_ntoa(addr_.sin_addr));
}

void IPv4Address::output(std::ostream & out) const
{
    char ip4[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &(addr_.sin_addr), ip4, INET_ADDRSTRLEN);
    out << ip4 << ":" << port();
}
