#ifndef CPW_NET_EPOLLMUX_H
#define CPW_NET_EPOLLMUX_H

#include <Multiplexer.h>

class EpollMux : public Multiplexer

{
public:
    const static int MAX_EVENTS;
    EpollMux(ChannelListener & listener, uint32_t initSize=1024) ;
    virtual ~EpollMux();

protected:
    virtual void _run();
    virtual bool _join(ChannelPtr & channel, bool modify);
    virtual bool _leave(ChannelPtr & channel);

    // channel events to epoll events
    uint32_t getEpollEvents(ChannelPtr & channel);
    // epoll events to channel events
    uint32_t getChannelEvents(uint32_t events);

    // conversion between epoll.data.u64 and id + fd
    uint64_t toEpollU64(Channel::id_type id, uint32_t fd);
    void fromEpollU64(Channel::id_type & id, uint32_t & fd, uint64_t evtu64);

protected:
    int epollfd_;
};

#endif
