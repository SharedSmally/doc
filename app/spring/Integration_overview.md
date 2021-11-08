# [Spring Integration](https://spring.io/projects/spring-integration)
- [Reference](https://docs.spring.io/spring-integration/docs/current/reference/html/)
- [API doc](https://docs.spring.io/spring-integration/docs/current/api/)


## Message
![Message](https://docs.spring.io/spring-integration/docs/current/reference/html/images/message.jpg)
The generic wrapper for any Java object combined with metadata used by the framework while handling that object. 
It consists of a payload and headers. The payload can be of any type, and the headers hold commonly required 
information such as ID, timestamp, correlation ID, and return address. 
Headers are also used for passing values to and from connected transports. 

Interface [Message<T>](https://docs.spring.io/spring-framework/docs/current/javadoc-api/org/springframework/messaging/Message.html):
- MessageHeaders 	getHeaders()
  Return message headers for the message (never null but may be empty).
- T 	getPayload()
  Return the message payload.
  
Interface [MessageSource<T>](https://docs.spring.io/spring-integration/docs/current/api/org/springframework/integration/core/MessageSource.html):
- default IntegrationPatternType 	getIntegrationPatternType() 	
Return a pattern type this component implements.
- Message<T> 	receive() 	
Retrieve the next available message from this source.
  
  
## Channel
![Channel](https://docs.spring.io/spring-integration/docs/current/reference/html/images/channel.jpg)

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
