#ifndef FDOBJ_H
#define FDOBJ_H

#include <sys/uio.h>

#include <memory>
#include <deque>

enum FdEvents {
    READ = 0x01,
    READ_PRIO = 0x02,
    WRITE = 0x04,
    HUP = 0x08,
    ERR = 0x81
};

template <typename MUX >
class Lockable
{
public:
	typename MUX mutex_type;
	Lockable() {}
	~Lockable() {}

	mutex_type &

protected:
	mutex_type mux;
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
/*
class FdObjListener
{
public:
    virtual ~FdObjListener();
    virtual bool onEvents() = 0;
};*/

class FdObj {
public:
	static const int INVALID_FD;
    FdObj(int fd = INVALID_FD);
    virtual ~FdObj();

    int fd() { return fd_; }
    operator bool() const { return fd_ > INVALID_FD; }

    // events to be monitored
    uint32_t getEvents() { return events_; };
    void setEvents(uint32_t e) { events_= e; };

    uint32_t getRetEvents() { return retevents_; };
    void setRetEvents(uint32_t e) { retevents_= e; };

    void setMonitored(bool v = true){ monitored_ = v; }
    bool isMonitored() const { return monitored_; }

    // events that happens
    bool write(const iovec & msg)
    {
       outgoing_.push_back(msg);
    }

    int read(uint8_t *ptr, int left);
    int write(const uint8_t *ptr, int left);

    virtual bool onEvents() { return false; }

protected:
    int fd_;
    volatile bool dontHalt_;
    bool monitored_;
    uint32_t id_;
    uint32_t events_;
    uint32_t retevents_;
    std::deque<iovec> outgoing_;
};

typedef std::shared_ptr<FdObj> FdObjPtr;

class IOEventsHandler
{
public:
    virtual bool onEvents(FdObjPtr & obj) = 0;

};

class FdObjListener
{
public:
    virtual ~FdObjListener();
    virtual bool onEvents(FdObjPtr & obj);

protected:
    virtual void onRead(FdObjPtr & ptr) = 0;
    virtual void onWrite(FdObjPtr & ptr) = 0;
    virtual void onHangup(FdObjPtr & ptr) = 0;
    virtual void onError(FdObjPtr & ptr, int err) = 0;
};


#endif /* end of FDOBJ_H */
