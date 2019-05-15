#ifndef FDOBJ_H
#define FDOBJ_H

#include <sys/uio.h>

#include <memory>
#include <deque>

enum FdEvents {
	READ,
	READ_PRIO,
	WRITE,
	HUP,
	ERR
};

/*
struct iovec {
    void  *iov_base;    // Starting address
    size_t iov_len;     // Number of bytes to transfer
};

#include <sys/uio.h>
ssize_t readv(int fd, const struct iovec *iov, int iovcnt);
ssize_t writev(int fd, const struct iovec *iov, int iovcnt);
*/

class FdObj {
public:
    FdObj(int fd);
    virtual ~FdObj();

    int fd() { return fd_; }

    // events to be monitored
    uint32_t getEvents() { return events_; };
    void setEvents(uint32_t e) { events_= e; };

    uint32_t getRetEvents() { return retevents_; };
    void setRetEvents(uint32_t e) { retevents_= e; };

    // events that happens
    bool write(const iovec & msg)
    {
       outgoing_.push_back(msg);
    }

protected:
    int fd_;
    uint32_t events_;
    uint32_t retevents_;
    std::deque<iovec> outgoing_;
};

typedef std::shared_ptr<FdObj> FdObjPtr;

class FdObjListener
{
public:
	virtual ~FdObjListener();
	virtual void onRead(FdObjPtr & ptr) = 0;
	virtual void onWrite(FdObjPtr & ptr) = 0;
	virtual void onHangup(FdObjPtr & ptr) = 0;
	virtual void onError(FdObjPtr & ptr, int err) = 0;
};

#endif /* end of FDOBJ_H */
