#include <EpollMux.h>
#include <Macro.h>

#include <unistd.h>
#include <string.h>
#include <sys/epoll.h>

const int EpollMux::MAX_EVENTS(10);

/*
typedef union epoll_data {
    void        *ptr;
    int          fd;
    uint32_t     u32;
    uint64_t     u64;
} epoll_data_t;

struct epoll_event {
    uint32_t     events;      // Epoll events
    epoll_data_t data;        // User data variable
};
*/

EpollMux::EpollMux(ChannelListener & listener, uint32_t initSize)
  : Multiplexer(listener, initSize)
{
    epollfd_ = epoll_create1(0);

    struct epoll_event ev;
    ev.events = EPOLLIN | EPOLLET; //no shapshoot
    ev.data.u64 = efd_;

    INFO("EpollMux::_join: efd=" << efd_);
    if (epoll_ctl(epollfd_, EPOLL_CTL_ADD, efd_, &ev) == -1) {
        //error
        INFO("efd: epoll_ctl fails: errno=" << errno << "; msg=" << strerror(errno));
    }
    INFO("efd: epoll_ctl success:");
}

EpollMux::~EpollMux()
{
    ::close(epollfd_);

    struct epoll_event ev;
    ev.events = 0;
    ev.data.u64 = efd_;

    if (epoll_ctl(epollfd_, EPOLL_CTL_DEL, efd_, &ev) == -1) {
        //error
    }
}

bool EpollMux::_join(ChannelPtr & channel, bool modify)
{
    if (!channel) return false;
    INFO("EpollMux::_join: fd=" << channel->fd() <<";id=" << channel->id() << "; modify=" << modify);
    struct epoll_event ev;
    ev.events = getEpollEvents(channel);
    ev.data.u64 = toEpollU64(channel->id(), channel->fd());
    int op = modify ? EPOLL_CTL_MOD : EPOLL_CTL_ADD;
    return epoll_ctl(epollfd_, op, channel->fd(), &ev) != -1;
}

bool EpollMux::_leave(ChannelPtr & channel)
{
    if (!channel) return false;

    struct epoll_event ev;
    ev.events = 0;
    ev.data.u64 = toEpollU64(channel->id(), channel->fd());

    return (epoll_ctl(epollfd_, EPOLL_CTL_DEL, channel->fd(), &ev) != -1);
}

uint32_t EpollMux::getEpollEvents(ChannelPtr & channel)
{
    if (!channel) return 0;
    if (channel->server()) return EPOLLIN | EPOLLET;

    uint32_t events(0);

    if (Channel::isReadable(channel->events()))
        events |= EPOLLIN;

    if (Channel::isPrioReadable(channel->events()))
        events |= EPOLLPRI;

    if (Channel::isPrioReadable(channel->events()))
        events |= EPOLLOUT;

    //Default is Level-Trigger
    //Edge Triggered: EPOLLONESHOT can be applied
    events |= EPOLLET;
    events |= EPOLLONESHOT; // need to use EPOLL_CTL_MOD to active it

    return events;
}

uint32_t EpollMux::getChannelEvents(uint32_t events)
{
	uint32_t evts(0);
	if ( (events & EPOLLIN ) == EPOLLIN) evts |= Channel::IN_EVENT;
	if ( (events & EPOLLPRI ) == EPOLLPRI) evts |= Channel::IN_PRIO_EVENT;

	if ( (events & EPOLLOUT ) == EPOLLOUT ) evts |= Channel::OUT_EVENT;

	if ( (events & EPOLLHUP ) == EPOLLHUP) evts |= Channel::HUP_EVENT;
	if ( (events & EPOLLRDHUP ) == EPOLLRDHUP) evts |= Channel::HUP_EVENT;

	if ( (events & EPOLLERR ) == EPOLLERR) evts |= Channel::ERROR_EVENT;

	return evts;
}

//first 32bits for id; and last 32bits for fd
uint64_t EpollMux::toEpollU64(Channel::id_type id, uint32_t fd)
{
	uint64_t u64(id);
	u64 <<= 32;
	u64 |= fd;
	return u64;
}
void EpollMux::fromEpollU64(Channel::id_type & id, uint32_t & fd, uint64_t u64)
{
	fd = u64 & 0xFFFFFFFF;
	u64 >>= 32;
	id = u64 & 0xFFFFFFFF;
}

void EpollMux::_run()
{
    struct epoll_event events[MAX_EVENTS];
    int nfds(0), n, evts;
    uint64_t value(0);
    Channel::id_type id(0);
    uint32_t fd;

    while (running_) {
        nfds = epoll_wait(epollfd_, events, MAX_EVENTS, -1);
        if (nfds == -1) {
            // error
            ERROR("epoll_wait");
        }

        INFO("return from epoll_wait: nfds=" << nfds << "; channel.size=" << channels_.size());
        for (n = 0; n < nfds; ++n) {
            fromEpollU64(id, fd, events[n].data.u64);
            if (events[n].data.fd == efd_) {
                 INFO("eventfd: fd=" << fd << "; events=" << events[n].events << "; id="<< id);
                 bool ret = onNotified(value);
                 INFO("read eventfd: ret=" << ret << "; value=" << value);
            } else {
                 evts = getChannelEvents(events[n].events);
                 if (fd < channels_.size()) {
                     INFO("epoll fd=" << fd << "; events=" << events[n].events << "; id="<< id << "; sock_events=" << evts);
                     getListener().onEvents(channels_[fd], evts);
                 } else {
                     INFO("epoll nullptr channel: fd=" << fd << "; channels.size=" << channels_.size());
                 }

            }
        }
    }
}
