#include <Executor.h>

////////////////////////////////////////////////////////
bool ProxyExecutor::execute(RunnablePtr & task)
{
    return executor_.execute(task);
}

////////////////////////////////////////////////////////
bool ThreadExecutor::execute(RunnablePtr & task)
{
    if (!task) return false;

    std::thread th( [task] { task->run(); } );
    th.detach();

    return true;
}

////////////////////////////////////////////////////////
ThreadPoolExecutor::ThreadPoolExecutor(uint32_t numThreads)
  : running_(true)
{
    threads_.reserve(numThreads);
    for (uint32_t i = 0; i<numThreads; ++i)
    	threads_.emplace ( threads_.end(), std::thread([=] { run(); }) );
}

ThreadPoolExecutor::~ThreadPoolExecutor()
{
	stop();

	for (std::thread & th : threads_)
		th.join();
}

bool ThreadPoolExecutor::execute(RunnablePtr & task)
{
	if (!task) return false;

	std::unique_lock<std::mutex> lk(mtx_);
	tasks_.push_back(task);
	cv_.notify_one();
	return true;
}

void ThreadPoolExecutor::run()
{
	 RunnablePtr task;
     while (running_) {
    	 {
    	    // Wait until task is available
    	    std::unique_lock<std::mutex> lk(mtx_);
    	    cv_.wait(lk, [=]{return !running_ || !tasks_.empty();});

    	    if (!running_) return;

    	    if (!tasks_.empty())
    	    {
    	    	task = tasks_.front();
    	    	tasks_.pop_front();
    	    }
    	    else
    	    {
    	    	task = nullptr;
    	    }
         }
    	 if (task) task->run();
     }
}

void ThreadPoolExecutor::stop()
{
	running_ = false;
	cv_.notify_all();
}

/*
// Executor based on BlockingQueue
class QueueExecutor : public Executor
{
public:
    QueueExecutor()
    {}
    virtual ~QueueExecutor()
	{}

    virtual bool execute(RunnablePtr & task)
    {
        return executor_.execute(task);
    }

protected:

};

// Executor based on linux event API
//linux event: https://linux.die.net/man/3/event
//#include <sys/time.h>
//#include <event.h>
class EventExecutor : public Executor
{
public:
    EventExecutor()
    {}
    virtual ~EventExecutor()
	{}

    virtual bool execute(RunnablePtr & task)
    {
        return executor_.execute(task);
    }

protected:

};

// Executor based on linux eventfd API
//http://man7.org/linux/man-pages/man2/eventfd.2.html
#include <sys/eventfd.h>
//int eventfd(unsigned int initval, int flags);
class EventFDExecutor : public Executor
{
public:
    EventFDExecutor(bool semaphore = false) : fd_(-1)
    {
        // 2.6.27:EFD_CLOEXEC | EFD_NONBLOCK
        // 2.6.30: EFD_SEMAPHORE
        int flags = EFD_CLOEXEC | EFD_NONBLOCK;
        if (semaphore)
            flags |= EFD_SEMAPHORE;
        fd_ = eventfd();
    }
    virtual ~EventFDExecutor()
	{
        if (fd_>=0)
           close(fd_);
	}

    //read/write/poll:epoll:select
    virtual bool execute(RunnablePtr & task)
    {
        return executor_.execute(task);
    }

protected:
    int fd_;
};

*/
