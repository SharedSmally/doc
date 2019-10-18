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

protected:
    int epollfd_;
};

#endif
