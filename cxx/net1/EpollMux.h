#ifndef EPOLLMUX_H
#define EPOLLMUX_H

#include <Multiplexer.h>

class EpollMux : public Multiplexer {
public:
	const static int MAX_EVENTS;
	EpollMux(uint32_t initSize=1024) ;
    virtual ~EpollMux();

protected:
	virtual void _run();
	virtual bool _join(ChannelPtr & channel, bool modify);
	virtual bool _leave(ChannelPtr & channel);

	uint32_t getEpollEvents(ChannelPtr & channel);

protected:
	int epollfd_;
};

#endif
