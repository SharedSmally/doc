#include <SelectMux.h>

#include <sys/select.h>

void SelectMux::run()
{
	fd_set readfds, writefds, exceptfds;
	int nreadrds, nwritefds, nexceptfds, maxfd;
	int fd, ret;
	bool flag;

	while(running_) {
		FD_ZERO(&readfds);
		FD_ZERO(&writefds);
		FD_ZERO(&exceptfds);
		nreadrds = nwritefds = nexceptfds = 1;

		maxfd = efd_;  // check readable-only
		FD_SET(efd_, &readfds);
		//FD_SET(efd_, &writefds);
		FD_SET(efd_, &exceptfds);

		for (auto ptr : channels_) {
			if (!ptr) continue;
			//if (!ptr->active()) continue;

			fd = ptr->fd();
			flag = false;
			IOEvents evts(ptr->events());
			if (evts.isReadable() || evts.isPrioReadable()){
				FD_SET(fd, &readfds);
				++nreadrds; flag=true;
			}
			if (evts.isWriteable()){
				FD_SET(fd, &writefds);
				++nwritefds; flag=true;
			}
			if (flag) {
				FD_SET(fd, &exceptfds);
				++nexceptfds;
				if (maxfd<fd) maxfd = fd;
			}
		}

		//blocked till events happens
		ret = select(maxfd+1, &readfds, nwritefds ? &writefds:nullptr, &exceptfds, nullptr);

		//for (i = 0; i < FD_SETSIZE; ++i) {if (FD_ISSET (i, &read_fd_set)) { } }
	}
}

/*
 * int select(int nfds, fd_set *readfds, fd_set *writefds, fd_set *exceptfds, struct timeval *timeout);
   void FD_ZERO(fd_set *set);
   void FD_CLR(int fd, fd_set *set);
   void FD_SET(int fd, fd_set *set);
   int  FD_ISSET(int fd, fd_set *set);
 *
 */
