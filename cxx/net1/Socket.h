#ifndef CPW_NET_SOCKET_H
#define CPW_NET_SOCKET_H

#include <string>
#include <sys/socket.h>

#include <Address.h>

typedef std::string Buffer; // not work as Buffer

class Socket {
	const static int BAD_FD;

public:
	const static int DEFAULT_BACKLOG;
	Socket(int fd = BAD_FD) : fd_(fd) { _nonblock(); } ;
	Socket(int domain, int type, int protocol=0);
	virtual ~Socket();
	int fd()  { return fd_;}
	operator bool() const { return fd_ > BAD_FD; }

protected:
	int _bind(const Address & addr);
	int _connect(const Address & addr);
	int _listen(int backlog);
	int _accept(Address & addr);

	int _nonblock();

protected:
	int fd_;
};

// point-to-point connection-based Socket
class CSocket : public Socket {

public:
	CSocket(int fd)
	: Socket(fd)
	{}
	CSocket(int domain, bool sctp);
	virtual ~CSocket()
	{};

	ssize_t send(const Buffer & data, int flags=0) { return send(data.data(), data.size(), flags); }
	ssize_t send(const char * data, size_t len, int flags=0);
	ssize_t recv(char * data, size_t len, int flags=0);
};

//local address
class DSocket : public Socket {
public:
	DSocket(int domain, bool sctp = false);
	virtual ~DSocket(){};

	ssize_t send(const Buffer & buffer, const Address & addr, int flags=0) { return send(buffer.data(),buffer.size(),addr, flags);}
	ssize_t send(const char * data, size_t len, const Address & addr, int flags=0);
	ssize_t recv(char * data, size_t len, Address & addr, int flags=0);
};

//raw_socket = socket(AF_INET, SOCK_RAW, protocol);
/*
struct msghdr {
    void         *msg_name;       // optional address
    socklen_t     msg_namelen;    // size of address
    struct iovec *msg_iov;        // scatter/gather array
    size_t        msg_iovlen;     // # elements in msg_iov
    void         *msg_control;    // ancillary data, see below
    size_t        msg_controllen; // ancillary data buffer len
    int           msg_flags;      // flags on received message
};
*/

class RSocket : public Socket {
public:
	RSocket(int fd ) : Socket(fd) { } ;
	RSocket(int domain, int protocol);
	virtual ~RSocket(){};

	ssize_t send(const struct msghdr &msgr, int flags=0);
	ssize_t recv(struct msghdr &msg, int flags=0);
};
//ssize_t sendmsg(int sockfd, const struct msghdr *msg, int flags);
//ssize_t recvmsg(int sockfd, struct msghdr *msg, int flags);

#endif
