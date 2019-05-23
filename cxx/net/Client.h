#ifndef CLIENT_H
#define CLIENT_H

#include <unistd.h>
#include <Socket.h>
#include <Multiplexer.h>

template <typename ADDR, typename SOCK >
class Client : public SOCK {
public:
    Client(Multiplexer & mux, const ADDR & addr, const ADDR & server)
	: addr_(addr), server_(server),SOCK(addr),mux_(mux)
    {
    	SOCK::setEvents(FdEvents::READ|FdEvents::READ|FdEvents::WRITE);
    	int ret(0);

    	ret = ::bind(SOCK::fd(), addr_.addr(), addr_.addrlen());
        if (ret != 0) perror ("bind error");

    	ret = ::connect(SOCK::fd(), server.addr(), server.addrlen());
    	if (ret != 0) perror ("connect error");
    	//return ret;
    }
    ~Client()
    {
    }
    Multiplexer & mux() { return mux_; }

protected:
    ADDR addr_, server_;
    Multiplexer & mux_;
};

typedef Client<Ipv4Address, TcpSocket> Tcpv4Client;
typedef Client<Ipv6Address, TcpSocket> Tcpv6Client;
typedef Client<IpAddress,   TcpSocket> TcpIpClient;
typedef Client<UnixAddress, TcpSocket> TcpLocalClient;

typedef Client<Ipv4Address, SctpSocket> Sctpv4Client;
typedef Client<Ipv6Address, SctpSocket> Sctpv6Client;
typedef Client<IpAddress,   SctpSocket> SctpIpClient;
typedef Client<UnixAddress, SctpSocket> SctpLocalClient;

#endif /* end of CLIENT_H */
