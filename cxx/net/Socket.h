#ifndef SOCKET_H
#define SOCKET_H

#include <FdObj.h>
#include <Address.h>

class Socket : public FdObj{
public:
	Socket(int fd) : FdObj(fd) {};
	Socket(const Address & addr, int type, int protocol);
    virtual ~Socket();

protected:

private:

};
/*
struct ip_mreqn {
    struct in_addr imr_multiaddr; // IP multicast group address
    struct in_addr imr_address;   // IP address of local interface
    int            imr_ifindex;   // interface index
};

struct ip_mreq_source {
    struct in_addr imr_multiaddr;  // IP multicast group address
    struct in_addr imr_interface;  // IP address of local interface
    struct in_addr imr_sourceaddr; // IP address of multicast source
};
 */

class RawSocket : public Socket {
public:
	RawSocket(int fd) : Socket(fd) {};
    RawSocket(const Address & addr, int protocol);
};

class TcpSocket : public Socket {
public:
	TcpSocket(int fd) : Socket(fd) {};
    TcpSocket(const Address & addr);
};

class UdpSocket : public Socket {
public:
	UdpSocket(int fd) : Socket(fd) {};
    UdpSocket(const Address & addr);
};

class SctpSocket : public Socket {
public:
	SctpSocket(int fd) : Socket(fd) {};
    SctpSocket(const Address & addr);
};

class MsctpSocket : public Socket {
public:
	MsctpSocket(int fd) : Socket(fd) {};
    MsctpSocket(const Address & addr);
};

#endif /* end of SOCKET_H */
