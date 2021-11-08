# [Spring Integration](https://spring.io/projects/spring-integration)
- [Reference](https://docs.spring.io/spring-integration/docs/current/reference/html/)
- [API doc](https://docs.spring.io/spring-integration/docs/current/api/)
- Components: 
    - Message: org.springframework.messaging.Message: Headers with Payload
    - Channel: org.springframework.messaging.MessageChannel: PollableChannel; SubscribableChannel 
    - MessageEndpoint( with MessageHandler):  org.springframework.integration.endpoint.AbstractEndpoint: The main implementations are:    
        - EventDrivenConsumer, used when we subscribe to a SubscribableChannel to listen for messages.
        - PollingConsumer, used when we poll for messages from a PollableChannel.

Spring integration follows the “pipes-and-filters” model. The “filters” represent any components capable of producing or consuming messages, and the “pipes” transport the messages between filters so that the components themselves remain loosely-coupled.

## Message
![Message](https://docs.spring.io/spring-integration/docs/current/reference/html/images/message.jpg)

The generic wrapper for any Java object combined with metadata used by the framework while handling that object. 
It consists of a payload and headers. The payload can be of any type, and the headers hold commonly required 
information such as ID, timestamp, correlation ID, and return address. 
Headers are also used for passing values to and from connected transports. 

### Interface [Message<T>](https://docs.spring.io/spring-framework/docs/current/javadoc-api/org/springframework/messaging/Message.html):
- MessageHeaders 	getHeaders()
  
  Return message headers for the message (never null but may be empty).
- T 	getPayload()
  
  Return the message payload.
  
### Interface [MessageSource<T>](https://docs.spring.io/spring-integration/docs/current/api/org/springframework/integration/core/MessageSource.html):
- IntegrationPatternType 	getIntegrationPatternType() 	
  
Return a pattern type this component implements.
- Message<T> 	receive() 	
  
Retrieve the next available message from this source.

### [MessageHandler](https://docs.spring.io/spring-framework/docs/current/javadoc-api/org/springframework/messaging/MessageHandler.html?)
- void 	handleMessage(Message<?> message)

Handle the given message.

### [MessageHandlerChain](https://docs.spring.io/spring-integration/docs/current/api/org/springframework/integration/handler/MessageHandlerChain.html)
 
A composite MessageHandler implementation that invokes a chain of MessageHandler instances in order. 

### [MessageProducer](https://docs.spring.io/spring-integration/docs/current/api/org/springframework/integration/core/MessageProducer.html)
- MessageChannel 	getOutputChannel() 	
- void 	setOutputChannel(MessageChannel outputChannel) 	
- void 	setOutputChannelName (String outputChannel)
  
## Channels
![Channel](https://docs.spring.io/spring-integration/docs/current/reference/html/images/channel.jpg)

Represents the “pipe” of a pipes-and-filters architecture. Supports 2 types of channels:
- Point-to-Point channel: no more than one consumer can receive each message sent to the channel  
- Publish-Subscribe channel: attempt to broadcast each message to all subscribers on the channel.   

### [MessageChannel](https://docs.spring.io/spring-framework/docs/current/javadoc-api/org/springframework/messaging/MessageChannel.html)  
- boolean 	send(Message<?> message)
- boolean 	send(Message<?> message, long timeout)

### [Interface SubscribableChannel](https://docs.spring.io/spring-framework/docs/current/javadoc-api/org/springframework/messaging/SubscribableChannel.html)
 A MessageChannel that maintains a registry of subscribers and invokes them to handle messages sent through this channel, it supports publish-subscribe feature
- boolean 	subscribe(MessageHandler handler)
- boolean 	unsubscribe(MessageHandler handler)

The channel can buffer messages, pollable channels are capable of buffering Messages within a queue.

###[Interface PollableChannel](https://docs.spring.io/spring-framework/docs/current/javadoc-api/org/springframework/messaging/PollableChannel.html)

A MessageChannel from which messages may be actively received through polling. It needs a Poller.
- Message<?> 	receive()
- Message<?> 	receive(long timeout)

## Message Endpoints
Represents the “filter” of a pipes-and-filters architecture. Similar to the role of a controller in the MVC paradigm. Just as controllers are mapped to URL patterns, message endpoints are mapped to message channels. 

###  Message Transformer

Responsible for converting a message’s content or structure and returning the modified message. Probably the most common type of transformer is one that converts the payload of the message from one format to another (such as from XML to java.lang.String). Similarly, a transformer can add, remove, or modify the message’s header values.

### Message Filter

Determines whether a message should be passed to an output channel at all. This simply requires a boolean test method that may check for a particular payload content type, a property value, the presence of a header, or other conditions. If the message is accepted, it is sent to the output channel. If not, it is dropped (or, for a more severe implementation, an Exception could be thrown). Message filters are often used in conjunction with a publish-subscribe channel, where multiple consumers may receive the same message and use the criteria of the filter to narrow down the set of messages to be processed.

### Message Router

![Router](https://docs.spring.io/spring-integration/docs/current/reference/html/images/router.jpg)
  
Responsible for deciding what channel or channels (if any) should receive the message next. Typically, the decision is based upon the message’s content or the metadata available in the message headers. A message router is often used as a dynamic alternative to a statically configured output channel on a service activator or other endpoint capable of sending reply messages. Likewise, a message router provides a proactive alternative to the reactive message filters used by multiple subscribers.

### Splitter

Responsibility to accept a message from its input channel, split that message into multiple messages, and send each of those to its output channel. This is typically used for dividing a “composite” payload object into a group of messages containing the subdivided payloads.

### Aggregator

Contrary to the splitter, the aggregator is a type of message endpoint that receives multiple messages and combines them into a single message. Aggregators are often downstream consumers in a pipeline that includes a splitter. Technically, the aggregator is more complex than a splitter, because it is required to maintain state (the messages to be aggregated), to decide when the complete group of messages is available, and to timeout if necessary. Furthermore, in case of a timeout, the aggregator needs to know whether to send the partial results, discard them, or send them to a separate channel. Spring Integration provides a CorrelationStrategy, a ReleaseStrategy, and configurable settings for timeout, whether to send partial results upon timeout

### Service Activator

The generic endpoint for connecting a service instance to the messaging system. The input message channel must be configured, and, if the service method to be invoked is capable of returning a value, an output message Channel may also be provided.
  
The service activator invokes an operation on some service object to process the request message, extracting the request message’s payload and converting (if the method does not expect a message-typed parameter). Whenever the service object’s method returns a value, that return value is likewise converted to a reply message if necessary (if it is not already a message type). That reply message is sent to the output channel. If no output channel has been configured, the reply is sent to the channel specified in the message’s “return address”, if available.

A request-reply service activator endpoint connects a target object’s method to input and output Message Channels.

  ![Activator](https://docs.spring.io/spring-integration/docs/current/reference/html/images/handler-endpoint.jpg)

  Service Activator
  
### Channel Adapter

The endpoint to connects a message channel to some other system or transport. Channel adapters may be either inbound or outbound. Typically, the channel adapter does some mapping between the message and whatever object or resource is received from or sent to the other system (file, HTTP Request, JMS message, and others). Depending on the transport, the channel adapter may also populate or extract message header values. Spring Integration provides a number of channel adapters.
  
![InBound Adaptor](https://docs.spring.io/spring-integration/docs/current/reference/html/images/source-endpoint.jpg)

  An inbound channel adapter endpoint connects a source system to a MessageChannel.

![OutBound Adaptor](https://docs.spring.io/spring-integration/docs/current/reference/html/images/target-endpoint.jpg)  

  An outbound channel adapter endpoint connects a MessageChannel to a target system
  
## Endpoint Bean Names

- Consuming endpoints (anything with an inputChannel) consist of two beans, the consumer and the message handler. The consumer has a reference to the message handler and invokes it as messages arrive.  

    - Consumer: someService (the id:  @EndpointId("someService"))
    - Handler: someService.handler
```
@Component
public class SomeComponent {
    @ServiceActivator(inputChannel = ...)
    public String someMethod(...) {
        ...
    }
}  
```  
- Consumer: someComponent.someMethod.serviceActivator
- Handler: someComponent.someMethod.serviceActivator.handler

```
@Component
public class SomeComponent {
    @EndpointId("someService")
    @ServiceActivator(inputChannel = ...)
    public String someMethod(...) {
        ...
    }
}  
```
- Consumer: someService
- Handler: someService.handler

```
@Configuration
public class SomeConfiguration {
    @Bean
    @ServiceActivator(inputChannel = ...)
    public MessageHandler someHandler() {
        ...
    }
}
```  
- Consumer: someConfiguration.someHandler.serviceActivator
- Handler: someHandler (the @Bean name)
```
@Configuration
public class SomeConfiguration {
    @Bean("someService.handler")             
    @EndpointId("someService")               
    @ServiceActivator(inputChannel = ...)
    public MessageHandler someHandler() {
        ...
    }
}
``` 
- Handler: someService.handler (the bean name)
- Consumer: someService (the endpoint ID)

If a MessageHandler @Bean does not define an AbstractReplyProducingMessageHandler, the framework wraps the provided bean in a ReplyProducingMessageHandlerWrapper. This wrapper supports request handler advice handling and emits the normal 'produced no reply' debug log messages. Its bean name is the handler bean name plus .wrapper (when there is an @EndpointId — otherwise, it is the normal generated handler name).

 Pollable Message Sources create two beans, a SourcePollingChannelAdapter (SPCA) and a MessageSource.  
```
@EndpointId("someAdapter")
@InboundChannelAdapter(channel = "channel3", poller = @Poller(fixedDelay = "5000"))
public String pojoSource() {
    ...
}
```
- SPCA: someAdapter
- Handler: someAdapter.source

```
@Bean("someAdapter.source")
@EndpointId("someAdapter")
@InboundChannelAdapter(channel = "channel3", poller = @Poller(fixedDelay = "5000"))
public MessageSource<?> source() {
    return () -> {
        ...
    };
}
```
- SPCA: someAdapter
- Handler: someAdapter.source (as long as you use the convention of appending .source to the @Bean name)

## Common Annotations
- @EnableIntegration:
    
    Is used to allow the registration of Spring Integration infrastructure beans. It is useful when have a parent context with no Spring Integration components and two or more child contexts that use Spring Integration. It lets these common components be declared once only, in the parent context.

- @IntegrationComponentScan
    
    Permits classpath scanning. This annotation plays a similar role as the standard Spring Framework @ComponentScan annotation, but it is restricted to components and annotations that are specific to Spring Integration, which the standard Spring Framework component scan mechanism cannot reach.     

- @EnablePublisher
    
    Registers a PublisherAnnotationBeanPostProcessor bean and configures the default-publisher-channel for those @Publisher annotations that are provided without a channel attribute.     

- @GlobalChannelInterceptor
    Used to mark ChannelInterceptor beans for global channel interception. It can be placed at the class level (with a @Component stereotype annotation) or on @Bean methods within @Configuration classes. In either case, the bean must implement ChannelInterceptor. 
    
- @IntegrationConverter
    
    Marks Converter, GenericConverter, or ConverterFactory beans as candidate converters for integrationConversionService. It can be used at the class level (with a @Component stereotype annotation) or on @Bean methods within @Configuration classes.
    
## Finding Class Names for Java and DSL Configuration

The Framework automatically produces the components with appropriate annotations and BeanPostProcessor implementations. When building components manually, should use the ConsumerEndpointFactoryBean to help determine the target AbstractEndpoint consumer implementation to create, based on the provided inputChannel property.

The ConsumerEndpointFactoryBean delegates to an another first class citizen in the Framework - org.springframework.messaging.MessageHandler. The goal of the implementation of this interface is to handle the message consumed by the endpoint from the channel. All EIP components in Spring Integration are MessageHandler implementations (for example, AggregatingMessageHandler, MessageTransformingHandler, AbstractMessageSplitter, and others). The target protocol outbound adapters (FileWritingMessageHandler, HttpRequestExecutingMessageHandler, AbstractMqttMessageHandler, and others) are also MessageHandler implementations. When you develop Spring Integration applications with Java configuration, should look into the Spring Integration module to find an appropriate MessageHandler implementation to use for the @ServiceActivator configuration.
    
For example, to send an XMPP message:    
```
@Bean
@ServiceActivator(inputChannel = "input")
public MessageHandler sendChatMessageHandler(XMPPConnection xmppConnection) {
    ChatMessageSendingMessageHandler handler = new ChatMessageSendingMessageHandler(xmppConnection);
    DefaultXmppHeaderMapper xmppHeaderMapper = new DefaultXmppHeaderMapper();
    xmppHeaderMapper.setRequestHeaderNames("*");
    handler.setHeaderMapper(xmppHeaderMapper);

    return handler;
}    
```      

The inbound message flow side has its own components, and are divided into polling and listening behaviors. The listening (message-driven) components are simple and typically require only one target class implementation to be ready to produce messages. Listening components can be one-way MessageProducerSupport implementations, (such as AbstractMqttMessageDrivenChannelAdapter and ImapIdleChannelAdapter) or request-reply MessagingGatewaySupport implementations (such as AmqpInboundGateway and AbstractWebServiceInboundGateway).

Polling inbound endpoints are for those protocols that do not provide a listener API or are not intended for such a behavior, including any file based protocol (such as FTP), any data bases (RDBMS or NoSQL), and others.

These inbound endpoints consist of two components: the poller configuration, to initiate the polling task periodically, and a message source class to read data from the target protocol and produce a message for the downstream integration flow. The first class for the poller configuration is a SourcePollingChannelAdapter. It is one more AbstractEndpoint implementation, but especially for polling to initiate an integration flow. Typically, with the messaging annotations or Java DSL, should not worry about this class. The Framework produces a bean for it, based on the @InboundChannelAdapter configuration or a Java DSL builder spec.

Message source components are more important for the target application development, and they all implement the MessageSource interface (for example, MongoDbMessageSource and AbstractTwitterMessageSource). With that in mind, the config for reading data from an RDBMS table with JDBC could resemble the following:
```
@Bean
@InboundChannelAdapter(value = "fooChannel", poller = @Poller(fixedDelay="5000"))
public MessageSource<?> storedProc(DataSource dataSource) {
    return new JdbcPollingChannelAdapter(dataSource, "SELECT * FROM foo where status = 0");
}
```

## POJO Method invocation    
```
@ServiceActivator
public String myService(String payload) { ... }
```
The framework extracts a String payload, invokes the method, and wraps the result in a message to send to the next component in the flow (the original headers are copied to the new message). 

Obtain header information:
```
@ServiceActivator
public String myService(@Payload String payload, @Header("foo") String fooHeader) { ... }
```

Dereference properties on the message
```
@ServiceActivator
public String myService(@Payload("payload.foo") String foo, @Header("bar.baz") String barbaz) { ... }
```
The org.springframework.messaging.handler.invocation.InvocableHandlerMethod is used by default to invoke the POJO methods.
 Set up POJO method to always use SpEL, using  UseSpelInvoker annotation,
```
@UseSpelInvoker(compilerMode = "IMMEDIATE")
public void bar(String bar) { ... }
```

    
## [Annotations](https://docs.spring.io/spring-integration/docs/current/api/org/springframework/integration/annotation/package-summary.html)
- IntegrationComponentScan: Configures component scanning directives for use with Configuration classes.


- InboundChannelAdapter: Indicates that a method is capable of producing a Message or Message payload.
- ServiceActivator: Indicates that a method is capable of handling a message or message payload.
- MessagingGateway: A stereotype annotation to provide an Integration Messaging Gateway Proxy (<gateway/>) as an abstraction over the messaging API.
- MessageEndpoint: Stereotype annotation indicating that a class is capable of serving as a Message Endpoint.


- Aggregator: Indicates that a method is capable of aggregating messages.
- Router:Indicates that a method is capable of resolving to a channel or channel name based on a message, message header(s), or both.
- Splitter: Indicates that a method is capable of splitting a single message or message payload to produce multiple messages or payloads.
- Transformer: Indicates that a method is capable of transforming a message, message header, or message payload.
- Filter: Indicates that a method is capable of playing the role of a Message Filter.


- BridgeFrom:Messaging Annotation to mark a Bean method for a MessageChannel to produce a BridgeHandler and Consumer Endpoint.
- BridgeTo: Messaging Annotation to mark a Bean method for a MessageChannel to produce a BridgeHandler and Consumer Endpoint.


- Poller: Provides the PollerMetadata options for the Messaging annotations for polled endpoints.
- EndpointId: When used alongside an EIP annotation (and no @Bean), specifies the bean name of the consumer bean with the handler bean being id.handler (for a consuming endpoint) or id.source for a message source (e.g.


- CorrelationStrategy: Indicates that a given method is capable of determining the correlation key of a message sent as parameter.
- ReleaseStrategy: Indicates that a method is capable of asserting if a list of messages or payload objects is complete.


- Default: Indicates that the class member has some default meaning.
- Gateway: Indicates that an interface method is capable of mapping its parameters to a message or message payload.
- GatewayHeader: Provides the message header value or expression.
- Payloads: This annotation marks a method parameter as being a list of message payloads, for POJO handlers that deal with lists of messages (e.g.
- IdempotentReceiver: A method that has a MessagingAnnotation (@code @ServiceActivator, @Router etc.) that also has this annotation, has an IdempotentReceiverInterceptor applied to the associated MessageHandler.handleMessage(org.springframework.messaging.Message<?>) method.

    
- Publisher: Annotation to indicate that a method, or all public methods if applied at class-level, should publish Messages.
- Reactive: Provides reactive configuration options for the consumer endpoint making any input channel as a reactive stream source of data.
- Role: Annotate endpoints to assign them to a role.
- UseSpelInvoker: Indicates that a POJO handler method (@ServiceActivator, @Transformer, etc., or such methods invoked from XML definitions) should be invoked using SpEL.
