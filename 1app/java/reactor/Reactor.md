# Reactive
Reactive Streams Implementation 
- [Reactor](https://projectreactor.io/)
- [JavaRx](https://github.com/ReactiveX/RxJava)

## Reactive Streams Specification
![Java Reactive](https://miro.medium.com/v2/resize:fit:640/format:webp/0*Boh8h9YJ79LdXOl5.jpeg)
### Publisher
    This is a single method interface that will be used to register the subscriber to the publisher. The subscribe method of this interface accepts the subscriber object and registers it.

### Subscriber
    This is an interface that has four methods
    - onSubscribe method will be called by the publisher when subscribing to the Subscribe object.
    - onNext method will be called when the next data will be published to the subscriber
    - onError method will be called when exceptions arise while publishing data to the subscriber
    - onComplete method will be called after the successful completion of data publishing to the subscriber

### Subscription
    This is an interface with two methods. The subscription object will be created when the user subscribes to the publisher in the publisher object as discussed earlier. The subscription object will be passed to the subscriber object via onSubscribe method
    - request method will be called when the subscriber needs to request data from the publisher
    - cancel method will be called when the subscriber needs to cancel and close the subscription

### Processor
    This is an interface that is extended by both publisher and subscriber interfaces. This interface is not very common but will be used to process the logic of the subscribing and publishing workflow



