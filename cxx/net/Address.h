#ifndef ADDRESS_H
#define ADDRESS_H

#include <string>
#include <sys/un.h>
#include <netinet/in.h>

class Address {
public:
    Address(){};
    virtual ~Address(){}

    int domain() const { return addr()->sa_family; }
    virtual struct sockaddr * addr() = 0;
    virtual const struct sockaddr * addr() const = 0;
    virtual socklen_t addrlen() const = 0;
    virtual const std::string toString() = 0;

    bool operator==(const Address & addr) const;
    bool operator<(const Address & addr) const;

protected:
    void _init();
};

/*
struct sockaddr {
    unsigned short    sa_family;    // address family, AF_xxx
    char              sa_data[14];  // 14 bytes of protocol address
};
 */
class IpAddress : public Address
{
public:
	IpAddress(uint16_t port=0, bool v4 = false);
	IpAddress(const std::string & ip, uint16_t port=0);
	IpAddress(IpAddress && addr);
	IpAddress(const IpAddress & addr);
	virtual ~IpAddress(){}

    virtual struct sockaddr * addr() { return (struct sockaddr *) (&addr_); }
    virtual const struct sockaddr * addr() const { return (const struct sockaddr *)(&addr_); }
    virtual socklen_t addrlen() const { return sizeof(sockaddr_storage); }
    virtual const std::string toString();

private:
	bool v4_;
	struct sockaddr_storage addr_;
};
/*
 struct sockaddr_storage {
    sa_family_t  ss_family;     // address family

    // all this is padding, implementation specific, ignore it:
    char      __ss_pad1[_SS_PAD1SIZE];
    int64_t   __ss_align;
    char      __ss_pad2[_SS_PAD2SIZE];
};
 */
class Ipv4Address : public Address
{
public:
	Ipv4Address(uint16_t port=0);
	Ipv4Address(const std::string & ip, uint16_t port=0);
	Ipv4Address(Ipv4Address && addr);
	Ipv4Address(const Ipv4Address & addr);
	virtual ~Ipv4Address() {}

    virtual struct sockaddr * addr() { return (struct sockaddr *) (&addr_); }
    virtual const struct sockaddr * addr() const { return (const struct sockaddr *)(&addr_); }
    virtual socklen_t addrlen() const { return sizeof(sockaddr_in); }
    virtual const std::string toString();

private:
	struct sockaddr_in addr_;
};
/* man -s7 ip
struct sockaddr_in {
    short            sin_family;   // e.g. AF_INET, AF_INET6
    unsigned short   sin_port;     // e.g. htons(3490)
    struct in_addr   sin_addr;     // see struct in_addr, below
    char             sin_zero[8];  // zero this if you want to
};

struct in_addr {
    unsigned long s_addr;          // load with inet_pton()
};
 */
class Ipv6Address : public Address
{
public:
	Ipv6Address(uint16_t port=0);
	Ipv6Address(const std::string & ip, uint16_t port=0);
	Ipv6Address(Ipv6Address && addr);
	Ipv6Address(const Ipv6Address & addr);
	virtual ~Ipv6Address() {}

    virtual struct sockaddr * addr() { return (struct sockaddr *) (&addr_); }
    virtual const struct sockaddr * addr() const { return (const struct sockaddr *)(&addr_); }
    virtual socklen_t addrlen() const { return sizeof(sockaddr_in6); }
    virtual const std::string toString();

private:
    struct sockaddr_in6 addr_;
};

/* man ipv6
struct sockaddr_in6 {
    u_int16_t       sin6_family;   // address family, AF_INET6
    u_int16_t       sin6_port;     // port number, Network Byte Order
    u_int32_t       sin6_flowinfo; // IPv6 flow information
    struct in6_addr sin6_addr;     // IPv6 address
    u_int32_t       sin6_scope_id; // Scope ID
};

struct in6_addr {
    unsigned char   s6_addr[16];   // load with inet_pton()
};
 */
class UnixAddress : public Address
{
public:
	UnixAddress(const std::string & path);
	UnixAddress(UnixAddress && addr);
	UnixAddress(const UnixAddress & addr);
	virtual ~UnixAddress(){}

    virtual struct sockaddr * addr() { return (struct sockaddr *) (&addr_); }
    virtual const struct sockaddr * addr() const { return (const struct sockaddr *)(&addr_); }
    virtual socklen_t addrlen() const { return sizeof(sockaddr_un); }
    socklen_t maxlen() const { return sizeof(addr_.sun_path)-1; }
    virtual const std::string toString();

    const char * path() const { return addr_.sun_path; }

private:
    struct sockaddr_un addr_;
};
/*
#define UNIX_PATH_MAX    108
struct sockaddr_un {
    sa_family_t sun_family;               // AF_UNIX
    char        sun_path[UNIX_PATH_MAX];  // pathname
};
 */

void getHostByName(const std::string & hostname);
void getAddrInfo(const std::string & service);

#endif /* end of ADDRESS_H */
