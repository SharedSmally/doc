#ifndef LOCKABLE_H
#define LOCKABLE_H

#include <mutex>
// #include <shared_mutex>

/*
mutex types: (C++11)
   mutex    provides basic mutual exclusion facility
   timed_mutex

   recursive_mutex:  provides mutual exclusion facility which can be locked recursively by the same thread
   recursive_timed_mutex

   shared_mutex: provides shared mutual exclusion facility  (C++17)
   shared_timed_mutex (C++14)

Generic mutex management: All are class template
   lock_guard: implements a strictly scope-based mutex ownership wrapper
   scoped_lock: deadlock-avoiding RAII wrapper for multiple mutexes (C++17)
   unique_lock:implements movable mutex ownership wrapper
   shared_lock:implements movable shared mutex ownership wrapper (C++14)

locking strategy for lock_guard, scoped_lock, unique_lock, and shared_lock.
   defer_lock_t: 	do not acquire ownership of the mutex (defer_lock)
   try_to_lock_t:  try to acquire ownership of the mutex without blocking ( (try_to_lock))
   adopt_lock_t:   assume the calling thread already has ownership of the mutex (adopt_lock)

Generic locking functions
   try_lock: attempts to obtain ownership of mutexes via repeated calls to try_lock
   lock:  locks specified mutexes, blocks if any are unavailable

Conditional variables
   condition_variable: provides a condition variable associated with a std::unique_lock
   condition_variable_any:  provides a condition variable associated with any lock type
   notify_all_at_thread_exit: schedules a call to notify_all to be invoked when this thread is completely finished
*/

enum MutexType
{
	MUTEX,
	MUTEXT0,
	RECURSIVE_MUTEX,
	RECURSIVE_MUTEXT0,
	READ_WRITE_MUTEX,
	READ_WRITE_MUTEXT0
};

template <typename MutexType = MUTEX >
class Lockable
{
public:
	typedef std::mutex mutex_type;
	typedef std::lock_guard<mutex_type> locker_type;

	Lockable()
	{}
	virtual ~Lockable()
	{}

	mutex_type & mutex() { return mutex_; }

protected:
	mutex_type mutex_;
};

template <>
class Lockable<MUTEXT0>
{
public:
	typedef std::timed_mutex mutex_type;
	typedef std::lock_guard<mutex_type> locker_type;

	Lockable()
	{}
	virtual ~Lockable()
	{}

	mutex_type & mutex() { return mutex_; }

protected:
	mutex_type mutex_;
};

#endif
