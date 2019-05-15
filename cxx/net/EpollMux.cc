#include "EpollMux.h"

#include <string.h>
#include <unistd.h>
#include <sys/epoll.h>
#include <sys/eventfd.h>

//epoll_create
//epoll_wait()
#define MAX_BATCH_SIZE 256

EpollMux::EpollMux()
: epollfd_( epoll_create(10))
{

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
    	if (ptr->fd()>container_.size()) // expansion
    	{
    		auto size = container_.size();
    		auto mysize = ptr->fd() + 1;
    		mysize >>= 10; mysize++; mysize <<= 10; // incremented by 1k

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

    	}
    }

    //ptr->onError(err);
    return false;
}

bool EpollMux::remove(FdObjPtr & ptr)
{
    {
    	//autolock
    	epoll_ctl(epollfd_, EPOLL_CTL_DEL, ptr->fd(), 0);

    	container_[ptr->fd()] = nullptr;
    	notify();
    }
}

bool EpollMux::monitor(FdObjPtr & ptr)
{
    epoll_event event;
    setEvent(event, ptr);

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

    while (running_) {
        int32_t num = epoll_wait(epollfd_, events, MAX_BATCH_SIZE, -1);
        if (num==-1) { //error
        	int err = errno;
        	if ( (err!= ETIME) && (err!= EINTR) ) {
        		// error
        	}
        	continue;
        }

        if (!running_) break;

        //get the io events
        {
            //AutoLock;
        	for (int i=0; i<num; ++i) {
        		iotasks[i] = container_[events[i].data.u32];
        		iotasks[i]->setRetEvents( getEvents(events[i].events) );
        	}
        }

        //execute the io events
        for (int i=0; i<num; ++i) {
            // run task to read/write data

            // reconfig to be monitored again.
            if (iotasks[i]->getEvents() != 0)
                monitor(iotasks[i]);
        }
    }
}

void EpollMux::ioTask()
{
	while (running_) {
		//
		FdObjPtr obj; // from queue
	}
}

void EpollMux::notify()
{
    int notifyfd_ = eventfd(0, EFD_NONBLOCK | EFD_CLOEXEC);

    epoll_event event;
    event.events   = EPOLLIN; // no EPOLLONESHOT: broadcast to all threads
    event.data.u64  = 0;
    event.data.u32  = notifyfd_;

    int rc = epoll_ctl(epollfd_, EPOLL_CTL_ADD, notifyfd_, &event);
    //uint64_t tmp = 1;
    //rc = write(wakeupfd_, &tmp, sizeof(tmp));
}


void EpollMux::setEvent(epoll_event & event, FdObjPtr & ptr)
{
    event.events  = EPOLLONESHOT; //dissociated after epoll_wait()
    if(ptr->getEvents() & FdEvents::READ)
    {
        event.events |= EPOLLIN;
    }
    if(ptr->getEvents() & FdEvents::WRITE)
    {
        event.events |= EPOLLOUT;
    }
    if(ptr->getEvents() & FdEvents::READ_PRIO)
    {
        event.events |= EPOLLPRI;
    }

    event.data.u64  = 0; // force init
    event.data.u32  = ptr->fd(); // | 0x80000000;
}


uint32_t EpollMux::getEvents(uint32_t revents)
{
	uint32_t rtn(0);

    if(revents & EPOLLPRI)
    {
        rtn |= FdEvents::READ_PRIO;
    }
    if(revents & EPOLLIN)
    {
        rtn |= FdEvents::READ;
    }
    if(revents & EPOLLOUT)
    {
        rtn |= FdEvents::WRITE;
    }
    if(revents & EPOLLHUP)
    {
        rtn |= FdEvents::HUP;
    }
    if(revents & EPOLLERR)
    {
        rtn |= FdEvents::ERR;
    }

    return rtn;
}
