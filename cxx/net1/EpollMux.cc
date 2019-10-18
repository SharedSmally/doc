#include <EpollMux.h>
#include <Macro.h>

#include <unistd.h>
#include <string.h>
#include <sys/epoll.h>

const int EpollMux::MAX_EVENTS(10);

EpollMux::EpollMux(ChannelListener & listener, uint32_t initSize)
  : Multiplexer(listener, initSize)
{
    epollfd_ = epoll_create1(0);

    struct epoll_event ev;
    ev.events = EPOLLIN | EPOLLET;
    ev.data.fd = efd_;
    ev.data.u64 = 0;

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
    ev.data.fd = efd_;

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

void EpollMux::_run()
{
    struct epoll_event events[MAX_EVENTS];
    int nfds(0), n, fd, evts;
    uint64_t value(0), id(0);

    while (running_) {
        nfds = epoll_wait(epollfd_, events, MAX_EVENTS, -1);
        if (nfds == -1) {
            // error
        }

        INFO("return from epoll_wait: nfds=" << nfds << "; channel.size=" << channels_.size());
        for (n = 0; n < nfds; ++n) {
            fd = events[n].data.fd;
            id = events[n].data.u64;
            if (events[n].data.fd == efd_) {
                 INFO("eventfd: fd=" << fd << "; events=" << events[n].events << "; id="<< id);
                 bool ret = onNotified(value);
                 INFO("read eventfd: ret=" << ret << "; value=" << value);
            } else {
                 evts = getChannelEvents(events[n].events);
                 INFO("epoll fd=" << fd << "; events=" << events[n].events << "; id="<< id << "; sock_events=" << evts);
                 if (fd < channels_.size()) {
                     getListener().onEvents(channels_[fd], evts);
                 }
                 //do_use_fd(events[n].data.fd);
            }
        }
    }
}
