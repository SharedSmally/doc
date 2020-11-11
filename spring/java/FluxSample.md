# Flux Samples

- [Cold vs Hot Publisher](http://www.vinsguru.com/reactive-programming-publisher-types-cold-vs-hot/)
There are two types of Publishers in Reactor, Cold Publisher and Hot Publisher. 

A Publisher is called Cold if it generates data anew for each subscription. If no subscription is created,
data never gets generated. But, each new subscription will get the whole data from the beginning. 

Hot publishers do not depend on any number of subscribers. They might start publishing data right away and would 
continue doing so whenever a new Subscriber comes in (the subscriber would see only new elements emitted after it subscribed)

Hot Publishers (Broadcast) do not create new data producer for each new subscription (as the Cold Publisher does).
Instead there will be only one data producer and all the observers listen to the data produced by the 
single data producer. So all the observers get the same data.

Every publisher starts off as Cold, we can call the publish() method on a Cold Publisher to make it Hot. Once publish is called, 
you get a ConnectableFlux<T> as a return value of the publisher. when publish() is called, you subscribe to this 
connectableFlux(publisher in this case) and not to the original Flux to get the Hot Publishing in action. With this, 
same publisher can now be subscribed and it will emit only new data after the subscription. But here, you have to use 
connect() to kick off the whole chain which makes sense, because for HotPublishers we have to tell it when it should 
start publishing data. 
```
public void exampleColdPublisher() throws InterruptedException {
    // Start a cold Publisher which emits 0,1,2 every sec.
    Flux<Long> flux =  Flux.interval(Duration.ofSeconds(1));
    // Let's subscribe to that with multiple subscribers.
    flux.subscribe(i -> System.out.println("first_subscriber received value:" + i));
    Thread.sleep(3_000);
    // Let a second subscriber come after some time 3 secs here.
    flux.subscribe(i -> System.out.println("second_subscriber received value:" + i));
}

public void exampleHotPublisher() throws InterruptedException {
    // Start a cold Publisher which emits 0,1,2 every sec.
    Flux<Long> flux =  Flux.interval(Duration.ofSeconds(1));
    // Make the Publisher Hot
    ConnectableFlux<Long> connectableFlux = flux.publish();
    // Now that we have a handle on the hot Publisher
    // Let's subscribe to that with multiple subscribers.
    connectableFlux.subscribe(i -> System.out.println("first_subscriber received value:" + i));
    // Start firing events with .connect() on the published flux.
    connectableFlux.connect();
    Thread.sleep(3_000);
    // Let a second subscriber come after some time 3 secs here.
    connectableFlux.subscribe(i -> System.out.println("second_subscriber received value:" + i));
}
```

- Schedulers (Concurrency Abstraction)
In Reactor, the execution model and where the execution happens is determined by the Scheduler that is used and Publisher chain is completely agnostic of that. A Scheduler has scheduling responsibilities similar to an ExecutorService, but having a dedicated abstraction lets it do more, notably acting as a clock and enabling a wider range of implementations (virtual time for tests, trampolining or immediate scheduling, and so on).
The Schedulers helper class has static factory methods that give access to the many types execution contexts easily:
     - Schedulers.immediate() — Does not spin any thread, the submitted Runnable will be directly executed, effectively running them on the current Thread
     - Schedulers.single() — A single, reusable thread will be spawned, used mostly for low risk, maintenance kind of workload. If you want a per-call dedicated thread, use Schedulers.newSingle() for each call.
     - Schedulers.parallel() — A fixed pool of workers that is tuned for parallel work (Mostly CPU bound), It creates as many workers as you have CPU cores.
     - Schedulers.elastic() — An unbounded elastic thread pool. This one is no longer preferred with the introduction of Schedulers.boundedElastic(), as it has a tendency to hide backPressure problems and lead to too many threads (see below). This is mostly used for I/O intensive operations.
     - Schedulers.boundedElastic() — Like its predecessor elastic(), it creates new worker pools as needed and reuses idle ones. Worker pools that stay idle for too long (the default is 60s) are also disposed. Unlike its elastic() predecessor, it has a cap on the number of backing threads it can create (default is number of CPU cores x 10)
     - Schedulers.fromExecutorService(ExecutorService) — Using this API, you can create a Scheduler out of any pre-existing ExecutorService

- [Reactive Asynchronous Programming](https://levelup.gitconnected.com/reactive-asynchronous-programming-in-java-using-reactor-core-part-2-e9c6caeb8833)
