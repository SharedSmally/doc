#include <Utils.h>
#include <Macro.h>
#include <EpollMux.h>

#include <iostream>
using namespace std;

#include <unistd.h>

class MyChannelListener : public ChannelListener
{
public:
	typedef IPv4Address addr_type;
	MyChannelListener(const addr_type & svcAddr)
	: svcAddr_(svcAddr), mtx_(nullptr) {}
    virtual ~MyChannelListener() {}
    void setMultiplexer(Multiplexer & mtx) {
        mtx_ = &mtx;
    }
    typedef ChannelObj<ServerSocket<addr_type> > ServerChannel;
    typedef ChannelObj<Connection<addr_type> > ConnectionChannel;
    typedef std::shared_ptr<ServerChannel> ServerChannelPtr;
    typedef std::shared_ptr<ConnectionChannel> ConnectionChannelPtr;

protected:
    virtual int _onRead(ChannelPtr & channel, bool prio)
    {
    	if (channel) { //std::shared_ptr<ChannelObj<ServerSocket<ADDR> > >
    		INFO("MyChannelListener onRead: id="<<channel->id()<<"; serverf="<< channel->server());
    		if (channel->server()) {
    			ServerChannelPtr ptr = std::dynamic_pointer_cast<ServerChannel>(channel);
    			ConnectionChannelPtr conn = ::connectChannel<addr_type>(ptr);
    			mtx_->manage(conn);
    		} else {
    			ConnectionChannelPtr ptr = std::dynamic_pointer_cast<ConnectionChannel>(channel);
				char msg[20]; memset(msg, '\0',20);
				ptr->sock().recv(msg, 20);
				INFO("**Recv msg:" << msg);
				mtx_->manage(channel);
    		}
    	} else {
    		INFO("MyChannelListener onRead: channel is null");
    	}
    }
    virtual int _onWrite(ChannelPtr & channel)
    {
    	Buffer msg("hello");
    	if (channel) {
    		INFO("MyChannelListener _onWrite: id="<<channel->id());
    		sleep(5);
    		ConnectionChannelPtr ptr = std::dynamic_pointer_cast<ConnectionChannel>(channel);
    		ptr->sock().send(msg);
    		mtx_->manage(channel);
    		INFO("**Send msg:" << msg);
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
    addr_type svcAddr_;
    Multiplexer * mtx_;
};



int main()
{
    IPv4Address addr("127.0.0.1", 9999);
    auto channel = serverChannel(addr);
    INFO("server addr="<<addr <<"; fd=" << channel->fd());
    MyChannelListener listener(addr);

    EpollMux epoll(listener);
    listener.setMultiplexer(epoll);

    epoll.start();
    epoll.manage(channel);
    epoll.join();
}
