#include <EpollMux.h>

#include <unistd.h>
#include <sys/epoll.h>

#include <iostream>

const int EpollMux::MAX_EVENTS(10);

EpollMux::EpollMux(uint32_t initSize)
  : Multiplexer(initSize)
{
	epollfd_ = epoll_create1(0);

	struct epoll_event ev;
    ev.events = EPOLLIN | EPOLLET;
    ev.data.fd = efd_;

    if (epoll_ctl(epollfd_, EPOLL_CTL_ADD, efd_, &ev) == -1) {
    	//error
    }
}

EpollMux::~EpollMux()
{
	::close(epollfd_);

	struct epoll_event ev;
    ev.events = 0;
    ev.data.fd = efd_;

    if (epoll_ctl(epollfd_, EPOLL_CTL_DEL, efd_, &ev) == -1) {
    	//error
    }
}

bool EpollMux::_join(ChannelPtr & channel, bool modify)
{
	if (!channel) return false;

	struct epoll_event ev;
    ev.events = getEpollEvents(channel);
    ev.data.fd = channel->fd();
    ev.data.u64 = channel->id();
    int op = modify ? EPOLL_CTL_MOD : EPOLL_CTL_ADD;
    return epoll_ctl(epollfd_, op, channel->fd(), &ev) != -1;
}

bool EpollMux::_leave(ChannelPtr & channel)
{
	if (!channel) return false;

	struct epoll_event ev;
    ev.events = 0;
    ev.data.fd = channel->fd();
    ev.data.u64 = channel->id();

    return (epoll_ctl(epollfd_, EPOLL_CTL_DEL, channel->fd(), &ev) != -1);
}

uint32_t EpollMux::getEpollEvents(ChannelPtr & channel)
{
	if (!channel) return 0;
	uint32_t events(0);

	if (Channel::isReadable(channel->events()))
		events |= EPOLLIN;

	if (Channel::isPrioReadable(channel->events()))
		events |= EPOLLPRI;

	if (Channel::isPrioReadable(channel->events()))
		events |= EPOLLOUT;

	//Edge Triggered: EPOLLONESHOT
	events |= EPOLLET;
	events |= EPOLLONESHOT; // need to use EPOLL_CTL_MOD to active it

	return events;
}

void EpollMux::_run()
{
	struct epoll_event events[MAX_EVENTS];
	int nfds(0), n;

	while (running_) {
		nfds = epoll_wait(epollfd_, events, MAX_EVENTS, -1);
		if (nfds == -1) {
			// error
		}

        for (n = 0; n < nfds; ++n) {
            if (events[n].data.fd == efd_) {

            } else {
            	std::cout << "epoll fd=" << events[n].data.fd << "; events=" << events[n].events << "; id="<< events[n].data.u64 << std::endl;
                //do_use_fd(events[n].data.fd);
            }
        }
	}
}
