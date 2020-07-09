# Objects

## Thread / ThreadPool

## Future<T> : Executor : ExecutorService
- bool execute(TaskablePtr task); 
Concrete implementations:
- SyncExecutor: run in current thread
- ThreadExecutor: run in a separated thread
- ThreadPoolExecutor: run in a thread pool
- ProxyExecutor: run in proxy executor

## ScheduledFuture<T> : Scheduler : SchedulerService
- bool schedule(const Time & time, TaskablePtr task); 
- bool schedule(TimerPtr timer); // Scheduler interface
Concrete implementations:
- SyncExecutor: scheduler in current thread with its own executor
- ThreadPoolScheduler: scheduler in current thread with its external executor
- ThreadScheduler: run in a separated thread, which waits and then run
- ProxyScheduler: scheduler in proxy executor
- CronScheduler: use system cron to scheduler the task.

## DataObject
```
template <KEY, DATA>
DataObject {
public:
    DataObject(const DataObject & obj) 
       : key_(obj.key_),data_(obj.data_)
    { }    
    DataObject(const KEY && key, const DATA && data) 
       : key_(key),data_(data)
    { }      
    template< typename... Args>
    DataObject(Args... & args) 
       : key_(args...),data_()
    { }
   ~DataObject(){}
   
   const KEY & key() const{ return key_; }   
   DATA & data() { return data_; }
   const DATA & data() const{ return data_; }

protected:
   KEY key_;
   DATA data_;
};
```

## SyncObject

- bool wait() //throws InterruptedException
- bool wait(const ) //throws InterruptedException
- void notify()
- void notifyAll()

## Manager<KEY, DATA>

## TreeNode

## Context

## parameter pack
See for [parameter pack](https://en.cppreference.com/w/cpp/language/parameter_pack).
```
// recursive variadic function
template<typename T, typename... Args>
void func(T t, Args... args) {
    std::cout << t <<std::endl ;
    func(args...) ;
}

//Using reference:
template<class Fun, class... Args>
void foo(Fun f, Args&&... args)
{
    f( std::forward<Args>(args)...);
}
```
