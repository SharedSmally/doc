#ifndef EXECUTOR_H
#define EXECUTOR_H

#include <vector>

#include <memory>

#include <chrono>
#include <thread>

#include <unistd.h>
#include <sys/eventfd.h>

#include <Runnable.h>

class Executor
{
public:
	virtual ~Executor() {}
	virtual void execute(RunnablePtr task) = 0;
};

// running in the calling thread, blocked till task completed.
class BlockExecutor : public Executor
{
public:
	virtual ~BlockExecutor() {}
	virtual void execute(RunnablePtr task)
	{
	        task->run();
	}
};

// each task is running in one thread,
class ThreadExecutor : public Executor
{
public:
	virtual ~ThreadExecutor() {}
	virtual void execute(RunnablePtr task)
	{
	    std::thread t([ task ] { //copied if not using & task
	        task->run();
	    });

	    t.detach();
	}
};

// each task is running in one thread,
class MThreadExecutor : public Executor
{
public:
	virtual ~MThreadExecutor() {}
	virtual void execute(RunnablePtr task)
	{
	    threads_.emplace_back([ task ] { //copied if not using & task
	        task->run();
	    });
	}

	// blocked till all threads are done
	void wait()
	{
		for (auto iter = threads_.begin() ; iter != threads_.end(); ++iter)
			iter->join();
	}

protected:
	std::vector<std::thread> threads_;
};

// Task is queued, and running in the threadpool,
class ThreadPoolExecutor : public Executor
{
public:
	virtual ~ThreadPoolExecutor() {}
	virtual void execute(RunnablePtr task)
	{

	}

//
};

// using Linux eventfd
//#include <sys/eventfd.h>
//int eventfd(unsigned int initval, int flags);
// read/write/close poll/select/epoll
// Each successful read returns an 8-byte integer
//
class EventfdExecutor : public Executor
{
public:
	EventfdExecutor()
	{
		fd_ = eventfd(0, EFD_CLOEXEC | EFD_NONBLOCK);
	}
	virtual ~EventfdExecutor() {
		if (fd_ >=0)  close(fd_);
	}
	virtual void execute(RunnablePtr task)
	{

	}

protected:
	int fd_;
};

//semaphore-like behavior to read from the new file descriptor
class SemaphoreExecutor : public Executor
{
public:
	SemaphoreExecutor(unsigned int initval = 0)
	{
		fd_ = eventfd(initval, EFD_CLOEXEC | EFD_NONBLOCK | EFD_SEMAPHORE);
		if (fd_ < 0)  //error
		{

		}
	}
	virtual ~SemaphoreExecutor()
	{
		if (fd_ >=0)  close(fd_);
	}
	virtual void execute(RunnablePtr task)
	{

	}

protected:
	int fd_;
};




#endif
