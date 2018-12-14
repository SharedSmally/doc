## [c++ Mutex](http://en.cppreference.com/w/cpp/concept/Mutex)
## [c++ thread](http://en.cppreference.com/w/cpp/thread)
C++11 has the following mutexes: (for: duration: until: time_point)
- [std::mutex](http://en.cppreference.com/w/cpp/thread/mutex):
     - lock/try_lock/unlock
- [std::recursive_mutex](http://en.cppreference.com/w/cpp/thread/recursive_mutex):
     - lock/try_lock/unlock
- [std::timed_mutex](http://en.cppreference.com/w/cpp/thread/timed_mutex):
     - lock/try_lock/try_lock_for/try_lock_until/unlock
- [std::recursive_timed_mutex](http://en.cppreference.com/w/cpp/thread/recursive_timed_mutex):
     - lock/try_lock/try_lock_for/try_lock_until/unlock
- [std::shared_mutex](http://en.cppreference.com/w/cpp/thread/shared_mutex): c++17
     - lock/try_lock/unlock; 
     - lock_shared/try_lock_shared/unlock_shared:   
- [std::shared_timed_mutex](http://en.cppreference.com/w/cpp/thread/shared_timed_mutex): c++14
     - lock/try_lock/try_lock_for/try_until/unlock;
     - lock_shared/try_lock_shared/try_lock_shared_for/try_lock_shared_until/unlock_shared

```
#include <chrono>
#include <mutex>

mutable std::timed_mutex mutex;
if (mutex.try_lock_for(Ms(100))) {}; 

if (mutex.try_lock_until(now + std::chrono::seconds(10))){};

mutable std::shared_mutex mutex_;

//Multiple threads/readers can read the shared object at the same time, but only one for write: 
std::shared_lock<std::shared_mutex> lock(mutex_);

//Only one thread/writer can write the shared objet at the same time:   
std::unique_lock<std::shared_mutex> lock(mutex_);
```

Scoped lockers:
- [lock_guard](http://en.cppreference.com/w/cpp/thread/lock_guard): implements a strictly scope-based mutex ownership wrapper 
- [unique_lock](http://en.cppreference.com/w/cpp/thread/unique_lock): implements movable mutex ownership wrapper: used for multiple mutexs and with condition variables 
- [scoped_lock](http://en.cppreference.com/w/cpp/thread/scoped_lock): C++17: deadlock-avoiding RAII wrapper for multiple mutexes 
- [shared_lock](http://en.cppreference.com/w/cpp/thread/shared_lock): C++14: implements movable shared mutex ownership wrapper 

C++ 11 Locking strategy
- [locking tag type](https://en.cppreference.com/w/cpp/thread/lock_tag_t):defer_lock_t/- try_to_lock_t/ adopt_lock_t
- [locking tag constants](https://en.cppreference.com/w/cpp/thread/lock_tag): defer_lock, try_to_lock, adopt_lock

Generic locking algorithms (c++11 functions)
- [try_lock](https://en.cppreference.com/w/cpp/thread/try_lock)    attempts to obtain ownership of mutexes via repeated calls to try_lock 
- [lock](https://en.cppreference.com/w/cpp/thread/lock)        locks specified mutexes, blocks if any are unavailable 

```
   {
       std::lock_guard<std::mutex> lock(g_i_mutex);
       // g_i_mutex is automatically released when lock goes out of scope
   }    
```

Conditional Variables:
- [condition_variable](http://en.cppreference.com/w/cpp/thread/condition_variable):  provides a condition variable associated with a std::unique_lock 
   - wait/wait_for/wait_until
   - notify_one/notify_all
- [condition_variable_any](http://en.cppreference.com/w/cpp/thread/condition_variable_any): provides a condition variable associated with any lock type 
   - wait/wait_for/wait_until
   - notify_one/notify_all
- [notify_all_at_thread_exit](): schedules a call to notify_all to be invoked when this thread is completely finished 
  
```
std::mutex m;
std::condition_variable cv;
std::string data;
bool ready = false;
bool processed = false;

void worker_thread()
{
    // Wait until main() sends data
    std::unique_lock<std::mutex> lk(m);
    cv.wait(lk, []{return ready;});
 
    // after the wait, we own the lock.
    std::cout << "Worker thread is processing data\n";
    data += " after processing";
 
    // Send data back to main()
    processed = true;
    std::cout << "Worker thread signals data processing completed\n";
 
    // Manual unlocking is done before notifying, to avoid waking up
    // the waiting thread only to block again (see notify_one for details)
    lk.unlock();
    cv.notify_one();
}
```
