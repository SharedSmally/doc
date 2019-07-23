#ifndef LOCKABLE_H
#define LOCKABLE_H

#include <mutex>
#include <shared_mutex>
#include <condition_variable>

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
   defer_lock_t:     do not acquire ownership of the mutex (defer_lock)
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
	NORMAL,
	SHARED,
	RECURSIVE
};
enum LockingType
{
    DEFER_LOCKING,
    TRY_LOCKING,
    ADOPT_LOCKING
};

template <MutexType mt, bool t0>
struct mutex_traits
{
	typedef std::mutex mutex_type;
};
template <bool any>
struct cv_traits
{
	typedef std::condition_variable cv_type;
};
template < LockingType E >
struct lock_traits
{
    typedef std::defer_lock_t locking_type;
    static const locking_type & locking_;
};

template <MutexType mt, bool t0>
class Lockable
{
public:
	typedef typename mutex_traits<mt, t0>::mutex_type mutex_type;
	typedef std::lock_guard<mutex_type> guard_type;
	typedef std::unique_lock<mutex_type> unique_locker;
	typedef std::shared_lock<mutex_type> shared_locker;
#ifdef CXX_17
	typedef std::scoped_lock<mutex_type> scoped_locker;
#else
    typedef std::unique_lock<mutex_type> scoped_locker;
#endif
	Lockable() : mutex_() {}

protected:
	//volatile mutex_type  mutex_;
	mutable mutex_type  mutex_;
};

template <MutexType mt, bool t0, bool any>
class Monitorable : public Lockable<mt, t0>
{
public:
	typedef typename cv_traits<any>::cv_type cv_type;

protected:
	cv_type cv_;
};

template <typename T, MutexType mt, bool t0>
class LockObject : public Lockable<mt, t0>
{
public:
	typedef T type;

protected:
	T  value_;
};

template <typename T, MutexType mt, bool t0, bool any>
class MonitorObject : public Monitorable<mt, t0, any>
{
public:
	typedef T type;

protected:
	T  value_;
};


///////////////// specialized
template < >
struct mutex_traits <MutexType::NORMAL, false>
{
	typedef std::mutex mutex_type;
};
template < >
struct mutex_traits <MutexType::NORMAL, true>
{
	typedef std::timed_mutex mutex_type;
};

template < >
struct mutex_traits <MutexType::SHARED, false>
{
#ifdef CXX_17
	typedef std::shared_mutex mutex_type;
#else
	typedef std::mutex mutex_type;
#endif
};
template < >
struct mutex_traits <MutexType::SHARED, true>
{
	typedef std::shared_timed_mutex mutex_type;
};

template < >
struct mutex_traits <MutexType::RECURSIVE, false>
{
	typedef std::recursive_mutex mutex_type;
};
template < >
struct mutex_traits <MutexType::RECURSIVE, true>
{
	typedef std::recursive_timed_mutex mutex_type;
};

template < >
struct lock_traits<DEFER_LOCKING>
{
    typedef std::defer_lock_t locking_type;
    static const locking_type & locking_;
};
template < >
struct lock_traits<TRY_LOCKING>
{
    typedef std::try_to_lock_t locking_type;
    static const locking_type & locking_;
};
template <  >
struct lock_traits<ADOPT_LOCKING>
{
    typedef std::adopt_lock_t locking_type;
    static const locking_type & locking_;
};

template < >
struct cv_traits <false>
{
	typedef std::condition_variable cv_type;
};

template < >
struct cv_traits <true>
{
	typedef std::condition_variable_any cv_type;
};

// lockable
typedef Lockable<MutexType::NORMAL, false>  Lock;
typedef Lockable<MutexType::NORMAL, true> T0Lock;

typedef Lockable<MutexType::SHARED, false>  SLock;
typedef Lockable<MutexType::SHARED, true> T0SLock;

typedef Lockable<MutexType::RECURSIVE, false>  RLock;
typedef Lockable<MutexType::RECURSIVE, true> T0RLock;


// conditional_variable_any
typedef Monitorable<MutexType::NORMAL, false, true>  MonitorAny;
typedef Monitorable<MutexType::NORMAL, true, true> T0MonitorAny;

typedef Monitorable<MutexType::SHARED, false, true>  SMonitorAny;
typedef Monitorable<MutexType::SHARED, true, true> T0SMonitorAny;

typedef Monitorable<MutexType::RECURSIVE, false, true>  RMonitorAny;
typedef Monitorable<MutexType::RECURSIVE, true, true> T0RMonitorAny;

// conditional_variable
typedef Monitorable<MutexType::NORMAL, false, false>  Monitor;
typedef Monitorable<MutexType::NORMAL, true, false> T0Monitor;

typedef Monitorable<MutexType::SHARED, false, false>  SMonitor;
typedef Monitorable<MutexType::SHARED, true, false> T0SMonitor;

typedef Monitorable<MutexType::RECURSIVE, false, false>  RMonitor;
typedef Monitorable<MutexType::RECURSIVE, true, false> T0RMonitor;


/////////////////////////////////////////////////////////////////////


#ifndef SLOCKER
#define SLOCKER locker_type slocker(mutex());
#endif

#ifndef LOCKER
#define LOCKER(T,obj)  T::locker_type locker((obj).mutex());
#endif


#endif

