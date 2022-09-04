# Spring Boot for Message

## [Messaging](https://docs.spring.io/spring-boot/docs/current/reference/html/messaging.html)
- JMS/ActiveMQ: JmsTemplate to send/receive message
- AMQP/RabbitMQ: using AMQP protocol
- WebSocket: include STOMP

## JMS
The javax.jms.ConnectionFactory interface provides a standard method of creating a javax.jms.Connection for interacting with a JMS broker.
- ActiveMQ via **spring.activemq.\*** and **spring.jms.\*** properties:
```
spring.activemq.in-memory=false
spring.activemq.broker-url=tcp://192.168.1.210:9876
spring.activemq.user=admin
spring.activemq.password=secret

spring.jms.cache.session-cache-size=5

spring.activemq.pool.enabled=true
spring.activemq.pool.max-connections=50
```

- ActiveMQ Artemis via **spring.artemis.\*** (spring-boot-starter-artemis), Faster, specifically for non-blocking
```
spring.artemis.mode=native
spring.artemis.broker-url=tcp://192.168.1.210:9876
spring.artemis.user=admin
spring.artemis.password=secret
```

- Sending a message
```
@Component
public class MyBean {
    private final JmsTemplate jmsTemplate;
    public MyBean(JmsTemplate jmsTemplate) {
        this.jmsTemplate = jmsTemplate;
    }

    public void someMethod() {
        this.jmsTemplate.convertAndSend("hello");
    }
}
```
- Receiving a message
```
@Component
public class MyBean {
    @JmsListener(destination = "someQueue")
    public void processMessage(String content) {
        // ...
    }
}
```
Create a JmsListenerContainerFactory to customize the converters, etc

```
import javax.jms.ConnectionFactory;
import org.springframework.boot.autoconfigure.jms.DefaultJmsListenerContainerFactoryConfigurer;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;
import org.springframework.jms.config.DefaultJmsListenerContainerFactory;

@Configuration(proxyBeanMethods = false)
public class MyJmsConfiguration {
    @Bean
    public DefaultJmsListenerContainerFactory myFactory(DefaultJmsListenerContainerFactoryConfigurer configurer) {
        DefaultJmsListenerContainerFactory factory = new DefaultJmsListenerContainerFactory();
        ConnectionFactory connectionFactory = getCustomConnectionFactory();
        configurer.configure(factory, connectionFactory);
        factory.setMessageConverter(new MyMessageConverter());
        return factory;
    }

    private ConnectionFactory getCustomConnectionFactory() {
        return ...
    }
}
```
And use the factory in @JmsListener-annotated method :
```
@JmsListener(destination = "someQueue", containerFactory = "myFactory")
```

## AMQP RabbitMQ (spring-boot-starter-amqp)
-  RabbitMQ with **spring.rabbitmq.\***:
```
spring.rabbitmq.host=localhost
spring.rabbitmq.port=5672
spring.rabbitmq.username=admin
spring.rabbitmq.password=secret
spring.rabbitmq.addresses=amqp://admin:secret@localhost  #including all

spring.rabbitmq.template.retry.enabled=true   # retry
spring.rabbitmq.template.retry.initial-interval=2s

spring.rabbitmq.stream.name=my-stream  # send message to a stream using RabbitStreamTemplate.
```
-  Send a Message
Spring’s **AmqpTemplate** and **AmqpAdmin** are auto-configured
```
import org.springframework.amqp.core.AmqpAdmin;
import org.springframework.amqp.core.AmqpTemplate;
import org.springframework.stereotype.Component;

@Component
public class MyBean {
    private final AmqpAdmin amqpAdmin;
    private final AmqpTemplate amqpTemplate;

    public MyBean(AmqpAdmin amqpAdmin, AmqpTemplate amqpTemplate) {
        this.amqpAdmin = amqpAdmin;
        this.amqpTemplate = amqpTemplate;
    }

    public void someMethod() {
        this.amqpAdmin.getQueueInfo("someQueue");
    }

    public void someOtherMethod() {
        this.amqpTemplate.convertAndSend("hello");
    }
}
```
-  Receive a Message
Any bean annotated with @RabbitListener is created as a listener endpoint, and the ListenerContainerFactory can be customized to set the converter,...:
```
import org.springframework.amqp.rabbit.annotation.RabbitListener;
import org.springframework.stereotype.Component;

@Component
public class MyBean {
    @RabbitListener(queues = "someQueue")
    public void processMessage(String content) {
        // ...
    }
}
```

## Kafka:
- Kafka Support with **spring.kafka.\*** properties:
```
spring.kafka.bootstrap-servers=localhost:9092
spring.kafka.consumer.group-id=myGroup
```
- Sending a Message
Use auto-configured **KafkaTemplate** bean:
```
import org.springframework.kafka.core.KafkaTemplate;
import org.springframework.stereotype.Component;

@Component
public class MyBean {
    private final KafkaTemplate<String, String> kafkaTemplate;
    public MyBean(KafkaTemplate<String, String> kafkaTemplate) {
        this.kafkaTemplate = kafkaTemplate;
    }

    public void someMethod() {
        this.kafkaTemplate.send("someTopic", "Hello");
    }
}
```
- Receiving a Message
Any bean annotated with **@KafkaListener** is created as a listener endpoint
```
@Component
public class MyBean {

    @KafkaListener(topics = "someTopic")
    public void processMessage(String content) {
        // ...
    }
}
```
- Kafka Stream
Spring for Apache Kafka provides a factory bean to create a StreamsBuilder object and manage the lifecycle of its streams.
Wire StreamsBuilder into the @Bean to use the factory bean:
```
import org.apache.kafka.common.serialization.Serdes;
import org.apache.kafka.streams.KeyValue;
import org.apache.kafka.streams.StreamsBuilder;
import org.apache.kafka.streams.kstream.KStream;
import org.apache.kafka.streams.kstream.Produced;

import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;
import org.springframework.kafka.annotation.EnableKafkaStreams;
import org.springframework.kafka.support.serializer.JsonSerde;

@Configuration(proxyBeanMethods = false)
@EnableKafkaStreams
public class MyKafkaStreamsConfiguration {
    @Bean
    public KStream<Integer, String> kStream(StreamsBuilder streamsBuilder) {
        KStream<Integer, String> stream = streamsBuilder.stream("ks1In");
        stream.map(this::uppercaseValue).to("ks1Out", Produced.with(Serdes.Integer(), new JsonSerde<>()));
        return stream;
    }
    private KeyValue<Integer, String> uppercaseValue(Integer key, String value) {
        return new KeyValue<>(key, value.toUpperCase());
    }
}
```

## RSocket: binary protocol for byte stream transport

The spring-messaging module of the Spring Framework provides support for RSocket requesters and responders, both on the client and on the server side.

Once the RSocket channel is established between server and client, any party can send or receive requests to the other.

As a server, you can get injected with an RSocketRequester instance on any handler method of an RSocket @Controller. As a client, you need to configure and establish an RSocket connection first. Spring Boot auto-configures an RSocketRequester.Builder for such cases with the expected codecs and applies any RSocketConnectorConfigurer bean.

```
import reactor.core.publisher.Mono;
import org.springframework.messaging.rsocket.RSocketRequester;
import org.springframework.stereotype.Service;

@Service
public class MyService {
    private final RSocketRequester rsocketRequester;
    public MyService(RSocketRequester.Builder rsocketRequesterBuilder) {
        this.rsocketRequester = rsocketRequesterBuilder.tcp("example.org", 9898);
    }
    public Mono<User> someRSocketCall(String name) {
        return this.rsocketRequester.route("user").data(name).retrieveMono(User.class);
    }
}
```

## Spring Integration (spring-boot-starter-integration)
Spring Integration provides abstractions over messaging and also other transports such as HTTP, TCP, and others.
Use **spring.integration.\*** to setup Spring Integration.

## WebSockets (spring-boot-starter-websocket/spring-boot-starter-webflux)
Spring Boot provides WebSockets auto-configuration for embedded Tomcat, Jetty, and Undertow


