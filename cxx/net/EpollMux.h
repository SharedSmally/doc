#ifndef EPOLLMUX_H
#define EPOLLMUX_H

#include <Multiplexer.h>
#include <sys/epoll.h>

class EpollMux
  : public Multiplexer
{
public:
    EpollMux();
    ~EpollMux();

    virtual bool add(FdObjPtr & ptr);
    virtual bool remove(FdObjPtr & ptr);

protected:
    virtual void monitorTask();
    virtual void ioTask();

    void setEvent(epoll_event & event, FdObjPtr & );
    uint32_t getEvents(uint32_t revents);

    virtual bool notify(); //notify new set of fds to be minitored
    virtual bool addNotify(bool addit=false);

    bool monitor(FdObjPtr & ptr);

private:
    int epollfd_;
    //single or multiple
};

#endif /* end of EPOLLMUX_H */
