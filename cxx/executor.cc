#include <memory>
#include <chrono>
#include <thread>
#include <unistd.h>
// unsigned int sleep(unsigned int seconds);

#ifndef OPT
#include <sstream>
#include <iostream>
#endif

// Use the preprocessor # operator for the arguments string   //#define STRING(s) #s

#ifndef DEBUG
   #ifndef OPT
      #define DEBUG(msg) { std::ostringstream oss; oss << "[" << getpid() << ":" << std::this_thread::get_id() << "]: " << msg << "\n"; std::cout << oss.str() ; }
   #else
      #define DEBUG (msg)
   #endif
#endif
//D [0x7effcb006700]        SocketChannel.cc -  308 : TCP fd=45 read 0 bytes. Tearing down connection.

class Runnable
{
public:
	virtual ~Runnable() {}
	virtual void run() = 0;
};
typedef std::shared_ptr<Runnable> RunnablePtr;

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


#ifndef OPT

using namespace std;

#define MAX_TIMEOUT 10

class SleepTask : public Runnable
{
public:
	SleepTask(int32_t timeout = 0)
		: timeout_(timeout) {
		if (0 == timeout_)
		{
			long int v0 = random();

			if (v0 & 0x01)
			{
				timeout_ = v0 % 1000000 + 1;
				timeout_ = - timeout_;
			}
			else
			{
				timeout_ = v0 % MAX_TIMEOUT + 1;
			}
		}
	}
	virtual ~SleepTask() {
		DEBUG("Call ~SleepTask()");
	}
	virtual void run() {
	    DEBUG( "Starting thread: timeout=" << timeout_ << " (micro)seconds");
	    std::this_thread::sleep_for(timeout_>0 ? std::chrono::seconds(timeout_) : std::chrono::microseconds(-timeout_) );
	    DEBUG( "Exiting  thread: timeout=" << timeout_ << " (micro)seconds" );
	}

protected:
	int32_t timeout_; // in seconds
};

void test()
{
	{
		RunnablePtr task1 = std::make_shared<SleepTask>(5);
		RunnablePtr task2 = std::make_shared<SleepTask>();

		ThreadExecutor executor;
		executor.execute(task1);
		executor.execute(task2);
	}

	sleep(10);
}

int main()
{
     test();
}
#endif
