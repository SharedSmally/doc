# Flux: 0..m
Create the Flux, define the operators, and finally subscribe the consumer to start the flow:
```
Flux<Integer> flux = Flux.just(1, 2, 3, 4);

flux.log()
    .subscribe(new Subscriber<Integer>() {
    @Override
    public void onSubscribe(Subscription s) {
      s.request(Long.MAX_VALUE);
    }

    @Override
    public void onNext(Integer integer) {
      elements.add(integer);
    }

    @Override
    public void onError(Throwable t) {}

    @Override
    public void onComplete() {}
});
```
- onSubscribe() – This is called when we subscribe to our stream
- request(unbounded) – When we call subscribe, behind the scenes we are creating a Subscription. This subscription requests elements from the stream. In this case, it defaults to unbounded, meaning it requests every single element available
- onNext() – This is called on every single element
- onComplete() – This is called last, after receiving the last element. There's actually an onError() as well, which would be called if there is an exception, but in this case, there isn't

## Backpressure:
The subscriber is telling the producer to push every single element at once. This could end up becoming overwhelming for the subscriber, consuming all of its resources. This is Backpressure when a downstream can tell an upstream to send it less data in order to prevent it from being overwhelmed.
```
Flux.just(1, 2, 3, 4)
  .log()
  .subscribe(new Subscriber<Integer>() {
    private Subscription s;
    int onNextAmount;

    @Override
    public void onSubscribe(Subscription s) {
        this.s = s;
        s.request(2);
    }

    @Override
    public void onNext(Integer integer) {
        elements.add(integer);
        onNextAmount++;
        if (onNextAmount % 2 == 0) {
            s.request(2);
        }
    }

    @Override
    public void onError(Throwable t) {}

    @Override
    public void onComplete() {}
});
```
Essentially, this is reactive pull backpressure. We are requesting the upstream to only push a certain amount of elements, and only when we are ready.

## Operating on a Stream
### Mapping Data in a Stream: 
```
Flux.just(1, 2, 3, 4)
  .log()
  .map(i -> i * 2)
  .subscribe(elements::add);
```
applying a transformation: map() will be applied when onNext() is called

### Combining Two Streams
```
Flux.just(1, 2, 3, 4)
  .log()
  .map(i -> i * 2)
  .zipWith(Flux.range(0, Integer.MAX_VALUE), (one, two) -> String.format("First Flux: %d, Second Flux: %d", one, two))
  .subscribe(elements::add);
```

## Hot Streams:
- Cold Streams: static, fixed-length streams 
- Hot Streams: always running and can be subscribed to at any point in time, missing the start of the data.
### Creating a ConnectableFlux
```
ConnectableFlux<Object> publish = Flux.create(fluxSink -> {
    while(true) {
        fluxSink.next(System.currentTimeMillis());
    }
})
  .publish();  // this create a ConnectableFlux.
```
The calling subscribe() won't cause it to start emitting, allowing us to add multiple subscriptions:
```
publish.subscribe(System.out::println);        
publish.subscribe(System.out::println);
```
It's not until we call connect(), that the Flux will start emitting
```
publish.connect();
```

### Throttling
Too much data is being passed to our consumers in the previous code. Use sample() method with an interval of two seconds; or windows/buffer.
```
ConnectableFlux<Object> publish = Flux.create(fluxSink -> {
    while(true) {
        fluxSink.next(System.currentTimeMillis());
    }
})
  .sample(ofSeconds(2))
  .publish();
```
### Concurrency
The code currently run on the main thread. We can control which thread our code runs on if we want. The Scheduler interface provides an abstraction around asynchronous code on another thread:
```
Flux.just(1, 2, 3, 4)
  .log()
  .map(i -> i * 2)
  .subscribeOn(Schedulers.parallel())  //cause subscription to be run on a different thread
  .subscribe(elements::add);
```
