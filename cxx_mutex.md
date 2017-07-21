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
- [std::shared_mutex](): c++17
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

//Multiple threads/readers can read the shared object at the same time: 
std::shared_lock<std::shared_mutex> lock(mutex_);

//Only one thread/writer can write the shared objet at the same time:   
std::unique_lock<std::shared_mutex> lock(mutex_);
```

Scoped lockers:
- lock_guard: implements a strictly scope-based mutex ownership wrapper 
- unique_lock: implements movable mutex ownership wrapper: used with condition variables 
- scoped_lock: C++17: deadlock-avoiding RAII wrapper for multiple mutexes 
- shared_lock: C++14: implements movable shared mutex ownership wrapper 
```
   {
       std::lock_guard<std::mutex> lock(g_i_mutex);
       // g_i_mutex is automatically released when lock goes out of scope
   }    
```
