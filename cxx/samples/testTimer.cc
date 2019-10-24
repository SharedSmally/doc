#include <thread>
#include <chrono>
#include <iostream>
using namespace std;

#include <sys/select.h>

class TimerThread
{
public:
	TimerThread(uint32_t interval)
	: interval_(interval), running_(false)
	{};
	virtual ~TimerThread(){};

	bool start()
	{
		if (running_) return false;
		running_ = true;
		th_=std::thread([&]{ run(); });
		return true;
	}

	void stop()
	{
		if (!running_) return;

		running_ = false;
		th_.join();
	}

protected:
	virtual void run()
	{
		uint32_t d0 = interval_;
		while (running_)
		{
			//std::chrono::nanoseconds/microseconds/milliseconds/seconds
			auto start = std::chrono::high_resolution_clock::now();
			if (d0 > 0)
				std::this_thread::sleep_for (std::chrono::milliseconds(d0));

			_doTask();

			auto end = std::chrono::high_resolution_clock::now();
			std::chrono::duration<double, std::milli> d1 = end - start;
			d0 = d1.count();
			if (d0 == interval_) continue;
			d0 = (d0 > interval_) ? 0 : interval_ - d0;
		}
	}
	virtual void _doTask() = 0;

protected:
	bool running_;
	uint32_t interval_; //interval in ms

	std::thread th_;
};

class MyTimerThread : public TimerThread
{
public:
	MyTimerThread(uint32_t interval)
	: TimerThread(interval)
	{};
	virtual ~MyTimerThread(){};

protected:
	virtual void _doTask()
	{
		std::cout << "Hello MyTimerThread: fdsize=" << FD_SETSIZE << std::endl;
	}
	// Instead of a single fd_set object, allocate an array of them large enough
	// to hold the max fd you'll need, then use
	// FD_SET(fd%FD_SETSIZE, &fds_array[fd/FD_SETSIZE]) to access the set.
};

void test1()
{
    std::cout << "Hello waiter\n" << std::flush;
    auto start = std::chrono::high_resolution_clock::now();
    std::this_thread::sleep_for(std::chrono::seconds(2));
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> elapsed = end-start;
    std::cout << "Waited " << elapsed.count() << " ms\n";
}

int main()
{
	//test1();
	MyTimerThread timer(4000);
	timer.start();
	std::this_thread::sleep_for (std::chrono::seconds(20));
	timer.stop();
}
