#include <Runnable.h>

// interface
class Executor
{
public:
     virtual ~Executor(){}
     virtual bool execute(RunnablePtr & task) = 0;
};


/////////////////////////////  impl
class ProxyExecutor : public Executor
{
public:
    ProxyExecutor(Executor & executor)
    : executor_(executor)
    {}
    virtual ~ProxyExecutor() {}

    virtual bool execute(RunnablePtr & task);

protected:
     Executor & executor_;
};


// each task runs as a separated thread
class ThreadExecutor : public Executor
{
public:
    ThreadExecutor()     {}
    virtual ~ThreadExecutor() {}
    virtual bool execute(RunnablePtr & task);
};


// each task runs as a separated thread
class ThreadPoolExecutor : public Executor
{
public:
    ThreadPoolExecutor(uint32_t numThreads = std::thread::hardware_concurrency());
    virtual ~ThreadPoolExecutor();
    virtual bool execute(RunnablePtr & task);

protected:
    void run();
    void stop();

protected:
    bool running_;
    std::vector<std::thread> threads_;

    std::mutex mtx_;
    std::condition_variable cv_;
    std::deque<RunnablePtr> tasks_;
};


#endif
