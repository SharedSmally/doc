#ifndef CPW_ADDRESS_H
#define CPW_ADDRESS_H

#include <string>
#include <sys/un.h>
#include <netinet/in.h>

void mapIPV4Addr(const sockaddr_in &in, sockaddr_in6 &in6);

/*
struct sockaddr {
    unsigned short    sa_family;    // address family, AF_xxx
    char              sa_data[14];  // 14 bytes of protocol address
};
*/
class Address
{
protected:
    enum AddressType
    {
        IP,
        IPV4,
        IPV6,
        UNIX
    };

public:
    typedef socklen_t len_type;
    Address(){};
    virtual ~Address(){}

    int domain() const { return addr()->sa_family; }
    virtual AddressType type() const = 0;
    virtual struct sockaddr * addr() = 0;
    virtual const struct sockaddr * addr() const = 0;
    virtual len_type addrlen() const = 0;
    virtual std::string toString() const = 0;

    bool operator==(const Address & addr) const;
    bool operator<(const Address & addr) const;
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
enum NetworkClass {
	CLASS_A,
	CLASS_B,
	CLASS_C,
	CLASS_D
};

class IPv4Address : public Address
{
public:
	static const IPv4Address ANY_ADDR;
	static const IPv4Address BROADCAST_ADDR;
	static const IPv4Address LOOPBACK_ADDR;

	static const IPv4Address GROUP_ADDR;
	static const IPv4Address ALLHOSTS_GROUP_ADDR;
	static const IPv4Address ALLRTRS_GROUP_ADDR;
	static const IPv4Address LOCAL_GROUP_ADDR;

	static const IPv4Address CLASSA_NET_ADDR;
    static const IPv4Address CLASSB_NET_ADDR;
    static const IPv4Address CLASSC_NET_ADDR;
    //static const IPv4Address CLASSD_NET_ADDR;

    IPv4Address(uint16_t port=0);
    IPv4Address(uint32_t ip, uint16_t port=0);
    IPv4Address(const std::string & ip, uint16_t port=0);
    IPv4Address(IPv4Address && addr);
    IPv4Address(const IPv4Address & addr);
    virtual ~IPv4Address() {}

    virtual AddressType type() const { return AddressType::IPV4; }
    virtual struct sockaddr * addr() { return (struct sockaddr *) (&addr_); }
    virtual const struct sockaddr * addr() const { return (const struct sockaddr *)(&addr_); }
    virtual len_type addrlen() const { return sizeof(sockaddr_in); }
    virtual std::string toString() const;  //ip4:port

    int getByName(const std::string & hostname);

    uint32_t getIPInt() const    { return ntohl(addr_.sin_addr.s_addr); }
    void setIP(uint32_t ip)    { addr_.sin_addr.s_addr = htonl(ip); }

    std::string getIP() const      ;
    bool setIP(const std::string & ip)  ;

    uint16_t getPort() const     { return ntohs(addr_.sin_port); }
    void setPort(uint16_t port)  { addr_.sin_port = htons(port); }

    //attributes
    NetworkClass networkClass() const;
    bool isMulticast() const;
    bool isExperimental() const;

private:
    void _init();
    struct sockaddr_in addr_;
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

#include <netinet/in.h>
tcp6_socket = socket(AF_INET6, SOCK_STREAM, 0);
raw6_socket = socket(AF_INET6, SOCK_RAW, protocol);
udp6_socket = socket(AF_INET6, SOCK_DGRAM, protocol);
 */
enum IPv6Type
{
	UNICAST,
	MULTICAST,
	MC_NODE,
	MC_LINK,
	MC_SITE,
	MC_ORG,
	MC_GLOBAL
};
class IPv6Address : public Address
{
public:
	static const IPv6Address ANY_ADDR;
	static const IPv6Address LOOPBACK_ADDR;

    IPv6Address(uint16_t port=0);
    IPv6Address(const struct in6_addr & addr, uint16_t port=0);
    IPv6Address(const std::string & ip, uint16_t port=0);
    IPv6Address(IPv6Address && addr);
    IPv6Address(const IPv6Address & addr);
    virtual ~IPv6Address() {}

    virtual AddressType type() const { return AddressType::IPV6; }
    virtual struct sockaddr * addr() { return (struct sockaddr *) (&addr_); }
    virtual const struct sockaddr * addr() const { return (const struct sockaddr *)(&addr_); }
    virtual socklen_t addrlen() const { return sizeof(sockaddr_in6); }
    virtual std::string toString() const; //[ip6]:port

    int getByName(const std::string & hostname);

    std::string getIP() const ;
    bool setIP(const std::string & ip)  ;

    uint16_t getPort() const     { return ntohs(addr_.sin6_port); }
    void setPort(uint16_t port)  { addr_.sin6_port = htons(port); }

    //attributes
    IPv6Type addrType() const;
    bool isMulticast() const;
    bool isV4Compat() const;
    bool isV4Mapped() const;

    bool isLoopback() const;
    bool isUnspecified() const;
    bool isLinkLocal() const;
    bool isSiteLocal() const;

private:
    void _init();
    struct sockaddr_in6 addr_;
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
class IPAddress : public Address
{
public:
    IPAddress(uint16_t port=0, bool v4 = false);
    IPAddress(const std::string & ip, uint16_t port=0);
    IPAddress(IPAddress && addr);
    IPAddress(const IPAddress & addr);
    virtual ~IPAddress(){}

    virtual AddressType type() const { return AddressType::IP; }
    virtual struct sockaddr * addr() { return (struct sockaddr *) (&addr_); }
    virtual const struct sockaddr * addr() const { return (const struct sockaddr *)(&addr_); }
    virtual socklen_t addrlen() const { return sizeof(sockaddr_storage); }
    virtual std::string toString() const;


    //const std::string getHostName();
    //IPv4Address & ipv4();
    //IPv6Address & ipv6();

    bool isV4() const { return v4_; }
    bool isV6() const { return !v4_; }

    int getByName(const std::string & hostname);

    std::string getIP() const ;
    bool setIP(const std::string & ip)  ;

    uint16_t getPort() const;
    void setPort(uint16_t port);

private:
    void _init();
    bool v4_;
    struct sockaddr_storage addr_;
};


/*
#define UNIX_PATH_MAX    108
struct sockaddr_un {
    sa_family_t sun_family;               // AF_UNIX
    char        sun_path[UNIX_PATH_MAX];  // pathname
};
 */
class UnixAddress : public Address
{
public:
    UnixAddress(const std::string & path);
    UnixAddress(UnixAddress && addr);
    UnixAddress(const UnixAddress & addr);
    virtual ~UnixAddress(){}

    virtual AddressType type() const { return AddressType::UNIX; }
    virtual struct sockaddr * addr() { return (struct sockaddr *) (&addr_); }
    virtual const struct sockaddr * addr() const { return (const struct sockaddr *)(&addr_); }
    virtual socklen_t addrlen() const { return sizeof(sockaddr_un); }
    static socklen_t maxlen() { return sizeof(addr_.sun_path)-1; }
    virtual std::string toString() const;

    const char * path() const { return addr_.sun_path; }

private:
    void _init();
    struct sockaddr_un addr_;
};


// by all types
int getHostByName(IPAddress & addr, const std::string & hostname);

// by IPv4
void getHostByName(const std::string & hostname, bool ipv6);


void getAddrInfo(const std::string & service);
//std::vector<IPAddress> & getInterfaces();

// call_once See https://en.cppreference.com/w/cpp/thread/call_once
class Interface
{
public:

protected:
    //static std::once_flag flag1_;
    //static std::vector<std::string> nicNames_;
};

/*
int32_t net::Address::getInterfaceIndex() const
{
    if(address_.sin6_scope_id != 0)  {
        return address_.sin6_scope_id;
    } else {
        struct ifaddrs *ifaddr, *ifa;
        int32_t index = 0;

        if (getifaddrs(&ifaddr) == -1) {
            return 0;
        }

        for (ifa = ifaddr; ifa != NULL; ifa = ifa->ifa_next) {
            if (ifa->ifa_addr == NULL)
                continue;

            int family = ifa->ifa_addr->sa_family;

            if (family == AF_INET) {
                Address tmp((struct sockaddr_in&)*ifa->ifa_addr);

                if(isSameIP(tmp)){
                    index = if_nametoindex(ifa->ifa_name);
                }
            }
            else if (family == AF_INET6) {
                Address tmp((struct sockaddr_in6&)*ifa->ifa_addr);

                if(isSameIP(tmp)) {
                    index = if_nametoindex(ifa->ifa_name);
                }
            }
        }

        if(index == 0) { // fails to find interface
        }

        freeifaddrs(ifaddr);
        return index;
    }

    return 0;
}
*/
//const std::vector<std::string> & getNICNames(const std::string & name);
//char hostname[MAXHOSTNAMELEN + 1];
// if(gethostname(hostname, MAXHOSTNAMELEN) == 0)
// int gethostname(char *name, size_t len);
// int sethostname(const char *name, size_t len);
// int getdomainname(char *name, size_t len);
// int setdomainname(const char *name, size_t len);
// int uname(struct utsname *name);
//
//

//Interface & getNIC(const std::string & name);

#endif /* end of ADDRESS_H */
