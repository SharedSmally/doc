#include "Address.h"

#include <sstream>

#include <utility>

#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>

const IPv4Address IPv4Address::ANY_ADDR(INADDR_ANY); //0.0.0.0
const IPv4Address IPv4Address::BROADCAST_ADDR(INADDR_BROADCAST); //256.256.256.256
const IPv4Address IPv4Address::LOOPBACK_ADDR(INADDR_LOOPBACK );  //127.0.0.1
const IPv4Address IPv4Address::GROUP_ADDR(INADDR_UNSPEC_GROUP);  //224.0.0.0
const IPv4Address IPv4Address::ALLHOSTS_GROUP_ADDR(INADDR_ALLHOSTS_GROUP); //224.0.0.1
const IPv4Address IPv4Address::ALLRTRS_GROUP_ADDR(INADDR_ALLRTRS_GROUP);   //224.0.0.2
const IPv4Address IPv4Address::LOCAL_GROUP_ADDR(INADDR_MAX_LOCAL_GROUP);   //224.0.0.255

const IPv4Address IPv4Address::CLASSA_NET_ADDR(IN_CLASSA_NET); //0xff000000
const IPv4Address IPv4Address::CLASSB_NET_ADDR(IN_CLASSB_NET); //0xffff0000
const IPv4Address IPv4Address::CLASSC_NET_ADDR(IN_CLASSC_NET); //0xffffff00
//const IPv4Address IPv4Address::CLASSD_NET_ADDR(IN_CLASSD_NET);

IPv4Address::IPv4Address(uint16_t port)
{
	_init();
	addr_.sin_port = htons(port);
	addr_.sin_addr.s_addr = INADDR_ANY;
}
IPv4Address::IPv4Address(uint32_t ip, uint16_t port)
{
	_init();
	addr_.sin_port = htons(port);
	addr_.sin_addr.s_addr = htonl(ip);
}
IPv4Address::IPv4Address(const std::string & ip, uint16_t port)
{
	_init();
	addr_.sin_port = htons(port);
	int ret = inet_pton(AF_INET, ip.c_str(), &(addr_.sin_addr));
	// 1 for success
}
IPv4Address::IPv4Address(IPv4Address && addr)
{
	addr_ = std::move(addr.addr_);
}
IPv4Address::IPv4Address(const IPv4Address & addr)
{
	memcpy(&addr_, &addr.addr_, sizeof(addr_));
}

void IPv4Address::_init()
{
    memset(&addr_, '\0', sizeof(addr_));
	addr_.sin_family = AF_INET;
}

std::string IPv4Address::toString() const
{
	std::ostringstream oss;
	oss << getIP() << ":" << getPort();
	return oss.str();
}

std::string IPv4Address::getIP() const
{
	char ip4[INET_ADDRSTRLEN]; //16
	inet_ntop(AF_INET, &(addr_.sin_addr), ip4, INET_ADDRSTRLEN);
	return std::string(ip4);
}
bool IPv4Address::setIP(const std::string & ip)
{
	return 1 == inet_pton(AF_INET, ip.c_str(), &addr_.sin_addr);
}

NetworkClass IPv4Address::networkClass() const
{
	if (IN_CLASSA(getIPInt())) return NetworkClass::CLASS_A;
	if (IN_CLASSB(getIPInt())) return NetworkClass::CLASS_B;
	if (IN_CLASSC(getIPInt())) return NetworkClass::CLASS_C;
	if (IN_CLASSD(getIPInt())) return NetworkClass::CLASS_D;
}

bool IPv4Address::isMulticast() const
{
    return IN_MULTICAST(getIPInt());
}
bool IPv4Address::isExperimental() const
{
    return IN_EXPERIMENTAL(getIPInt());
}

int IPv4Address::getByName(const std::string & name)
{
    struct addrinfo hints;
    hints.ai_family = AF_INET;
    hints.ai_socktype = 0;
    hints.ai_protocol = 0;
    hints.ai_flags = 0;

    struct addrinfo *host(nullptr);
    int err = getaddrinfo(name.c_str(), 0, &hints, &host);

    if(err == 0)
    {
        if((host->ai_family == AF_INET) && (host->ai_addrlen == sizeof(sockaddr_in)))
        {
        	addr_ = *(reinterpret_cast< sockaddr_in* >(host->ai_addr));
        }
        else
        {
            err = -1; // no such hostname
        }

        freeaddrinfo(host);
    }

    return err;
}
