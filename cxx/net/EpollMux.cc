#include "EpollMux.h"

#include <string.h>
#include <unistd.h>
#include <sys/epoll.h>
#include <sys/eventfd.h>

#include <iostream>
using namespace std;

//epoll_create
//epoll_wait()
#define MAX_BATCH_SIZE 256
#define INCR_BIT_NUMBER 2

EpollMux::EpollMux()
: epollfd_( epoll_create(1))
{
    //start(numIO, numMonitor);
    addNotify(true);
    //notify(); //not needed
}

EpollMux::~EpollMux()
{
    ::close(epollfd_);
}

bool EpollMux::add(FdObjPtr & ptr)
{
    epoll_event event;
    setEvent(event, ptr);

    {
        //autolock
        locker_type lock(mtx_);
        if (ptr->fd()>container_.size()) // expansion
        {
            auto size = container_.size();
            auto mysize = ptr->fd() + 1;

            // incremented by step of 2**INCR_BIT_NUMBER
            mysize >>= INCR_BIT_NUMBER;
            mysize++;
            mysize <<= INCR_BIT_NUMBER;

            FdObjPtr tmp(nullptr);
            container_.reserve(mysize);
            container_.insert(container_.end(), mysize-size,tmp);
        }

        if ( epoll_ctl(epollfd_, EPOLL_CTL_ADD, ptr->fd(), &event) == 0 )
        {
            //FdObjPtr tmp = ptr->fd(); //handle to old one??
            container_[ptr->fd()] = ptr;
            notify();
            return true;
        }

        // error
        int err = errno;
        if (err == EEXIST) // existing one
        {
            INFO( "error:" << err );
        }
    }

    //ptr->onError(err);
    return false;
}

bool EpollMux::remove(FdObjPtr & ptr)
{
    {
        locker_type lock(mtx_);
        epoll_ctl(epollfd_, EPOLL_CTL_DEL, ptr->fd(), 0);

        container_[ptr->fd()] = nullptr;
        notify();
    }
}

bool EpollMux::monitor(FdObjPtr & ptr)
{
    epoll_event event;
    setEvent(event, ptr);

    locker_type lock(mtx_);
    if (epoll_ctl(epollfd_, EPOLL_CTL_MOD, ptr->fd(), &event) == 0)
    {
        notify();
        return true;
    }

    //error
    {
        //error; err=errno;
    }
    return false;
}

void EpollMux::monitorTask()
{
    epoll_event events[MAX_BATCH_SIZE];
    FdObjPtr iotasks[MAX_BATCH_SIZE];

    memset(events, 0, sizeof(events));
    memset(iotasks, 0, sizeof(iotasks));
    INFO( "enter monitorTask for epoll_create" )

    while (running_) {
        INFO( "waiting for epoll_wait:" )
        int32_t num = epoll_wait(epollfd_, events, MAX_BATCH_SIZE, -1);
        INFO( "return from epoll_create: num=" << num )
        if (num==-1) { //error
            int err = errno;
            if ( (err!= ETIME) && (err!= EINTR) ) {
                // error
            }
            INFO( "return from epoll_create: error=" << err )
            continue;
        }

        if (!running_) break;

        //get the io events
        {
            locker_type lock(mtx_);
            INFO( "get events from epoll_create: num=" << num )
            for (int i=0; i<num; ++i) {
                if (events[i].data.u32 == notifyfd_)
                {
                    INFO1( "get events from eventfd: fd=" << notifyfd_ )
                    uint64_t tmp(0);
                    int rc = read(notifyfd_, &tmp, sizeof(tmp));
                    INFO1( "get events from eventfd: tmp=" << tmp <<"; size=" << rc )
                    //addNotify(false);  // no need to reassociate it.
                }
                else
                {
                    iotasks[i] = container_[events[i].data.u32];
                    if (iotasks[i])
                        iotasks[i]->setRetEvents( getEvents(events[i].events) );
                }
            }
        }

        //execute the io events
        INFO( "execute events from epoll_create: size=" << num )
        bool cvnotif(false);
        for (int i=0; i<num; ++i) {
            // run task to read/write data

            // reconfig to be monitored again.
            if (iotasks[i] && iotasks[i]->getRetEvents() != 0)
            {
                monitor(iotasks[i]);
                cvnotif = true;
            }
        }

        if (cvnotif)
            cv_.notify_all();
    }
}

bool EpollMux::onEvents(FdObjPtr & obj)
{
    return true;
}

bool EpollMux::notify()
{
    uint64_t tmp = 1;
    int rc = write(notifyfd_, &tmp, sizeof(tmp));
    INFO1( "write to notifyfd: rc=" << rc )
    return rc == sizeof(tmp);
}

bool EpollMux::addNotify(bool addit)
{
    epoll_event event;
    event.events   = EPOLLIN; // no EPOLLONESHOT: broadcast to all threads
    event.data.u64  = 0;
    event.data.u32  = notifyfd_;

    int rc = addit ? epoll_ctl(epollfd_, EPOLL_CTL_ADD, notifyfd_, &event)
            : epoll_ctl(epollfd_, EPOLL_CTL_MOD, notifyfd_, &event);
    INFO1( "add notifyfd to be managed: rc=" << rc )
    return (rc==0);
}

void EpollMux::setEvent(epoll_event & event, FdObjPtr & ptr)
{
    event.events  = EPOLLONESHOT; //dissociated after epoll_wait()
    if(ptr->getEvents() & FdEvents::READ)
        event.events |= EPOLLIN;

    if(ptr->getEvents() & FdEvents::WRITE)
        event.events |= EPOLLOUT;

    if(ptr->getEvents() & FdEvents::READ_PRIO)
        event.events |= EPOLLPRI;

    event.data.u64  = 0; // force init
    event.data.u32  = ptr->fd(); // ind | 0x80000000;
}


uint32_t EpollMux::getEvents(uint32_t revents)
{
    uint32_t rtn(0);

    if(revents & EPOLLPRI)
        rtn |= FdEvents::READ_PRIO;

    if(revents & EPOLLIN)
        rtn |= FdEvents::READ;

    if(revents & EPOLLOUT)
        rtn |= FdEvents::WRITE;

    if(revents & EPOLLHUP)
        rtn |= FdEvents::HUP;

    if(revents & EPOLLERR)
        rtn |= FdEvents::ERR;

    return rtn;
}
