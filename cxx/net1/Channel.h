#ifndef CPW_NET_CHANNEL_H
#define CPW_NET_CHANNEL_H

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
    static bool isWritable(int events){ return (events & OUT_EVENT) == OUT_EVENT; }
    static bool isHup(int events)      { return (events & HUP_EVENT) == HUP_EVENT; }
    static bool isError(int events)    { return (events & ERROR_EVENT) == ERROR_EVENT; }

public:
    typedef uint32_t id_type;

    Channel()
     : id_(++idCnt_), events_(ALL_EVENTS),
       server_(false)
    {}
    virtual ~Channel() {}
    virtual int fd() = 0;

    id_type id() { return id_;}
    id_type id() const { return id_;}

    void events(uint32_t e) { events_=e; }
    uint32_t events() const { return events_; }

    void server(bool v) { server_=v;}
    bool server() const { return server_;}

protected:
    id_type id_;
    bool server_;
    uint32_t events_; // events to be monitored

    static std::atomic<id_type> idCnt_;
};
typedef std::shared_ptr<Channel> ChannelPtr;

class ChannelListener
{
public:
    virtual ~ChannelListener() {}
    virtual int onEvents(ChannelPtr & channel, uint32_t events) {
        if (Channel::isError(events)) { return _onError(channel); }
        if (Channel::isHup(events)) { return _onError(channel); }
        int retRD(0), retWR(0);
        if (Channel::isReadable(events)) { retRD=_onRead(channel,false);}
        if (Channel::isPrioReadable(events)) { retRD=_onRead(channel, true);}
        if (Channel::isWritable(events)) { retWR=_onWrite(channel);}
        return retRD + retWR;
    }

protected:
    virtual int _onRead(ChannelPtr & channel, bool prio) = 0;
    virtual int _onWrite(ChannelPtr & channel) = 0;
    virtual int _onHup(ChannelPtr & channel) = 0;
    virtual int _onError(ChannelPtr & channel) = 0;
};

class Acceptor
{
public:
    virtual ~Acceptor() {}
    virtual bool onAccept(ChannelPtr & svcChannel, ChannelPtr conn) = 0;
};

class Connector
{
public:
    virtual ~Connector() {}
    virtual void onConnected(ChannelPtr & channel) = 0;
};

/////////////////////////////////////////////////////////////////
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

#endif
