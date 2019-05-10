#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <set>
#include <mutex>
#include <condition_variable>

#include <iostream>

#include <Time.h>
#include <Executor.h>

std::string toString( const Time & time) {
    std::time_t t = Clock::to_time_t(time);
    std::string ts = std::ctime(&t);
    ts.resize(ts.size()-1);
    return ts;
}

class Timer : public Runnable
{
public:
	Timer()
	: expireTime_()
	{}
	Timer(const Time & time)
      : expireTime_(time)
    {}
	Timer(Time && time)
      : expireTime_(time)
    {}
	Timer(const Duration & delay)
      : expireTime_(Clock::now() + delay)
    {}
	Timer(Duration && delay)
      : expireTime_(Clock::now() + delay)
    {}
    virtual ~Timer()
    {}
    const Time & expireTime() const
    {
        return expireTime_;
    }
    void expireTime(const Time & time)
    {
        expireTime_ = time;
    }
    virtual void run() {
    	std::cout << "expired time=" << ::toString(expireTime_)
    			  << " in threadid=" << std::this_thread::get_id() << std::endl;
    };

protected:
    Time expireTime_;
};
typedef std::shared_ptr< Timer> TimerPtr;


bool timerCompare(const Timer & lhs, const Timer &rhs)
{
    return lhs.expireTime() < rhs.expireTime();
}
//set<Timer, timerCompare> s;
//std::set<int, decltype(&timerCompare)> s(&timerCompare);

struct TimerComparer {
    bool operator() (const Timer& lhs, const Timer& rhs) const
    {
        return lhs.expireTime() < rhs.expireTime();
    }
};
/*
//set<Timer, TimerComparer> s;
template < >
struct std::less < Timer> {
    bool operator() (const Timer& lhs, const Timer& rhs) const
    {
         std::cout << "std::less<Timer>" << std::endl;
        return lhs.expireTime() < rhs.expireTime();
    }
};
template < >
struct std::less < TimerPtr > {
    bool operator() (const TimerPtr & lhs, const TimerPtr & rhs) const
    {
         std::cout << "std::less<TimerPtr>" << std::endl;
        return lhs->expireTime() < rhs->expireTime();
    }
};
*/
struct TimerPtrComparer {
    bool operator() (const TimerPtr & lhs, const TimerPtr & rhs) const
    {
        return lhs->expireTime() < rhs->expireTime();
    }
};

class TaskTimer : public Timer
{
public:
	TaskTimer(RunnablePtr & task, const Duration & delay)
	: Timer(delay), task_(task)
	{}
	virtual ~TaskTimer()
	{}
	virtual void run()
	{
		task_->run();
	}

protected:
	RunnablePtr task_;
};

class Scheduler
{
public:
    virtual ~Scheduler() {}
    virtual bool schedule(TimerPtr & timer) = 0;
    virtual bool schedule(RunnablePtr & task, const Duration & delay)
    {
    	std::shared_ptr<Timer> timer = std::static_pointer_cast<Timer>(std::make_shared<TaskTimer> (task, delay ));
    	return schedule(timer);
    }
    //virtual bool schedule(RunnablePtr & task, const Time & delay, const Time & period) = 0;

protected:
};

//One thread to handle order of timer
class SchedulerThread : public Scheduler
{
public:
	SchedulerThread (Executor & executor)
     : running_(true), updated_(false),
	   executor_(executor),
	   th_([&]{ run(); })
    {}
    virtual ~SchedulerThread()
    {
    	stop();
    	th_.join();
    }

	virtual bool schedule(TimerPtr & timer)
	{
		std::unique_lock<std::mutex> lk(mtx_);
		if (container_.empty())
		{
			updated_ = true;
		}
		else
		{
			updated_ = timer->expireTime() < (*(container_.begin()))->expireTime() ;
		}
		container_.insert(timer);
		if (updated_) cv_.notify_one();

		return true;
	}

	virtual bool schedule(TimerPtr && timer)
	{
		std::unique_lock<std::mutex> lk(mtx_);
		if (container_.empty())
		{
			updated_ = true;
		}
		else
		{
			updated_ = timer->expireTime() < (*(container_.begin()))->expireTime() ;
		}

		container_.insert(timer);
		if (updated_) cv_.notify_one();

		return true;
	}

	void stop() {
		running_ = false;
		cv_.notify_one();
	}

protected:
	void run()
	{
		TimerPtr current = std::make_shared<Timer>();

		while (running_) {
			std::deque<TimerPtr> tasks;
			{
				std::unique_lock<std::mutex> lk(mtx_);
				updated_ = false;

				if (container_.empty()) {
					cv_.wait(lk, [=]{return !running_ || updated_;});
				} else {
					cv_.wait_until(lk, (*(container_.begin()))->expireTime(),  [=]{return !running_ || updated_;});
				}

				if (!running_) break;

				if (container_.empty()) continue;

				Time current(Clock::now());
				while (!container_.empty()) {
					if ( current < (*(container_.begin()))->expireTime() )
						break;

					tasks.push_back( *(container_.begin()) );
					container_.erase(container_.begin());
				}
			}

			while (!tasks.empty())
			{
				RunnablePtr task = std::static_pointer_cast<Runnable>(tasks.front());
				tasks.pop_front();
				executor_.execute( task );
			}
		}
	}

protected:
	bool running_;
	bool updated_;

	std::thread th_;
    Executor & executor_;
    std::set<TimerPtr, TimerPtrComparer> container_;

    std::mutex mtx_;
    std::condition_variable cv_;
};

#endif

/*
#include <Scheduler.h>

#include <iostream>
using namespace std;

int main()
{
	ThreadExecutor executor;
	SchedulerThread scheduler(executor);

	scheduler.schedule( std::make_shared<Timer>( Duration(2000) ) );
	scheduler.schedule( std::make_shared<Timer>( Duration(1000) ) );

	/*
	scheduler.schedule( std::make_shared<Timer>( Duration(200)  ) );
	scheduler.schedule( std::make_shared<Timer>( Duration(500)  ) );
	scheduler.schedule( std::make_shared<Timer>( Duration(5000) ) );
   */

    std::this_thread::sleep_for (std::chrono::seconds(10));
}
*/

