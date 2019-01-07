#ifndef LOCKABLE_H
#define LOCKABLE_H

#include <mutex>

#ifdef CXX_17
    #include  <shared_mutex>
#else
    #ifdef CXX_14
        #include  <shared_mutex>
    #endif
#endif

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
    MUTEX,
    MUTEXT0,
    RECURSIVE_MUTEX,
    RECURSIVE_MUTEXT0,
    SHARED_MUTEX,
    SHARED_MUTEXT0
};

template < MutexType E >
struct MutexTraits
{
    typedef std::mutex mutex_type;
};

template < >
struct MutexTraits <MUTEXT0>
{
    typedef std::timed_mutex mutex_type;
};

template < >
struct MutexTraits < RECURSIVE_MUTEX >
{
    typedef std::recursive_mutex mutex_type;
};
template < >
struct MutexTraits < RECURSIVE_MUTEXT0 >
{
    typedef std::recursive_timed_mutex mutex_type;
};

#ifdef CXX_14
template < >
struct MutexTraits < SHARED_MUTEXT0 >
{
    typedef std::shared_timed_mutex mutex_type;
};
#endif

#ifdef CXX_17
template < >
struct MutexTraits < SHARED_MUTEX >
{
    typedef std::shared_mutex mutex_type;
};
#endif

enum LockingType
{
    DEFER_LOCKING,
    TRY_LOCKING,
    ADOPT_LOCKING
};

template < LockingType E >
struct LockingTraits
{
    typedef std::defer_lock_t locking_type;
    static const locking_type & locking_;
};
template < >
struct LockingTraits<DEFER_LOCKING>
{
    typedef std::defer_lock_t locking_type;
    static const locking_type & locking_;
};
template < >
struct LockingTraits<TRY_LOCKING>
{
    typedef std::try_to_lock_t locking_type;
    static const locking_type & locking_;
};
template <  >
struct LockingTraits<ADOPT_LOCKING>
{
    typedef std::adopt_lock_t locking_type;
    static const locking_type & locking_;
};


template <MutexType E = MUTEX, LockingType L = DEFER_LOCKING >
class Lockable
{
public:
    typedef typename MutexTraits<E>::mutex_type mutex_type;
    typedef typename LockingTraits<L>::locking_type locking_type;

    typedef std::lock_guard<mutex_type> locker_type;
    typedef std::unique_lock<mutex_type> unique_locker;

#ifdef CXX_17
    typedef std::scoped_lock<mutex_type, locking_type> scoped_locker;
#else
    typedef std::unique_lock<mutex_type> scoped_locker;
#endif

#ifdef CXX_17
    typedef std::shared_lock<mutex_type> shared_locker;
#else
    #ifdef CXX_14
        typedef std::shared_lock<mutex_type> shared_locker;
    #else
        typedef std::unique_lock<mutex_type> shared_locker;
    #endif
#endif

    Lockable()
    {}
    virtual ~Lockable()
    {}

    mutex_type & mutex() { return mutex_; }
    const mutex_type & mutex() const { return mutex_; }

protected:
    mutable mutex_type mutex_;
};

template <typename T, MutexType E = MUTEX, LockingType L = DEFER_LOCKING >
class LockableObject : public T, virtual public Lockable<E, L>
{
public:
	LockableObject(){}
	virtual ~LockableObject(){};
};

///////////////////////////////////////////
typedef Lockable<> DefaultLockable;

typedef Lockable<MUTEX>   MLockable;
typedef Lockable<MUTEXT0> M0Lockable;

typedef Lockable<RECURSIVE_MUTEX>   RLockable;
typedef Lockable<RECURSIVE_MUTEXT0> R0Lockable;

typedef Lockable<SHARED_MUTEX>   SLockable;
typedef Lockable<SHARED_MUTEXT0> S0Lockable;


#ifndef SLOCKER
#define SLOCKER locker_type slocker(mutex());
#endif

#ifndef LOCKER
#define LOCKER(T,obj)  T::locker_type locker((obj).mutex());
#endif

#endif

