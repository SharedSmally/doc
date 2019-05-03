## [ future<T> ](https://en.cppreference.com/w/cpp/thread/future)
Provides a mechanism to access the result of asynchronous operations.  std::future references shared state that is not shared with any other asynchronous return objects (as opposed to std::shared_future)

### object: Not support copy constructor
```
future() noexcept;

future( future&& other ) noexcept;
future& operator=( future&& other ) noexcept;

future( const future& other ) = delete;
future& operator=( const future& other ) = delete;

template< class Function, class... Args>
std::future<std::result_of_t<std::decay_t<Function>(std::decay_t<Args>...)>>
    async( Function&& f, Args&&... args );
    
template< class R, class ...Args > 
std::future<R> std::packaged_task get_future();

template< class R > 
std::future<R>  promise<R>::get_future();
```

### operation
```
future& operator=( future&& other ) noexcept;
std::shared_future<T> share() noexcept;

T get(); 	(member only of generic future template)
T& get();	(member only of future<T&> template specialization)
void get();	(member only of future<void> template specialization)

bool valid() const noexcept;
void wait() const;  Blocks until the result becomes available
template< class Rep, class Period >
std::future_status wait_for( const std::chrono::duration<Rep,Period>& timeout_duration ) const;
template< class Clock, class Duration >
std::future_status wait_until( const std::chrono::time_point<Clock,Duration>& timeout_time )
```
## shared_future
The same operations except supporting copy constructor:
```
shared_future() noexcept;
shared_future( const shared_future& other );
shared_future( const shared_future& other ) noexcept;
shared_future( std::future<T>&& other ) noexcept;
shared_future( shared_future&& other ) noexcept;

shared_future& operator=( const shared_future& other );
shared_future& operator=( const shared_future& other ) noexcept;
shared_future& operator=( shared_future&& other ) noexcept;
```
Could be created from future. 

## packaeg_task

## promise

## async

