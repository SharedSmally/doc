#ifndef ADDRESS_H
#define ADDRESS_H

#include <string>

#include <netinet/in.h>
#include <arpa/inet.h>

class Address {
public:
	virtual ~Address() {}
	virtual int domain() const = 0;
	
	virtual struct sockaddr * addr() = 0;
	virtual const struct sockaddr * addr() const = 0;
	
	virtual socklen_t length() const = 0;
	virtual socklen_t size() const { return length(); }
	virtual socklen_t maxLength() const  { return length(); }
};

/*
  struct sockaddr_in {
      sa_family_t    sin_family; // address family: AF_INET
      in_port_t      sin_port;   // port in network byte order
      struct in_addr sin_addr;   // internet address
  };
  // Internet address.
  struct in_addr {
      uint32_t       s_addr;     // address in network byte order
   };
 */
class IPv4Address : public Address {
public:
	IPv4Address(uint16_t p=0);
	IPv4Address(struct sockaddr_in && addr);
	IPv4Address(const struct sockaddr_in & addr);
	IPv4Address(const IPv4Address & addr);
	IPv4Address(IPv4Address && addr);
	IPv4Address(uint32_t i, uint16_t p=0);
	IPv4Address(const std::string & i, uint16_t p=0) ;
	~IPv4Address() {}

	virtual struct sockaddr * addr() { return (struct sockaddr *)(&addr_); }
	virtual const struct sockaddr * addr() const { return (struct sockaddr *)(&addr_); }
	virtual socklen_t length() const     { return sizeof(addr_); }
	virtual socklen_t maxLength() const  { return sizeof(addr_); }

	virtual int domain() const { return AF_INET; }

	void ip(uint32_t p) { addr_.sin_addr.s_addr = htonl(p);}
	uint32_t ipInt() const { return ntohl(addr_.sin_addr.s_addr); }
	bool ip(const std::string & p);
	std::string ip() const;

	void port(uint16_t p) { addr_.sin_port = htons(p); }
	uint16_t port() const { return ntohs(addr_.sin_port); }

protected:
	void _init();
	struct sockaddr_in addr_;
};

#endif
