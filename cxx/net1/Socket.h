#ifndef SOCKET_H
#define SOCKET_H

#include <string>
#include <sys/socket.h>

//Only for IPAddress.
#include <Address.h>

typedef std::string Buffer;

class Socket {
	const static int BAD_FD;

public:
	const static int DEFAULT_BACKLOG;
	Socket(int fd = BAD_FD) : fd_(fd) { } ;
	Socket(int domain, int type, int protocol=0);
	virtual ~Socket();
	int fd()  { return fd_;}
	operator bool() const { return fd_ > BAD_FD; }

protected:
	int _bind(const Address & addr);
	int _connect(const Address & addr);
	int _listen(int backlog);
	int _accept(Address & addr);

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

	ssize_t send(const Buffer & buffer, int flags=0);
	ssize_t recv(Buffer & buffer, int flags=0);
};

//local address
class DSocket : public Socket {
public:
	//DSocket(int fd ) : Socket(fd) { } ;
	DSocket(int domain, bool sctp = false);
	virtual ~DSocket(){};

	ssize_t send(const Buffer & buffer, const Address & addr, int flags=0);
	ssize_t recv(Buffer & buffer, Address & addr, int flags=0);
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


/*
connection:type=SOCK_STREAM/0; SOCK_STREAM/IPPROTO_SCTP (one-to-one style)
A typical server has the following sequences :
     1. socket()
     2. bind()
     3. listen()
     4. accept()
        4a: accept() blocks until return a new fd to send()/recv()
     5. close()
A typical client has the following sequences:
     1. socket()
     2. connect()
     2a. send()/recv()
     3. close()
*/
template <typename ADDR>
class Connection : public CSocket {
public:
	Connection(const ADDR & localAddr, const ADDR & remoteAddr, int fd)
	: localAddr_(localAddr), remoteAddr_(remoteAddr), Socket(fd)
	{ };
	virtual ~Connection(){};

	ssize_t send(const Buffer & buffer, int flags=0);
	ssize_t recv(Buffer & buffer, int flags=0);

	const ADDR & remoteAddr() const { return remoteAddr_;}
	const ADDR & localAddr() const  { return localAddr_; }
	const ADDR & serverAddr() const { return localAddr_; }

protected:
	ADDR remoteAddr_; // remote
	ADDR localAddr_;  // local server address
};



//local and remote address
template <typename ADDR>
class ClientSocket : public CSocket {
public:
	ClientSocket(const ADDR & addr, const ADDR & svrAddr, bool sctp=false)
		: remoteAddr_(svrAddr), localAddr_(addr),
		  CSocket(addr.domain(), sctp)
	{
	}
	virtual ~ClientSocket() { };

	const ADDR & remoteAddr() const { return remoteAddr_;}
	const ADDR & localAddr() const  { return localAddr_; }
	const ADDR & serverAddr() const { return remoteAddr_; }

	int connect(bool bind=false)
	{
		int ret(0);
		if (bind)
		{
			ret = _bind(localAddr_);
		}
		ret = _connect(remoteAddr_);
		return ret;
	}

protected:
	ADDR remoteAddr_;// remote server address
	ADDR localAddr_; // local address
};

//local address
template <typename ADDR>
class ServerSocket : public Socket {

public:
	ServerSocket(const ADDR & addr, bool sctp=false)
	: localAddr_(addr), Socket(addr.domain(),
			sctp ? SOCK_STREAM : SOCK_STREAM,
			sctp ? IPPROTO_SCTP : 0)
	{}
	virtual ~ServerSocket(){};

	const ADDR & localAddr() const  { return localAddr_; }
	const ADDR & serverAddr() const { return localAddr_; }

	int listen(int backlog=DEFAULT_BACKLOG)
	{
		int ret = _bind(localAddr_);
		ret = _listen(backlog);
		return ret;
	}

	// blocked to return connection
	int accept(ADDR & remoteAddr)
	{
		return _accept(remoteAddr);
	}

protected:
	ADDR localAddr_; // local address
};

/*
 connectionless socket: SOCK_DGRAM/0; SOCK_SEQPACKET/IPPROTO_SCTP
 A typical server has the following sequences:
     1. socket()
     2. bind()
     3. listen()
     4. recvmsg()
     5. sendmsg()
     6. close()
 A typical client has the following sequences:
     1. socket()
     2. sendmsg()
     3. recvmsg()
     4. close()
 */
#endif
