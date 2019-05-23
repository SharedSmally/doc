#ifndef SOCKET_H
#define SOCKET_H

#include <unistd.h>

#include <FdObj.h>
#include <Address.h>

class Socket : public FdObj{
public:
	Socket(int fd) : FdObj(fd) {};
	Socket(const Address & addr, int type, int protocol);
    virtual ~Socket();
    virtual int type() const = 0;

protected:

private:
};

// connection-based stream socket:
class CSocket : public Socket{
public:
	CSocket(int fd) : Socket(fd) {};
	CSocket(const Address & addr, int protocol = 0);
    virtual ~CSocket() { }
    virtual int type() const;

    int recv(uint8_t *ptr, int left, int flags);
    int send(const uint8_t *ptr, int left, int flags);
};

// connectionless-based dgram socket:
class DSocket : public Socket {
public:
	DSocket(int fd) : Socket(fd) {};
	DSocket(const Address & addr, int type, int protocol = 0);
    virtual ~DSocket() {}
    virtual int type() const { return type_; }

    int recvfrom(Address & addr, uint8_t *ptr, int left, int flags);
    int sendto(const Address & addr, const uint8_t *ptr, int left, int flags);

private:
    int type_;
};

class RawSocket : public Socket {
public:
	RawSocket(int fd) : Socket(fd) {};
    RawSocket(const Address & addr, int protocol);

    int recvmsg(struct msghdr & msg, int flags);
    int sendmsg(const struct msghdr & msg, int flags);
};



class TcpSocket : public CSocket {
public:
	TcpSocket(int fd) : CSocket(fd) {};
    TcpSocket(const Address & addr);
};

class UdpSocket : public DSocket {
public:
	UdpSocket(int fd) : DSocket(fd) {};
    UdpSocket(const Address & addr);
};
class McastSocket : public UdpSocket {
public:
	McastSocket(int fd) : UdpSocket(fd) {};
    McastSocket(const Address & addr, int protocol);

    //void join(const Address &group, const Address &interface); //getInterfaceIndex for ipv6
    //void leave(const Address &group, const Address &interface);
};


class SctpSocket : public CSocket {
public:
	SctpSocket(int fd) : CSocket(fd) {};
    SctpSocket(const Address & addr);
};

class MsctpSocket : public DSocket {
public:
	MsctpSocket(int fd) : DSocket(fd) {};
    MsctpSocket(const Address & addr);
};

template <typename ADDR, typename SOCK>
class Connection : public SOCK
{
public:
	Connection() : addr_(), SOCK(-1){};
	~Connection() {}

	ADDR & addr() { return addr_; }
	const ADDR & addr() const { return addr_; }

	void fd(int fdval)
	{
		if (SOCK::fd_>-1) ::close(SOCK::fd_);
		SOCK::fd_ = fdval;
	}

protected:
	ADDR addr_;
};

#endif /* end of SOCKET_H */
