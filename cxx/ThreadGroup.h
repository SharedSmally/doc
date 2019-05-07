#ifndef THREADGROUP_H
#define THREADGROUP_H

#include <thread>
#include <mutex>

#include <vector>

class ThreadGroup
{
public:
	enum State
	{
		INIT,
		RUNNING,
		STOPPING,
		STOPPED
	};

	ThreadGroup()
	    : state_(INIT), stopped_(false)
	{
	}
	virtual ~ThreadGroup()
	{
		for (auto & th : threads_)
			th.join();
		threads_.clear();
	}

	ThreadGroup::State state()
	{
		return state_;
	}

	void stop()
	{
		state_ = STOPPING;
		std::unique_lock<std::mutex> lck(mtx_);
		stopped_ = true;
		state_ = STOPPED;
	}

protected:
	virtual void run() = 0;

	bool start(uint32_t numThreads = std::thread::hardware_concurrency() )
	{
		std::unique_lock<std::mutex> lck(mtx_);
		switch (state_)
		{
		case INIT:
			threads_.reserve(numThreads);
			for (int i=0; i<numThreads; ++i)
			{
				threads_.emplace_back( [=] { run(); } );
				//std::thread(&ThreadGroup::run, this);
				//std::thread( [this] { this->run(); } );
				//std::thread( [this] { run(); } )
				//std::thread( [=] { run(); } );
			}
			state_ = RUNNING;
			return true;

		case RUNNING:
			return true;

		default:
			return false;
		}
	}

protected:
	bool stopped_;
	ThreadGroup::State state_;

	std::mutex mtx_;
	std::vector<std::thread> threads_;
};

#ifdef TEST
#include <chrono>
#include <sstream>
#include <iostream>
using namespace std;

class MyThreadGroup : public ThreadGroup
{
public:
	MyThreadGroup(int num)
	{
		start(num);
	}

	virtual ~MyThreadGroup()
	{
		stop();
	}

protected:
	virtual void run()
	{
		std::ostringstream oss;
		int cnt(0);
		while (!stopped_)
		{
			++cnt;
			oss << " start to run MyThreadGroup: id=" << std::this_thread::get_id() <<"; cnt=" << cnt << "; thread Size=" << threads_.size();
			std::cout << oss.str() << std::endl; oss.clear(); oss.str("");
			std::this_thread::sleep_for (std::chrono::seconds(1));
			oss << " finish running MyThreadGroup: id=" << std::this_thread::get_id() <<"; cnt=" << cnt << "; thread Size=" << threads_.size();
			std::cout << oss.str() << std::endl; oss.clear(); oss.str("");
		}
	}
};

int main()
{
	MyThreadGroup group(2);

	std::this_thread::sleep_for (std::chrono::seconds(10));
	group.stop();
	std::this_thread::sleep_for (std::chrono::seconds(5));

}
#endif

#endif
