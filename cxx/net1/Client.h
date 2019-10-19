#ifndef CPW_NET_CLIENT_H
#define CPW_NET_CLIENT_H

#include <Socket.h>
#include <Macro.h>

//connection-based client: local and remote address
/*
A typical client has the following sequences:
     1. socket()
     2. connect()
     2a. send()/recv()
     3. close()
*/
template <typename ADDR>
class ClientSocket : public CSocket {
public:
    ClientSocket(const ADDR & addr, const ADDR & svrAddr, bool sctp=false)
        : remoteAddr_(svrAddr), localAddr_(addr),
          CSocket(addr.domain(), sctp), connected_(false)
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
            INFO("client bind=" << ret);
        }
        ret = _connect(remoteAddr_);
        INFO("client connect=" << ret);
        return ret;
    }

    bool isConnected() const { return connected_; }
    void setConnected(bool v){ connected_=v; }

protected:
    bool connected_;
    ADDR remoteAddr_;// remote server address
    ADDR localAddr_; // local address
};

// connectionless-based client:
/*
  A typical client has the following sequences:
     1. socket()
     2. sendmsg()
     3. recvmsg()
     4. close()
 */
template <typename ADDR>
class DClientSocket : public DSocket {
public:
    DClientSocket(const ADDR & addr, bool sctp=false)
    : localAddr_(addr), DSocket(addr.domain(),sctp)
    {
    }
    virtual ~DClientSocket(){};

    const ADDR & localAddr() const  { return localAddr_; }
    const ADDR & serverAddr() const { return localAddr_; }

protected:
    ADDR localAddr_; // local address
};

#endif

