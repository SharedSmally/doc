#ifndef SERVER_H
#define SERVER_H

#include <unistd.h>
#include <sys/socket.h>

#include <Socket.h>
#include <Multiplexer.h>

template <typename ADDR, typename SOCK >
class Server : public SOCK {
public:
	typedef Connection<ADDR, SOCK> connection_type;
	typedef std::shared_ptr<connection_type> connptr_type;
	typedef std::vector<connptr_type> conn_container_type;

    Server(Multiplexer & mux, const ADDR & addr, int backlog)
	: addr_(addr), SOCK(addr),mux_(mux)
    {
    	SOCK::setEvents(FdEvents::READ|FdEvents::READ); // only for read
        int ret(0);
        ret = ::bind(SOCK::fd(), addr_.addr(), addr_.addrlen());
        if (ret != 0) perror ("bind error");
    	ret = ::listen(SOCK::fd(), backlog);
    	if (ret != 0) perror ("listen error");
    	//return ret;
    }
    ~Server()
    {
    }
    Multiplexer & mux() { return mux_; }

    virtual bool onEvents()
	{
    	 uint32_t events = SOCK::getRetEvents();
    	if (events & ( FdEvents::READ | FdEvents::READ_PRIO) )
    	{
    		FdObjPtr fdptr = std::static_pointer_cast<FdObj>(accept());

    		if (fdptr) mux_.add( fdptr);

    		return true;
    	}
    	// other:
    	return true;
	}

    connptr_type accept()
    {
    	INFO( "accept connection:" );
    	connptr_type ptr = std::make_shared<connection_type>();
    	ADDR & addr = ptr->addr();
    	auto len = addr.addrlen();
    	int fd0 = ::accept(SOCK::fd(), addr.addr(), &len);
    	if (fd0 > -1) {
    		ptr->fd(fd0);
    		// config ptr
    	} else {
    		ptr.reset();
    	}
    	return ptr;
    }

protected:
    ADDR addr_;
    Multiplexer & mux_;
    conn_container_type conns_;
};


typedef Server<Ipv4Address, TcpSocket> Tcpv4Server;
typedef Server<Ipv6Address, TcpSocket> Tcpv6Server;
typedef Server<IpAddress,   TcpSocket> TcpIpServer;
typedef Server<UnixAddress, TcpSocket> TcpLocalServer;

typedef Server<Ipv4Address, SctpSocket> Sctpv4Server;
typedef Server<Ipv6Address, SctpSocket> Sctpv6Server;
typedef Server<IpAddress,   SctpSocket> SctpIpServer;
typedef Server<UnixAddress, SctpSocket> SctpLocalServer;

#endif /* end of SERVER_H */
