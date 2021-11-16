# Java Flow
The useful implementation is reactive: Similar to callback, Publisher pushes the data to the subscribers.

# [Flow](https://docs.oracle.com/javase/9/docs/api/java/util/concurrent/Flow.html) 
in java.util.concurrent
- Flow.Subscription

| Method |	Description |
|--------|--------------|
|static interface Flow.Processor<T,R> | A component that acts as both a Subscriber and Publisher.|
|static interface  	Flow.Publisher<T> | A producer of items (and related control messages) received by Subscribers.|
|static interface  	Flow.Subscriber<T> | A receiver of messages.|
|static interface  	Flow.Subscription  | Message control linking a Flow.Publisher and Flow.Subscriber.|

- Flow.Publisher:  public static interface Flow.Processor<T,R> extends Flow.Subscriber<T>, Flow.Publisher<R>

| Method |	Description |
|--------|--------------|
| void subscribe(Flow.Subscriber<? super T> subscriber) | Adds the given Subscriber if possible.|
  
- Flow.Subscriber

| Method |	Description |
|--------|--------------|
|void onComplete() |Method invoked when it is known that no additional Subscriber method invocations will occur for a Subscription that is not already terminated by error, after which no other Subscriber methods are invoked by the Subscription.
|void onError(Throwable throwable) | Method invoked upon an unrecoverable error encountered by a Publisher or Subscription, after which no other Subscriber methods are invoked by the Subscription.|
|void onNext(T item) 	|Method invoked with a Subscription's next item.|
|void onSubscribe(Flow.Subscription subscription) 	| Method invoked prior to invoking any other Subscriber methods for the given Subscription.|
  
- Flow.Processor
public static interface Flow.Processor<T,R> extends Flow.Subscriber<T>, Flow.Publisher<R>
  
- Flow.Subscription

| Method |	Description |
|--------|--------------|
|void cancel() |	Causes the Subscriber to (eventually) stop receiving messages. |
|void request(long n) |	Adds the given number n of items to the current unfulfilled demand for this subscription.|

- Consumer<T>
| Method |	Description |
|--------|--------------|
|void 	accept(T t)|Performs this operation on the given argument.|
|default Consumer<T> 	andThen(Consumer<? super T> after)|Returns a composed Consumer that performs, in sequence, this operation followed by the after operation.|
