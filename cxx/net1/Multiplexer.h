#ifndef CPW_NET_MULTIPLEXER_H
#define CPW_NET_MULTIPLEXER_H

#include <thread>
#include <vector>
#include <mutex>

#include <Channel.h>

class Notifier{
    const static uint64_t ONE;

public:
    Notifier(uint32_t initval=0, bool semaphore=false,
            bool cloexec=true, bool nonblock=true);
    virtual ~Notifier();
    int fd() { return efd_; }
    bool notify();

protected:
    bool onNotified(uint64_t & value);

protected:
    int efd_;
    uint32_t events_;
};

class Multiplexer : public Notifier
{
    const static int STEP_BIT_NUM;
public:
    typedef std::mutex mutex_type;
    typedef std::lock_guard<mutex_type>  guard_type;
    typedef std::unique_lock<mutex_type> lock_type;

    Multiplexer(ChannelListener & listener, uint32_t initSize=1024) ;
    virtual ~Multiplexer() { }

    bool start();
    void stop();
    void join() { if (ioThread_) ioThread_->join(); }
    bool isRunning() const { return running_; }

    template <typename T >
    bool manage(std::shared_ptr<T> & channel)
    {
        ChannelPtr ptr = std::static_pointer_cast<Channel>(channel);
        return manage(ptr);
    }
    template <typename T >
    bool unmanage(std::shared_ptr<T> & channel)
    {
        ChannelPtr ptr = std::static_pointer_cast<Channel>(channel);
        return unmanage(ptr);
    }

    virtual bool manage(ChannelPtr & channel) ;
    virtual bool unmanage(ChannelPtr & channel) ;
    //ChannelListener & getListener() = 0;

protected:
    // one thread to monitor the fds
    virtual void _run() = 0;
    virtual bool _join(ChannelPtr & channel, bool modify) = 0;
    virtual bool _leave(ChannelPtr & channel) =0;

    virtual ChannelListener & getListener()  { return listener_; }

protected:
    mutable mutex_type mtx_;
    volatile bool running_;
    std::vector<ChannelPtr> channels_;
    std::shared_ptr<std::thread> ioThread_;
    ChannelListener & listener_;
};

#endif

