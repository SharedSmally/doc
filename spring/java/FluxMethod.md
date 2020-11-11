# Java Flux
- [Flux API doc](https://projectreactor.io/docs/core/release/api/reactor/core/publisher/Flux.html)
- [Tutorial](https://www.codingame.com/playgrounds/929/reactive-programming-with-reactor-3/Flux)


A Flux<T> is a Reactive Streams Publisher, augmented with a lot of operators that can be used to generate, transform, orchestrate Flux sequences.

It can emit 0 to n <T> elements (onNext event) then either completes or errors (onComplete and onError terminal events). If no terminal event is triggered, the Flux is infinite.

- Static factories on Flux allow to create sources, or generate them from several callbacks types.
- Instance methods, the operators, let you build an asynchronous processing pipeline that will produce an asynchronous sequence.
- Each Flux#subscribe() or multicasting operation such as Flux#publish and Flux#publishNext will materialize a dedicated instance of the pipeline and trigger the data flow inside it.


## Create Flux via static methods
```
Flux<Integer> just = Flux.just(1, 2, 3, 4);
Mono<Integer> just = Mono.just(1);

List<Integer> elements = new ArrayList<>();
Flux.just(1, 2, 3, 4).log().subscribe(elements::add);

Flux.just(1, 2, 3, 4).log().subscribe(new Subscriber<Integer>() {
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

Flux.just(1, 2, 3, 4).log().subscribe(new Subscriber<Integer>() {
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

Flux.just(1, 2, 3, 4).log()
    .map(i -> i * 2)
	  .subscribe(elements::add);

Flux.just(1, 2, 3, 4)
	  .log()
	  .map(i -> i * 2)
	  .zipWith(Flux.range(0, Integer.MAX_VALUE), 
	    (one, two) -> String.format("First Flux: %d, Second Flux: %d", one, two))
	  .subscribe(elements::add);
```

## Hot Streams
Cold streams are static, fixed-length streams that are easy to deal with. A more realistic use case for reactive might be something that happens infinitely (Hot Stream). They are always running and can be subscribed to at any point in time, missing the start of the data.

- Creating a ConnectableFlux: converting a cold stream into hot stream
```
ConnectableFlux<Object> publish = Flux.create(fluxSink -> {
	    while(true) {
	        fluxSink.next(System.currentTimeMillis());
	    }
	})
	  .publish();
```
By calling publish() we are given a ConnectableFlux. This means that calling subscribe() won't cause it to start emitting, allowing us to add multiple subscriptions:
```
publish.subscribe(System.out::println);        
publish.subscribe(System.out::println);
```
Nothing will happen when try running this code. It's not until we call connect(), that the Flux will start emitting:
```
	publish.connect();
```  
- Throttling, windowing, buffering
```
ConnectableFlux<Object> publish = Flux.create(fluxSink -> {
	    while(true) {
	        fluxSink.next(System.currentTimeMillis());
	    }
	})
	  .sample(ofSeconds(2)) # values will only be pushed to subscriber every two seconds
	  .publish();
```
- Concurrency
```
Flux.just(1, 2, 3, 4)
	  .log()
	  .map(i -> i * 2)
	  .subscribeOn(Schedulers.parallel())
	  .subscribe(elements::add);
```
Normally they run on the main thread. The Parallel scheduler will cause our subscription to be run on a different thread.

## operators
- map / flatMap
- filter : if
- zip/zipWith:

- buffer

## [Combining Publishers samples](https://www.baeldung.com/reactor-combine-streams)
- concat/concatWith:
- combineLatest()
- merge()/mergeSequential()/mergeDelayError()/mergeWith()
- zip()/zipWith():  
static xxx(flux1, pub2) is similar to flux1.xxxWith(pub2). Flux and Mono are Publisher.
```
Flux<Integer> evenNumbers = Flux.range(min, max).filter(x -> x % 2 == 0); // 2, 4 
Flux<Integer> oddNumbers = Flux.range(min, max).filter(x -> x % 2 > 0);  // 1, 3, 5

Flux<Integer> fluxOfIntegers = Flux.concat(evenNumbers,oddNumbers); //2,4,1,3,5
Flux<Integer> fluxOfIntegers = evenNumbers.concatWith(oddNumbers);  //2,4,1,3,5
	    
Flux<Integer> fluxOfIntegers = Flux.combineLatest(evenNumbers,oddNumbers,(a, b) -> a + b); // 4+1, 4+3, 4+5

Flux<Integer> fluxOfIntegers = Flux.merge(evenNumbers, oddNumbers); //2,4,1,3,5

Flux<Integer> fluxOfIntegers = Flux.merge(evenNumbers.delayElements(Duration.ofMillis(500L)), 
           oddNumbers.delayElements(Duration.ofMillis(300L))); //1,2,3,5,4
Flux<Integer> fluxOfIntegers = Flux.mergeSequential(evenNumbers, oddNumbers); //2.4.1.3.5

Flux<Integer> fluxOfIntegers = Flux.mergeDelayError(1, evenNumbers.delayElements(Duration.ofMillis(500L)), 
	      oddNumbers.delayElements(Duration.ofMillis(300L))); //1,2,3,5,4
        
Flux<Integer> fluxOfIntegers = evenNumbers.mergeWith(oddNumbers);  //2,4,1,3,5

Flux<Integer> fluxOfIntegers = Flux.zip(evenNumbers,oddNumbers,(a, b) -> a + b); //2+1, 4+3
Flux<Integer> fluxOfIntegers = evenNumbers.zipWith(oddNumbers, (a, b) -> a * b); //2*1,4*3
```





