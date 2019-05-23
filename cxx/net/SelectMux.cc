#include "SelectMux.h"

SelectMux::SelectMux() {

}

SelectMux::~SelectMux() {

}


bool SelectMux::add(FdObjPtr & ptr)
{

}

bool SelectMux::remove(FdObjPtr & ptr)
{

}
bool SelectMux::onEvents(FdObjPtr & obj)
{

}

void SelectMux::monitorTask()
{
	fd_set readfds, writefds, exceptfds;
	int nfds;

    while (running_) {
        INFO( "preparing for select:" )
        FD_ZERO(&readfds); FD_ZERO(&writefds); FD_ZERO(&exceptfds);
        nfds = 0;
        {
        	//unilocker_type lk(mtx_);
        	for (auto ptr : iotasks_) {
        		if (!ptr->isMonitored()) continue;

        		uint32_t events = ptr->getEvents();
        		int fd = ptr->fd();

        		if (events & (FdEvents::READ | FdEvents::READ_PRIO ) )
        			FD_SET(notifyfd_, &readfds);

        		if (events & FdEvents::WRITE )
        			FD_SET(notifyfd_, &writefds);

                FD_SET(notifyfd_, &exceptfds);

                if (fd > nfds) nfds = fd;
        	}
        }

        FD_SET(notifyfd_, &readfds);
        FD_SET(notifyfd_, &exceptfds);
        if (notifyfd_ > nfds) nfds = notifyfd_;

        nfds++;
        INFO( "waiting for select:" )
        int32_t num = select(nfds, &readfds, &writefds,&exceptfds, nullptr);

        INFO( "return from waiting for select: num=" << num )

    }
}

/*
int select(int nfds, fd_set *readfds, fd_set *writefds, fd_set *exceptfds, struct timeval *timeout);
void FD_CLR(int fd, fd_set *set);
int  FD_ISSET(int fd, fd_set *set);
void FD_SET(int fd, fd_set *set);
void FD_ZERO(fd_set *set);
 */
bool SelectMux::monitor(FdObjPtr & ptr)
{


}
