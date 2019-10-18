#include <Socket.h>

#include <unistd.h>
#include <sys/socket.h>
#include <netinet/sctp.h>
#include <sys/socket.h>

const int Socket::BAD_FD(-1);
const int Socket::DEFAULT_BACKLOG(10);

Socket::Socket(int domain, int type, int protocol)
{
	fd_ = socket(domain, type, protocol);
	//check
}
Socket::~Socket()
{
	if (fd_ > BAD_FD)
		::close(fd_);
}

int Socket::_bind(const Address & addr)
{
	int ret = ::bind(fd_, addr.addr(), addr.length());
	return ret;
}
int Socket::_connect(const Address & addr)
{
	int ret = ::connect(fd_, addr.addr(), addr.length());
	return ret;
}

int Socket::_listen(int backlog)
{
	int ret = ::listen(fd_, backlog);
	return ret;
}

int Socket::_accept(Address & addr)
{
	socklen_t len = addr.maxLength();
	int ret = ::accept(fd_, addr.addr(), &len);
	return ret;
}

CSocket::CSocket(int domain, bool sctp)
: Socket(domain,sctp ? SOCK_STREAM : SOCK_STREAM,
		sctp ? IPPROTO_SCTP : 0)
{
}

//ssize_t send(int socket, const void *buffer, size_t length, int flags); flags: MSG_EOR, MSG_OOB
//ssize_t recv(int socket, void *buffer, size_t length, int flags); flags: MSG_PEEK, MSG_OOB, MSG_WAITALL
ssize_t CSocket::send(const Buffer & buffer, int flags)
{
	ssize_t total(0);
    size_t left = buffer.size();
    int ret (0);
    char *ptr = (char *)buffer.data();

    while (left != 0 ) {
        int ret = ::send(fd_, ptr, left, flags);

        if (ret == 0 || ret == left)
        {
            return( total + ret );
        }

        if (ret == -1)
        {
            if (errno == EINTR)
                continue;
            else
                return (-1); //error
        }

        left -= ret;
        ptr += ret;
        total += ret;
    }

    return (total);

}
ssize_t CSocket::recv( Buffer & buffer, int flags)
{
	ssize_t total(0);
    size_t left = buffer.size();
    char *ptr = (char *)buffer.data();

    while (left != 0) {
        int ret = ::recv(fd_, ptr, left, flags);

        if (ret == 0 || ret == left)
        {
            return( total + ret );
        }

        if (ret == -1)
        {
            if (errno == EINTR)
                continue;
            else
                return (-1); //error
        }

        left -= ret;
        ptr += ret;
        total += ret;
    }

    return (total);
}

DSocket::DSocket(int domain, bool sctp)
: Socket(domain, sctp ? SOCK_SEQPACKET : SOCK_DGRAM,
		sctp ? IPPROTO_SCTP : 0)
{
}

//ssize_t sendto(int socket, const void *message, size_t length, int flags, const struct sockaddr *dest_addr, socklen_t dest_len);
//ssize_t recvfrom(int socket, void *restrict buffer, size_t length, int flags, struct sockaddr * address, socklen_t * address_len);

ssize_t DSocket::send(const Buffer & buffer, const Address & addr, int flags)
{
	ssize_t cnt(0);
	int errNum(0);

	//while (true) {
		cnt = ::sendto(fd_, (const void *)buffer.data(), buffer.size(), flags, addr.addr(), addr.length());
		if (cnt != -1) return cnt;
		errNum = errno;
		//if(errNum == ENOMEM || errNum == ENOSR)
		//other throw exception
	//}
}

ssize_t DSocket::recv(Buffer & buffer, Address & addr, int flags)
{
	ssize_t cnt(0);
	int errNum(0);
	socklen_t addrLen = addr.maxLength();

	//while (true) {
		cnt = ::recvfrom(fd_, (void *) buffer.data(), buffer.size(), flags, addr.addr(), &addrLen);
		if (cnt != -1) return cnt;
		errNum = errno;
		//if(errNum == ENOMEM || errNum == ENOSR)
		//other throw exception
	//}
}


RSocket::RSocket(int domain, int protocol)
: Socket(domain, SOCK_RAW, protocol)
{
}


ssize_t RSocket::send(const struct msghdr &msg, int flags)
{
	return ::sendmsg(fd_, &msg, flags);
}
ssize_t RSocket::recv(struct msghdr &msg, int flags)
{
	return ::recvmsg(fd_, &msg, flags);
}

