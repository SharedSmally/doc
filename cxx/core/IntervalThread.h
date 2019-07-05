#ifndef INTERVALTHREAD_H
#define INTERVALTHREAD_H

#include <thread>
#include <chrono>

#include <mutex>
#include <condition_variable>

#include <iostream>

class IntervalThread
{
public:
	typedef std::chrono::system_clock Clock; //duration: ns
	//typedef std::chrono::steady_clock Clock;
	typedef std::chrono::milliseconds Duration;
	typedef std::chrono::time_point<Clock> Time;
	typedef std::lock_guard<std::mutex> Guarder;
	typedef std::unique_lock<std::mutex> Locker;

	IntervalThread(uint32_t duration)
	    : running_(false)
	{
		interval_ = Duration(duration);
	}

	virtual ~IntervalThread() {}
	bool start()
	{
		Guarder guard(mutex_);
		if (running_) return true;
		thread_ = std::thread([this]{ run(); });
		thread_.detach();
		startTime_ = Clock::now();
		running_ = true;
		return running_;
	}
	void stop()
	{
		Guarder guard(mutex_);
		if (!running_) return;
		cv_.notify_one();
		running_ = false;
	}

	const Time & startTime() const { return startTime_; }
	const Duration & interval() const { return interval_; }
	void interval(uint32_t duration )
	{
		Guarder guard(mutex_);
		interval_ = Duration(duration);
	}

	bool running() const
	{
		return running_;
	}

protected:
	void run()
	{
		std::cout << "Thread starts\n";
		while (running_)
		{
			{
				Locker lk(mutex_);
			    if(cv_.wait_for(lk, interval_, [this] { return !running_;})) {
			        std::cout << "Thread finished waiting. running_=" << running_ << '\n';
			    } else {
			    	std::cout << "Thread timed out. running = " <<  running_ << '\n';
			    	task(); // may modify interval
			    }
			}
		}
		std::cout << "Thread completed\n";
	}

	virtual void task() = 0;

protected:
	bool running_;
	std::thread thread_;
	Time startTime_;
	Duration interval_;

	std::mutex mutex_;
	std::condition_variable cv_;
};

#endif

/*
#include <Interval.h>
#include <iostream>
#include <iomanip>
#include <ctime>
using namespace std;

class MyInterval : public IntervalThread
{
public:
	MyInterval(uint32_t duration = 1)
		: IntervalThread(duration)
	{
	}
	virtual ~MyInterval(){};

protected:
	virtual void task()
	{
		std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
		std::time_t now_c = std::chrono::system_clock::to_time_t(now);
		std::cout << "MyInterval::run @time= "
		          << std::put_time(std::localtime(&now_c), "%F %T") << '\n';
	}
};

int main()
{
	MyInterval thread(500);
	thread.start();
	std::this_thread::sleep_for(3s);
	thread.stop();
}
*/
