#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <functional>
#include <chrono>
#include <future>
#include <queue>
#include <thread>
#include <memory>
#include <mutex>

#include <iostream>

static std::string toString(const std::chrono::system_clock::time_point& tp)
{
    std::time_t t = std::chrono::system_clock::to_time_t(tp);
    std::string ts = std::ctime(&t);
    ts.resize(ts.size()-1);
    return ts;
}

struct Timer
{
    std::function<void()> func;
    std::chrono::system_clock::time_point time;

    Timer()
    { }

    Timer(std::function<void()>&& f, std::chrono::system_clock::time_point & t)
        : func(f), time(t)
    { }

    // priority_queue is ordered in terms of smallest time to largest
    bool operator<(const Timer& rhs) const
    {
        return time > rhs.time;
    }

    void run()
    {
        func();
    }
};

class Scheduler
{


public:
    Scheduler()
        :running_(true),
        thread(new std::thread([this]() { ThreadLoop(); }))
    { }

    ~Scheduler()
    {
        running_ = false;
        thread->join();
    }

    void ThreadLoop()
    {
        while(running_)
        {
            auto now = std::chrono::system_clock::now();
            {
            	std::cout << "Main now="<< toString(now) << "\n";

            	std::unique_lock<std::mutex> lock(mutex_);
            	while(!tasks.empty() && tasks.top().time <= now) {
            		Timer & f = const_cast<Timer &>(tasks.top());
            		tasks.pop();
            		std::cout << "timeout="<< toString(f.time) << "\n";
            		f.run();
            	}

            	if(tasks.empty()) {
            		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            	} else {
            		std::cout << " waiting till " << toString(tasks.top().time) << "\n";
            		timeoutChanged_.wait_until(lock, tasks.top().time);
            	}
            }
        }
    }

    void schedule(std::chrono::system_clock::time_point& time, std::function<void()>&& func)
    {
    	if (time < std::chrono::system_clock::now()) {
    		func(); return;
        }

        if (tasks.empty()) {
            tasks.push(Timer(std::move(func), time));
        } else {
        	if (time < tasks.top().time) {
        		tasks.push(Timer(std::move(func), time));
        		timeoutChanged_.notify_one();
        	} else {
        		tasks.push(Timer(std::move(func), time));
        	}
        }
    }

    void scheduleInterval(std::chrono::system_clock::duration interval, std::function<void()> func)
    {
        std::function<void()> waitFunc = [this,interval,func]()
        {
             func();
             this->scheduleInterval(interval, func);
        };

        auto timeout = std::chrono::system_clock::now() + interval;
        schedule(timeout, std::move(waitFunc));
    }

private:
    bool running_;
    std::priority_queue<Timer> tasks;
    std::unique_ptr<std::thread> thread;

    std::mutex mutex_;
    std::condition_variable timeoutChanged_;

private:
    Scheduler(const Scheduler& rhs) = delete;
    Scheduler& operator=(const Scheduler& rhs) = delete;
};

#ifdef TEST

void test2()
{
    Scheduler sch;

    auto now = std::chrono::system_clock::now();

    std::cout << "test2 !\n now is " << toString(now) << std::endl;
    auto t15=now + std::chrono::seconds(15); sch.schedule(t15, []{ Task2(); });
    auto t25=now + std::chrono::seconds(25); sch.schedule(t25, []{ Task2(); });
    auto t20=now + std::chrono::seconds(20); sch.schedule(t20, []{ Task2(); });
    auto t2=now + std::chrono::seconds( 2);  sch.schedule(t2,  []{ Task2(); });

    getchar();

}

int main()
{
	test2();
}
#endif

#endif

