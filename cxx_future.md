# C++ async


## (future header)[https://en.cppreference.com/w/cpp/header/future]
- (promise<T>)[https://en.cppreference.com/w/cpp/thread/promise]
   - promise();
   - get_future: returns a future associated with the promised result 
   - set_value/set_value_at_thread_exit: sets the result to specific value 
   - set_exception/set_exception_at_thread_exit: sets the result to indicate an exception 
   
- (future<T>)(https://en.cppreference.com/w/cpp/thread/future)
   - promise.get_future()
   - get(): 	returns the result 
   - wait/wait_for/wait_until() methods

- (shared_future)(https://en.cppreference.com/w/cpp/thread/shared_future)
   - generated from future.share()


## (promise header)[]

