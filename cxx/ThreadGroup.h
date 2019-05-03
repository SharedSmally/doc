#define ThreadGroup_H

#include <thread>
#include <mutex>

#include <vector>

class ThreadGroup
{
public:
	static enum State
	{
		INIT,
		RUNNING,
		STOPPING,
		STOPPED
	};

	ThreadGroup()
	    : state_(INIT)
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
		std::unique_lock<std::mutex> lck(mtx_);
		stopped_ = true;
	}

protected:
	virtual void run() = 0;

	bool start(uint32_t numThreads)
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

#endif
