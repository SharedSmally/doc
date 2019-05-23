#include "PollMux.h"

#include <poll.h>

PollMux::PollMux() {

}

PollMux::~PollMux() {

}

bool PollMux::add(FdObjPtr & ptr)
{

}
bool PollMux::remove(FdObjPtr & ptr)
{

}
bool PollMux::onEvents(FdObjPtr & obj)
{

}

/*
// int poll(struct pollfd *fds, nfds_t nfds, int timeout);
struct pollfd {
    int   fd;         // file descriptor
    short events;     // requested events
    short revents;    // returned events
};
*/

void PollMux::monitorTask()
{

}

bool PollMux::monitor(FdObjPtr & ptr)
{
    struct pollfd *fds(nullptr);
    int nfds(0),index;
    std::deque<int> iotask;

    while (running_) {
        INFO( "preparing for poll:" )
        iotask.empty();
        int size = iotasks_.size()+1;
        if (fds == nullptr) {
            fds = new struct pollfd[size];
        } else if (size > nfds) {
            delete [] fds;
            fds = new struct pollfd[size];
        }

        nfds = 0;
        fds[nfds].fd = notifyfd_;
        fds[nfds].events = POLLIN | POLLPRI;
        ++nfds;

        short events(0);
        uint32_t pe(0);
        for (auto ptr : iotasks_) {
            pe = ptr->getEvents();
            events = 0;
            if (pe & FdEvents::READ)
                events |= POLLIN;
            if (pe & FdEvents::READ_PRIO)
                events |= POLLPRI;
            if (pe & FdEvents::WRITE )
                events |= POLLOUT;

            if (pe != 0) {
                fds[nfds].fd = ptr->fd();
                fds[nfds].events = events;
                ++nfds;
            }
        }

        INFO( "waiting for poll: nfds=" << nfds )
        int ret = poll(fds, nfds, -1);
        INFO( "return from waiting for poll: ret=" << ret );

        for (int i=0; i<ret; ++i) {
        	if (fds[i].fd == notifyfd_) {
        		wakeup(); continue;
        	}

        	events = fds[i].revents;
        	if (events & POLLIN) pe |= FdEvents::READ;
        	if (events & POLLRDNORM) pe |= FdEvents::READ;

        	if (events & POLLPRI) pe |= FdEvents::READ_PRIO;
        	if (events & POLLRDBAND) pe |= FdEvents::READ_PRIO;

        	if (events & POLLOUT) pe |= FdEvents::WRITE;
        	if (events & POLLWRNORM) pe |= FdEvents::WRITE;
        	if (events & POLLWRBAND) pe |= FdEvents::WRITE;

        	if (events & POLLRDHUP) pe |= FdEvents::HUP;
        	if (events & POLLHUP) pe |= FdEvents::HUP;

        	if (events & POLLERR) pe |= FdEvents::ERR;
        	if (events & POLLNVAL) pe |= FdEvents::ERR;
        }

    	//iotasks_.push();
    }

    if (fds!=nullptr) delete[] fds;
}
