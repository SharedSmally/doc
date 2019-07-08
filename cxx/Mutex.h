#ifndef CPW_MUTEX_H
#define CPW_MUTEX_H

#include <mutex>
#include <condition_variable>

// mutex. timed_mutex
// shared_mutex. shared_timed_mutex
// recursive_mutex. recursive_timed_mutex
enum MutexEnum
{
	MUTEX,
	RECURSIVE_MUTEX,
	SHARED_MUTEX
};

template <MutexEnum mutexEnum, bool timed>
struct MutexType
{
	typedef std::mutex mutex_type;
};

template <>
struct MutexType<MutexEnum::MUTEX, false>
{
	typedef std::mutex mutex_type;
};
template <>
struct MutexType<MutexEnum::MUTEX, true>
{
	typedef std::timed_mutex mutex_type;
};

template <>
struct MutexType<MutexEnum::RECURSIVE_MUTEX, false>
{
	typedef std::recursive_mutex mutex_type;
};
template <>
struct MutexType<MutexEnum::RECURSIVE_MUTEX, true>
{
	typedef std::recursive_timed_mutex mutex_type;
};

#ifdef CXX_17
template <>
struct MutexType<MutexEnum::SHARED_MUTEX, false>
{
	typedef std::shared_mutex mutex_type;
};
template <>
struct MutexType<MutexEnum::SHARED_MUTEX, true>
{
	typedef std::shared_timed_mutex mutex_type;
};
#endif

#ifdef CXX_14
template <>
struct MutexType<MutexEnum::SHARED_MUTEX, true>
{
	typedef std::shared_timed_mutex mutex_type;
};
#endif

template <MutexEnum mutexEnum, bool timed>
class Lockable
{
public:
	typedef typename MutexType<mutexEnum, timed>::mutex_type mutex_type;
	typedef std::lock_guard<mutex_type> Guarder;
	typedef std::unique_lock<mutex_type> Locker;
#ifdef CXX_17
	typedef std::scoped_lock<mutex_type> Scoper;
	typedef std::shared_lock<mutex_type> ShareLocker;
#endif
#ifdef CXX_14
	typedef std::shared_lock<mutex_type> ShareLocker;
#endif

	mutex_type & mutex() { return mutex_; }

protected:
	mutex_type mutex_;
};

typedef Lockable<MUTEX, false> Mutexable;
typedef Lockable<MUTEX, true>  MutexableT0;

typedef Lockable<RECURSIVE_MUTEX, false> RMutexable;
typedef Lockable<RECURSIVE_MUTEX, true>  RMutexableT0;

typedef Lockable<SHARED_MUTEX, false> SMutexable;
typedef Lockable<SHARED_MUTEX, true>  SMutexableT0;


class Monitor : public Mutexable
{
public:
	void notify()
	{
		cv_.notify_one();
	}
	void notifyAll()
	{
		cv_.notify_all();
	}

	template< typename Predicate >
	void wait(Predicate pred )
	{
		Mutexable::Locker locker(mutex());
		cv_.wait(locker, pred);
	}

	template< class Lock, class Rep, class Period >
	std::cv_status waitFor(const std::chrono::duration<Rep, Period>& rel_time)
	{
		Mutexable::Locker locker(mutex());
		return cv_.wait_for(locker, rel_time);
	}

	template< class Lock, class Rep, class Period, class Predicate >
	bool waitFor( const std::chrono::duration<Rep, Period>& rel_time, Predicate pred)
	{
		Mutexable::Locker locker(mutex());
		return cv_.wait_for(locker, rel_time, pred);
	}

	template< class Clock, class Duration >
	std::cv_status waitUntil(const std::chrono::time_point<Clock, Duration>& timeout_time)
	{
		Mutexable::Locker locker(mutex());
		return wait_until(locker, timeout_time );
	}

	template< class Lock, class Clock, class Duration, class Pred >
	bool waitUntil( const std::chrono::time_point<Clock, Duration>& timeout_time, Pred pred )
	{
		Mutexable::Locker locker(mutex());
		return wait_until(locker, timeout_time, pred );
	}

protected:
	std::condition_variable cv_;
};

//condition_variable_any: generalized condition_variable
//semaphore: shared n resources; (mutex: 1 shared resource)
//queue: producer-consumer patter queue.

#endif
