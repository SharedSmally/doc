#ifndef SOCKETOPTS_H
#define SOCKETOPTS_H

//<fcntl.h>
class FDObjectOpts
{
public:
    FDObjectOpts (FDObject & fd)
    : fd_(fd)
    {}
    ~FDObjectOpts()
    {}
    
 protected:
    FDObject & fd_;
}

class SocketOpts
{
public:
    SocketOpts (Socket & sock)
    : sock_(sock)
    {}
    ~SocketOpts()
    {}
    
 protected:
    Socket & sock_;
};

class TcpSocketOpts
{
public:
    TcpSocketOpts (TcpSocket & sock)
    : sock_(sock)
    {}
    ~TcpSocketOpts()
    {}
    
 protected:
    TcpSocket & sock_;
};

#endif
