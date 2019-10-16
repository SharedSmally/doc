#ifndef CHANNEL_H
#define CHANNEL_H

#include <bitset>
#include <atomic>
#include <memory>

//bitset for IO events:
class IOEvents {

};

class Channel {
public:
	typedef uint32_t id_type;

	Channel() : id_(idCnt_++)
  {};
	virtual ~Channel() {}
	virtual int fd() = 0;

	id_type id() { return id_;}
	id_type id() const { return id_;}

protected:
	id_type id_;
	static std::atomic<id_type> idCnt_;
};
typedef std::shared_ptr<Channel> ChannelPtr;


class ChannelListener
{
public:
	ChannelListener() {};
	virtual ~ChannelListener() {}
	virtual int onEvents(ChannelPtr channel, uint32_t) = 0;

	virtual int onRead(ChannelPtr channel) = 0;
	virtual int onWrite(ChannelPtr channel) = 0;
	virtual int onHup(ChannelPtr channel) = 0;
	virtual int onError(ChannelPtr channel) = 0;
};

#endif
