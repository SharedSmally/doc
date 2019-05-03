## [ future<T> ](https://en.cppreference.com/w/cpp/thread/future)
Provides a mechanism to access the result of asynchronous operations.  std::future references shared state that is not shared with any other asynchronous return objects (as opposed to std::shared_future)

- object: Not support copy constructor
```
Defined in header <future>

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
### operations
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
## [shared_future](https://en.cppreference.com/w/cpp/thread/shared_future)
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

## [packaeg_task](https://en.cppreference.com/w/cpp/thread/packaged_task)
Defined in header <future>.
Wraps any Callable target (function, lambda expression, bind expression, or another function object) so that it can be invoked asynchronously.
    
```
template< class > class packaged_task; //not defined
template< class R, class ...Args > 
class packaged_task<R(Args...)>;
```
- constructor
```
packaged_task() noexcept;

template <class F>
explicit packaged_task( F&& f );

template <class F, class Allocator>
explicit packaged_task( std::allocator_arg_t, const Allocator& a, F&& f );

packaged_task( packaged_task&& rhs ) noexcept;
packaged_task& operator=( packaged_task&& rhs ) noexcept;
    
packaged_task( const packaged_task& ) = delete;    
packaged_task& operator=( const packaged_task& ) = delete;

void swap( packaged_task& other ) noexcept;
```

- execution
```
void operator()( ArgTypes... args );
void make_ready_at_thread_exit( ArgTypes... args );
void reset();
```

## promise
Provides a facility to store a value or an exception that is later acquired asynchronously via a std::future object created by the std::promise object. std::promise object is meant to be used only once.

- constructor
```
promise();
template< class Alloc >
promise( std::allocator_arg_t, const Alloc& alloc );
promise( promise&& other ) noexcept;
promise& operator=( promise&& other ) noexcept;

promise& operator=( const promise& rhs ) = delete;
promise( const promise& other ) = delete;

void swap( promise& other ) noexcept;
```

- operaions
```
std::future<T> get_future();

void set_value( const R& value );   (member only of generic promise template)
void set_value( R&& value );	(member only of generic promise template)
void set_value( R& value ); (member only of promise<R&> template specialization)
void set_value();	(member only of promise<void> template specialization)

void set_value_at_thread_exit( const R& value );   (member only of generic promise template)
void set_value_at_thread_exit( R&& value );	(member only of generic promise template)
void set_value_at_thread_exit( R& value ); (member only of promise<R&> template specialization)
void set_value_at_thread_exit();	(member only of promise<void> template specialization)

void set_exception( std::exception_ptr p );
void set_exception_at_thread_exit( std::exception_ptr p );
```

## async
The template function async runs the function f asynchronously (potentially in a separate thread which may be part of a thread pool) and returns a std::future that will eventually hold the result of that function call
```
template< class Function, class... Args>
std::future<std::result_of_t<std::decay_t<Function>(std::decay_t<Args>...)>>
    async( Function&& f, Args&&... args );

template< class Function, class... Args>
std::future<std::invoke_result_t<std::decay_t<Function>, std::decay_t<Args>...>>
    async( Function&& f, Args&&... args );

template< class Function, class... Args>
std::future<std::invoke_result_t<std::decay_t<Function>, std::decay_t<Args>...>>
    async( Function&& f, Args&&... args );

template< class Function, class... Args >
std::future<std::result_of_t<std::decay_t<Function>(std::decay_t<Args>...)>>
    async( std::launch policy, Function&& f, Args&&... args );

template< class Function, class... Args >
std::future<std::invoke_result_t<std::decay_t<Function>, std::decay_t<Args>...>>
    async( std::launch policy, Function&& f, Args&&... args );

template< class Function, class... Args >
std::future<std::invoke_result_t<std::decay_t<Function>, std::decay_t<Args>...>>
    async( std::launch policy, Function&& f, Args&&... args );
```
