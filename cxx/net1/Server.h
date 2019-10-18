#ifndef CPW_NET_SERVER_H
#define CPW_NET_SERVER_H

#include <string.h>

#include <Socket.h>
#include <Macro.h>

/*
connection:type=SOCK_STREAM/0; SOCK_STREAM/IPPROTO_SCTP (one-to-one style)
A typical server has the following sequences :
     1. socket()
     2. bind()
     3. listen()
     4. accept()
        4a: accept() blocks until return a new fd to send()/recv()
     5. close()
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
        INFO("server bind=" << ret);
        if (ret==-1) {
            int e = errno;
            INFO("server bind error=" << e << ":" << strerror(e));
        }
        ret = _listen(backlog);
        INFO("server listen=" << ret);
        if (ret==-1) {
            int e = errno;
            INFO("server listen error=" << e << ":" << strerror(e));
        }
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
     3. listen() for sctp
     4. recvmsg()
     5. sendmsg()
     6. close()
 */
template <typename ADDR>
class DServerSocket : public DSocket {
public:
    DServerSocket(const ADDR & addr, bool sctp=false)
    : localAddr_(addr), DSocket(addr.domain(),sctp)
    {
        int ret = _bind(localAddr_);
        if (sctp)
        {
            ret = _listen();
        }
    }
    virtual ~DServerSocket(){};

    const ADDR & localAddr() const  { return localAddr_; }
    const ADDR & serverAddr() const { return localAddr_; }

protected:
    ADDR localAddr_; // local address
};

#endif
