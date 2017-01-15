- IApplication: Application, singleton (parse command line arguments: -n xxx -- XXX )
   - int argc() const;
   - const char ** argv() const const;
   - const char ** env() const const;
   - bool getArgv(xxx & arg, char name) const
   - bool getArgv(xxx & arg, const char * name) const
   - const char * getEnv(xxx & arg, const char * name) const;
   - int retCode() const = 0;
   - virtual void run() = 0;
   - AppContext & getContext() = 0;
- IContext: contains list of objects.
- AppContext:IContext impl for Application
   - IApplication & getApp();
   - Object & find(const std::string & name)
   - start()
   - stop()
- IContainer: contains list of Components
- Container: default impl of IContainer
- IComponent: can be wired each other, and provide list of services.
- Component: default impl of IComponent
- App<CONTEXT>: IApplication
   - CONTEXT context_;
- BundleMgr: manage list of bundle; monitoring list of directories for Bundle
- Bundle: the shared library, contains a list of ComponentFactory.
   - getFilename
   - load
   - unload
   - reload
   - BundleContext getContext()
- BundleContext: Hierarchy context relationship
   - AppContext appContext()
   - BundleContext parent()
   - Component find(String name)   
```cpp
int main(int argc, char ** argv) {  
   //register signal handler to stop app.
   App<Context> app(argc, argv);
   try {
      app.run();
   } catch (...) {
      return EXIT_FAILURE;
   }
   return app.retCode();
}
```
- Runnable: virtual void run();
- ThreadPool: list ot threads to run the task
- Queue<T>: multi-threading Queue
    - enqueue(T)
    - dequeue(T)
- Producer:
    - R produce()
- Consumer
    - void consume(T)
- Processor
    - R process (T )
- Event : Message
    - Object getSource()
    - int getEvents()
    - int getClassId()
- EventListener / MessgeListener
    - onEvent(Event)
    - onMessage(Message(Message)
- EventCallback : MessageCallback
    - onCompleted(Event)
    - onError(Event, Exception)
- EventManager
    - add/removeListener(EventListener)
    - notify(Event): sync
    - void notifyAsync(Event, EventCallback): async
    - Future notifyAsync(Event): async
- Dispatcher
    - add/removeListener(MessageListener)
    - dispatch(Message)
    - dispatchAsync(Message, MessageCallback)
    - Future dispatchAsync(Message)
- Future:
    - hasDone()
    - hasError()
    - waitCompleted()
- Executor
    - executor(Task)
- Scheduler
    - schedule(TimerTask, Time)
