#ifndef SOCKET_H
#define SOCKET_H

#include <string>
#include <sys/socket.h>

#include <Address.h>

typedef std::string Buffer;

class Socket {
	const static int BAD_FD;
public:
	Socket(int fd = BAD_FD) : fd_(fd) { } ;
	Socket(int domain, int type, int protocol=0);
	virtual ~Socket();
	int fd()  { return fd_;}
	operator bool() const { return fd_ > BAD_FD; }

protected:
	int fd_;
};

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
class CSocket : public Socket {
	const static int BAD_FD;
public:
	CSocket(int fd) : Socket(fd) { } ;
	CSocket(const Address & addr, bool bind, bool sctp=false);
	CSocket(int domain, bool sctp);
	virtual ~CSocket(){};

	ssize_t send(const Buffer & buffer, int flags=0);
	ssize_t recv(Buffer & buffer, int flags=0);

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
class DSocket : public Socket {
public:
	DSocket(int fd ) : Socket(fd) { } ;
	DSocket(const Address & addr, bool bind, bool sctp=false);
	DSocket(int domain, bool sctp);
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
#endif
