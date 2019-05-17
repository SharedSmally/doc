#include "Address.h"

#include <utility>

#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>

void Address::_init()
{
	memset(&addr(), '\0', addrlen());
}

IpAddress::IpAddress(uint16_t port, bool v4)
    : v4_(v4)
{
    _init();
    if (v4) {
    	struct sockaddr_in * addr4 = (struct sockaddr_in *)(&addr_);
    	addr4->sin_family = AF_INET;
    	addr4->sin_port = htons(port);
    	addr4->sin_addr.s_addr = INADDR_ANY;
    } else {
    	struct sockaddr_in6 * addr6 = (struct sockaddr_in6 *)(&addr_);
    	addr6->sin6_family = AF_INET6;
    	addr6->sin6_port = htons(port);
    	addr6->sin6_addr = in6addr_any;
    }
}
IpAddress::IpAddress(const std::string & ip, uint16_t port)
    : v4_(false)
{
	struct sockaddr_in6 * addr6 = (struct sockaddr_in6 *)(&addr_);
	int ret = inet_pton(AF_INET6, ip.c_str(), &(addr6->sin6_addr));

	if (ret==1) {
		addr6->sin6_family = AF_INET6;
		addr6->sin6_port = htons(port);
		return;
	}

	struct sockaddr_in * addr4 = (struct sockaddr_in *)(&addr_);
	ret = inet_pton(AF_INET, ip.c_str(), &(addr4->sin_addr));
	if (ret==1) {
		addr4->sin_family = AF_INET;
		addr4->sin_port = htons(port);
		return;
	}
	// failure
}
IpAddress::IpAddress(IpAddress && addr)
{
	addr_ = std::move(addr.addr_);
}
IpAddress::IpAddress(const IpAddress & addr)
{
	memcpy(&addr_, &addr.addr_, sizeof(addr_));
}

const std::string IpAddress::toString()
{
	if (v4_)
	{
		struct sockaddr_in * addr4 = (struct sockaddr_in *)(&addr_);
		char ip4[INET_ADDRSTRLEN];
		inet_ntop(AF_INET, &(addr4->sin_addr), ip4, INET_ADDRSTRLEN);
		return std::string(ip4);
	}
	else
	{
		char ip6[INET6_ADDRSTRLEN];
		struct sockaddr_in6 * addr6 = (struct sockaddr_in6 *)(&addr_);
		inet_ntop(AF_INET6, &(addr6->sin6_addr), ip6, INET6_ADDRSTRLEN);
		return std::string(ip6);
	}
}

/////////////////////////////////////////////////////
Ipv4Address::Ipv4Address(uint16_t port)
{
	_init();
	addr_.sin_family = AF_INET;
	addr_.sin_port = htons(port);
	addr_.sin_addr.s_addr = INADDR_ANY;
}
Ipv4Address::Ipv4Address(const std::string & ip, uint16_t port)
{
	_init();
	addr_.sin_family = AF_INET;
	addr_.sin_port = htons(port);
	inet_pton(AF_INET, ip.c_str(), &addr_.sin_addr);
}
Ipv4Address::Ipv4Address(Ipv4Address && addr)
{
	addr_ = std::move(addr.addr_);
}
Ipv4Address::Ipv4Address(const Ipv4Address & addr)
{
	memcpy(&addr_, &addr.addr_, sizeof(addr_));
}
const std::string Ipv4Address::toString()
{
	char ip4[INET_ADDRSTRLEN];
	inet_ntop(AF_INET, &(addr_.sin_addr), ip4, INET_ADDRSTRLEN);
	return std::string(ip4);
}

/////////////////////////////////////////////////////
Ipv6Address::Ipv6Address(uint16_t port)
{
	addr_.sin6_family = AF_INET6;
	addr_.sin6_port = htons(port);
	addr_.sin6_addr = in6addr_any;
}
Ipv6Address::Ipv6Address(const std::string & ip, uint16_t port)
{
	addr_.sin6_family = AF_INET6;
	addr_.sin6_port = htons(port);
	int ret = inet_pton(AF_INET6, ip.c_str(), &addr_.sin6_addr);
	//ret==1: successful;
}
Ipv6Address::Ipv6Address(Ipv6Address && addr)
{
	addr_ = std::move(addr.addr_);
}
Ipv6Address::Ipv6Address(const Ipv6Address & addr)
{
	memcpy(&addr_, &addr.addr_, sizeof(addr_));
}

const std::string Ipv6Address::toString()
{
	char ip6[INET6_ADDRSTRLEN];
	inet_ntop(AF_INET6, &(addr_.sin6_addr), ip6, INET6_ADDRSTRLEN);
	return std::string(ip6);
}

/////////////////////////////////////////////////////
UnixAddress::UnixAddress(const std::string & path)
{
	_init();
	addr_.sun_family = AF_UNIX;
}
UnixAddress::UnixAddress(UnixAddress && addr)
{
	addr_ = std::move(addr.addr_);
}
UnixAddress::UnixAddress(const UnixAddress & addr)
{
	memcpy(&addr_, &addr.addr_, sizeof(addr_));
}
const std::string UnixAddress::toString()
{
	return std::string(path());
}

/////////////////////////////////////////////
#include <sys/socket.h>       /* for AF_INET */
//struct hostent *gethostbyaddr(const void *addr, socklen_t len, int type);

void getHostByName()
{

}
/*
struct addrinfo {
     int              ai_flags;
     int              ai_family;
     int              ai_socktype;
     int              ai_protocol;
     socklen_t        ai_addrlen;
     struct sockaddr *ai_addr;
     char            *ai_canonname;
     struct addrinfo *ai_next;
};
*/
void getAddrInfo(const std::string & service)  // prot in string, such as port-"3409"
{
    struct addrinfo hints, *res;

    // load up address structs with getaddrinfo():
    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;  // use IPv4 or IPv6, whichever
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;     // fill in my IP for me

    getaddrinfo(NULL, service.c_str(), &hints, &res);
    struct addrinfo *iter = res;

    while (iter != nullptr) {
        //(res->ai_family, res->ai_socktype, res->ai_protocol);
    	iter = iter->ai_next;
    }

    freeaddrinfo(res);
}
