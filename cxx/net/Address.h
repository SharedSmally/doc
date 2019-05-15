#ifndef ADDRESS_H
#define ADDRESS_H

class Address {
public:
    Address();
    ~Address();

    virtual int domain() const = 0;
};

class IpAddress
{
public:
	virtual int domain() const;

private:
	bool v4_;
};

class Ipv4Address
{
public:
	virtual int domain() const;

};
/* man -s7 ip
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
class Ipv6Address
{
public:
	virtual int domain() const;

};

/* man ipv6
 struct sockaddr_in6 {
    sa_family_t     sin6_family;   // AF_INET6
    in_port_t       sin6_port;     // port number
    uint32_t        sin6_flowinfo; // IPv6 flow information
    struct in6_addr sin6_addr;     // IPv6 address
    uint32_t        sin6_scope_id; // Scope ID (new in 2.4)
};
struct in6_addr {
    unsigned char   s6_addr[16];   // IPv6 address
};
 */
class UnixAddress
{
public:
	virtual int domain() const;
};
/*
#define UNIX_PATH_MAX    108
struct sockaddr_un {
    sa_family_t sun_family;               // AF_UNIX
    char        sun_path[UNIX_PATH_MAX];  // pathname
};
 */
#endif /* end of ADDRESS_H */
