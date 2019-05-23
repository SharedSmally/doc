#ifndef MULTIPLEXER_H
#define MULTIPLEXER_H

#include <vector>
#include <deque>
#include <thread>
#include <mutex>
#include <condition_variable>

#include <FdObj.h>

#ifndef INFO
//#define INFO(msg) std::cout << msg << std::endl;
#define INFO(msg)
#endif

#ifndef INFO1
#define INFO1(msg) std::cout << msg << std::endl;
//#define INFO(msg)
#endif

class Multiplexer {

public:
    typedef std::mutex mutex_type;
    typedef std::lock_guard<mutex_type> locker_type; // cannot unlock
    typedef std::unique_lock<mutex_type> unilocker_type; // can unlock
    //typedefstd::scoped_lock<mutex_type> locker_type; // multi-mutexs

    enum State {
        INIT,
        RUNNING,
        STOPPING,
        STOPPED
    };

    const static int numCPUS;
    Multiplexer();
    virtual ~Multiplexer();

    virtual void start(int numMonitor = numCPUS, int numIO = numCPUS);
    void stop();

    virtual bool add(FdObjPtr & ptr) = 0;
    virtual bool remove(FdObjPtr & ptr) = 0;
    virtual IOEventsHandler & getHandler() = 0;

protected:
    //dissociate/associate from monitoring;
    bool notify(); //notify new set of fds to be minitored
    bool wakeup();

    virtual bool addNotify(bool addit=false) = 0;
    virtual bool monitor(FdObjPtr & ptr) = 0;

    virtual void monitorTask() = 0; // one or more threads to monitor fds
    virtual void ioTask();  // one or more threads to read/write

protected:
    bool running_;
    int notifyfd_;
    mutex_type mtx_;
    std::condition_variable cv_;

    State state_;

    std::vector<std::thread> ioThreads_;
    std::vector<std::thread> monitorThreads_;

    //fds includes one notify fd, such as eventfd, pipe,...
    //to indicate that contents of fds_ changed
    typedef std::vector<FdObjPtr> container_type;
    container_type container_;  // fd=>fdObj; managed fdObj

    typedef std::deque<FdObjPtr> iotasks_type;
    iotasks_type iotasks_;
};

#endif /* end of MULTIPLEXER_H */

