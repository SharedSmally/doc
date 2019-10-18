#ifndef CHANNEL_H
#define CHANNEL_H

#include <bitset>
#include <atomic>
#include <memory>

//bitset for IO events:
class Channel {
public:
	static const int IN_EVENT;
	static const int IN_PRIO_EVENT;
	static const int OUT_EVENT;
	static const int HUP_EVENT;
	static const int ERROR_EVENT;
	static const int ALL_EVENTS;

	static bool isReadable(int events) { return (events & IN_EVENT) == IN_EVENT;  }
	static bool isPrioReadable(int events) { return (events & IN_PRIO_EVENT) == IN_PRIO_EVENT; }
	static bool isWriteable(int events){ return (events & OUT_EVENT) == OUT_EVENT; }
	static bool isHup(int events)      { return (events & HUP_EVENT) == HUP_EVENT; }
	static bool isError(int events)    { return (events & ERROR_EVENT) == ERROR_EVENT; }

public:
	/*
	//state: managed:  ;active: monitored; deactive: managed but not monitored,
	enum ChannelState {
		ADDED,
		ACTIVE,
		DEACTIVE
	};
	ChannelState state_;
	state(ChannelState e) { state_=e; }
	ChannelState state() const { return state_; }
	*/
	typedef uint32_t id_type;

	Channel() : id_(idCnt_++)
	{}
	virtual ~Channel() {}
	virtual int fd() = 0;

	id_type id() { return id_;}
	id_type id() const { return id_;}

	void events(uint32_t e) { events_=e; }
	uint32_t events() const { return events_; }


protected:
	id_type id_;
	uint32_t events_; // events to be monitored


	static std::atomic<id_type> idCnt_;
};
typedef std::shared_ptr<Channel> ChannelPtr;


template <typename SOCK>
class ChannelObj : public Channel
{
public:
	template <typename ...Args>
	ChannelObj(Args... args)
	: sock_(args...)
	{}

	virtual int fd() { return sock_.fd(); }
	SOCK & sock() { return sock_; }

protected:
	SOCK sock_;
};

class ChannelListener
{
public:
	ChannelListener() {};
	virtual ~ChannelListener() {}
	virtual int onEvents(ChannelPtr channel, uint32_t events) = 0;

	virtual int onRead(ChannelPtr channel) = 0;
	virtual int onWrite(ChannelPtr channel) = 0;
	virtual int onHup(ChannelPtr channel) = 0;
	virtual int onError(ChannelPtr channel) = 0;
};

#endif
