# Promise - Future/Shared_Future
- Promise: set the value in the future
- Future: get the value from Promise one time, blocked if not ready
- Shared Future: can call get() multiple times

Sample: https://stackoverflow.com/questions/12086622/is-there-a-way-to-cancel-detach-a-future-in-c11
```
#include <chrono>
#include <future>
#include <iostream>

using namespace std;

int long_running_task(int target, const std::atomic_bool& cancelled)
{
    // simulate a long running task for target*100ms, 
    // the task should check for cancelled often enough!
    while(target-- && !cancelled)
        this_thread::sleep_for(chrono::milliseconds(100));
    // return results to the future or raise an error 
    // in case of cancellation
    return cancelled ? 1 : 0;
}

int main()
{
    std::atomic_bool cancellation_token = ATOMIC_VAR_INIT(false);
    auto task_10_seconds= async(launch::async, 
                                long_running_task, 
                                100, 
                                std::ref(cancellation_token));
    auto task_500_milliseconds = async(launch::async, 
                                       long_running_task, 
                                       5, 
                                       std::ref(cancellation_token));
// do something else (should allow short task 
// to finish while the long task will be cancelled)
    this_thread::sleep_for(chrono::seconds(1));
// cancel
    cancellation_token = true;
// wait for cancellation/results
    cout << task_10_seconds.get() << " " 
         << task_500_milliseconds.get() << endl;
}
```
Using promise/future
```
template <typename RESULT_TYPE, typename FUNCTION_TYPE>
std::future<RESULT_TYPE> startDetachedFuture(FUNCTION_TYPE func) {
    std::promise<RESULT_TYPE> pro;
    std::future<RESULT_TYPE> fut = pro.get_future();

    std::thread([func](std::promise<RESULT_TYPE> p){p.set_value(func());},
                std::move(pro)).detach();

    return fut;
}

int main(int argc, char ** argv) {
    auto returner = []{fprintf(stderr, "I LIVE!\n"); sleep(10); return 123;};

    std::future<int> myFuture = startDetachedFuture<int, decltype(returner)>(returner);
    sleep(1);
}
```
