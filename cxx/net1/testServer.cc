#include <Utils.h>
#include <EpollMux.h>

#include <iostream>
using namespace std;

#include <unistd.h>

class MyChannelListener : public ChannelListener
{
public:
	MyChannelListener(const IPv4Address & svcAddr)
	: svcAddr_(svcAddr) {}
    virtual ~MyChannelListener() {}

protected:
    virtual int _onRead(ChannelPtr & channel, bool prio)
    {
    	if (channel) {
    		INFO("MyChannelListener onRead: id="<<channel->id());
    	} else {
    		INFO("MyChannelListener onRead: channel is null");
    	}
    }
    virtual int _onWrite(ChannelPtr & channel)
    {
    	if (channel) {
    		INFO("MyChannelListener _onWrite: id="<<channel->id());
    	} else {
    		INFO("MyChannelListener _onWrite: channel is null");
    	}
    }
    virtual int _onHup(ChannelPtr & channel)
    {
    	if (channel) {
    		INFO("MyChannelListener _onHup: id="<<channel->id());
    	} else {
    		INFO("MyChannelListener _onHup: channel is null");
    	}
    }
    virtual int _onError(ChannelPtr & channel)
    {
    	if (channel) {
    		INFO("MyChannelListener _onError: id="<<channel->id());
    	} else {
    		INFO("MyChannelListener _onError: channel is null");
    	}
    }

protected:
    IPv4Address svcAddr_;
};



int main()
{
    IPv4Address addr("10.32.119.152", 9999);
    auto channel = serverChannel(addr);
    INFO("server addr="<<addr <<"; fd=" << channel->fd());
    MyChannelListener listener(addr);

    EpollMux epoll(listener);
    epoll.start();
    epoll.manage(channel);
    epoll.join();
}
