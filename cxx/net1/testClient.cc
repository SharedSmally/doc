#include <Utils.h>
#include <Macro.h>
#include <EpollMux.h>

#include <iostream>
using namespace std;

#include <unistd.h>

class MyChannelListener : public ChannelListener
{
	typedef IPv4Address addr_type;
    typedef ChannelObj<ClientSocket<addr_type> > ClientChannel;
    typedef std::shared_ptr<ClientChannel> ClientChannelPtr;

public:
	MyChannelListener(const IPv4Address & svcAddr)
	: svcAddr_(svcAddr), mtx_(nullptr) {}
    virtual ~MyChannelListener() {}
    void setMultiplexer(Multiplexer & mtx) {
        mtx_ = &mtx;
    }
protected:
    virtual int _onRead(ChannelPtr & channel, bool prio)
    {
    	if (channel) {
    		INFO("MyChannelListener onRead: id="<<channel->id());
			ClientChannelPtr ptr = std::dynamic_pointer_cast<ClientChannel>(channel);
			if (!ptr->sock().isConnected()) {
				INFO("MyChannelListener onRead: connected to server");
				ptr->sock().setConnected(true);
				mtx_->manage(channel);
				Buffer msg("hello from client");
				ptr->sock().send(msg);
				mtx_->manage(channel);
			} else {
				char msg[10]; memset(msg, '\0',10);
				ptr->sock().recv(msg, 10);
				INFO("**Recv msg:" << msg);
				mtx_->manage(channel);
			}
    	} else {
    		INFO("MyChannelListener onRead: channel is null");
    	}
    }
    virtual int _onWrite(ChannelPtr & channel)
    {
    	if (channel) {
    		Buffer msg("hello from client");
    		INFO("MyChannelListener _onWrite: id="<<channel->id());
    		sleep(5);
    		ClientChannelPtr ptr = std::dynamic_pointer_cast<ClientChannel>(channel);
    		ptr->sock().send(msg);
    		mtx_->manage(channel);
    	} else {
    		INFO("MyChannelListener _onWrite: channel is null");
    	}
    }
    virtual int _onHup(ChannelPtr & channel)
    {
    	if (channel) {
    		INFO("MyChannelListener _onHup: id="<<channel->id());
    		mtx_->unmanage(channel);
    	} else {
    		INFO("MyChannelListener _onHup: channel is null");
    	}
    }
    virtual int _onError(ChannelPtr & channel)
    {
    	if (channel) {
    		INFO("MyChannelListener _onError: id="<<channel->id());
    		mtx_->unmanage(channel);
    	} else {
    		INFO("MyChannelListener _onError: channel is null");
    	}
    }

protected:
    IPv4Address svcAddr_;
    Multiplexer * mtx_;
};

int main()
{
    IPv4Address addr("127.0.0.1"); // no port
    IPv4Address svrAddr("127.0.0.1", 9999);
    auto channel = clientChannel(addr, svrAddr);

    INFO("clientApp: server addr="<<svrAddr <<"; fd=" << channel->fd());
    MyChannelListener listener(addr);

    EpollMux epoll(listener);
    listener.setMultiplexer(epoll);
    epoll.start();
    epoll.manage(channel);
    sleep(20);
    epoll.stop();
}
