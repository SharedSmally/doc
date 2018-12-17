#ifndef QUEUE_H
#define QUEUE_H

#include <queue>

#include <Lockable.h>

template <typename T >
class Queue : public Lockable<MUTEX, DEFER_LOCKING>
{
public:
	//using Lockable<MUTEX, DEFER_LOCKING>::mutex_;

	typedef T value_type;
	typedef std::queue<T> container_type;
	typedef typename container_type::size_type size_type;

	Queue(uint32_t maxSize = -1)
	: maxSize_(maxSize) {}
	~Queue() {
		SLOCKER;
		std::queue<T> empty;
		std::swap( container_, empty );
	}

	// immediate operations
	bool pushNow( const value_type& value )
	{
		SLOCKER;
		if (container_.size()>maxSize_)
		{
			return false;
		}
		else
		{
			container_.push_back(value);
			return true;
		}
	}
	bool popNow( value_type& value )
	{
		SLOCKER;
		if (container_.empty())
		{
			return false;
		}
		else
		{
			value = container_.front();
			container_.push_front();
			return true;
		}
	}

	// blocking operations
	bool push( const value_type& value )
	{
        {
            std::unique_lock<std::mutex> lock(mutex());
            notFull_.wait(lock, [=]{ return this->container_.size() <  this->maxSize_; });
            container_.push(value);
        }
        notEmpty_.notify_one();
	}

	bool pop( value_type& value )
	{
        {
            std::unique_lock<std::mutex> lock(mutex());
            notEmpty_.wait(lock, [=]{ return !this->container_.empty(); });

            //T rc(std::move(container_.front()));
            value = container_.front();
            container_.pop();
        }

        notFull_.notify_one();
	}

	bool empty()
	{
		SLOCKER;
		return container_.empty();
	}
	size_type size( )
	{
		SLOCKER;
		return container_.size();
	}
	void notify(bool all = true)
	{
		if (all) {
			notFull_.notify_all();
			notEmpty_.notify_all();
		} else {
			notFull_.notify_one();
			notEmpty_.notify_one();
		}
	}

private:
	Queue(const Queue & );
	Queue & operator=(const Queue & );

protected:
	uint32_t maxSize_;
	container_type container_;
	std::condition_variable notFull_, notEmpty_;
};

/*
template <typename T >
class Queue<T *>
   : public Lockable<MUTEX, DEFER_LOCKING>
{
public:
	typedef std::shared_ptr<T> value_type;

	Queue(uint32_t maxSize = -1)
	: maxSize_(maxSize) {}
	~Queue() {
		container_.clear();
	}

	//return
	bool push( const value_type& value )
	{

	}

	bool pop( value_type& value )
	{

	}

protected:
	std::queue<T> container_;
	uint32_t maxSize_;
};
*/
#endif
