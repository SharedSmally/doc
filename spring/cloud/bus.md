# Spring Cloud Bus: Based on Cloud Stream

Spring Cloud Bus uses lightweight message broker to link distributed system nodes. The primary usage is to broadcast configuration changes 
or other management information. We can think about it as a distributed Actuator. The project uses AMQP broker as the transport, 
but Apache Kafka or Redis can be utilized instead of RabbitMQ. Other transports are not supported yet.

- [Reference](https://spring.io/projects/spring-cloud-bus)
- [Tutorial](https://www.baeldung.com/spring-cloud-bus)


## Cloud Bus
To enable the bus, add spring-cloud-starter-bus-amqp or spring-cloud-starter-bus-kafka to the dependency management.

The bus currently supports sending messages to all nodes listening or all nodes for a particular service (as defined by Eureka). The /bus/* actuator namespace has some HTTP endpoints. Currently, two are implemented. The first, /bus/env, sends key/value pairs to update each node’s Spring Environment. The second, /bus/refresh, reloads each application’s configuration, as though they had all been pinged on their /refresh endpoint.

## Cloud Bus Endpoints
Spring Cloud Bus provides two endpoints, /actuator/bus-refresh and /actuator/bus-env that correspond to individual actuator endpoints in Spring Cloud Commons, /actuator/refresh and /actuator/env respectively.

- Bus Refresh Endpoint

The /actuator/bus-refresh endpoint clears the RefreshScope cache and rebinds @ConfigurationProperties
```
management.endpoints.web.exposure.include=bus-refresh
```
- Bus Env Endpoint

The /actuator/bus-env endpoint updates each instances environment with the specified key/value pair across multiple instances.
```
management.endpoints.web.exposure.include=bus-env
```
The /actuator/bus-env endpoint accepts POST requests with the following shape:
```
{
    "name": "key1",
    "value": "value1"
}
```
### Addressing an Instance

Each instance of the application has a service ID, whose value can be set with spring.cloud.bus.id and whose value is expected to be a colon-separated list of identifiers, in order from least specific to most specific. The default value is constructed from the environment as a combination of the spring.application.name and server.port (or spring.application.index, if set). The default value of the ID is constructed in the form of app:index:id, where:

- app is the vcap.application.name, if it exists, or spring.application.name
- index is the vcap.application.instance_index, if it exists, spring.application.index, local.server.port, server.port, or 0 (in that order).
- id is the vcap.application.instance_id, if it exists, or a random value.

The HTTP endpoints accept a “destination” path parameter, such as /bus-refresh/customers:9000, where destination is a service ID. If the ID is owned by an instance on the bus, it processes the message, and all other instances ignore it.

The “destination” parameter is used in a Spring PathMatcher (with the path separator as a colon — :) to determine if an instance processes the message. Using the example from earlier, /bus-env/customers:** targets all instances of the “customers” service regardless of the rest of the service ID.

### Tracing Bus Events
Bus events (subclasses of RemoteApplicationEvent) can be traced by setting spring.cloud.bus.trace.enabled=true. The Spring Boot TraceRepository (if present) shows each event sent and all the acks from each service instance (from the /trace endpoint).

To handle the ack signals yourself, you could add an @EventListener for the AckRemoteApplicationEvent and SentApplicationEvent types to your app (and enable tracing). Alternatively, you could tap into the TraceRepository and mine the data from there.

## Broadcasting Own Events

The Bus can carry any event of type RemoteApplicationEvent. The default transport is JSON, and the deserializer needs to know which types are going to be used ahead of time. To register a new type, you must put it in a subpackage of org.springframework.cloud.bus.event.

To customise the event name, you can use @JsonTypeName on your custom class or rely on the default strategy, which is to use the simple name of the class.

If you cannot or do not want to use a subpackage of org.springframework.cloud.bus.event for your custom events, you must specify which packages to scan for events of type RemoteApplicationEvent by using the @RemoteApplicationEventScan annotation. Packages specified with @RemoteApplicationEventScan include subpackages.
```
@Configuration
@RemoteApplicationEventScan
public class BusConfiguration {
    ...
}
```

## Config Client Depdendencies
- spring-cloud-starter-bus-amqp: cloud config client can subscribe to RabbitMQ/Kafka exchange
- In application.yml:
```
spring:
	  rabbitmq:
	    host: localhost
	    port: 5672
	    username: guest
	    password: guest
	  cloud:
	    bus:
	      enabled: true
	      refresh:
	        enabled: true
```
The client will have another endpoint ‘/bus-refresh'. Calling this endpoint will cause:
- get the latest configuration from the config server and update its configuration annotated by @RefreshScope
- send a message to AMQP exchange informing about refresh event
- all subscribed nodes will update their configuration as well

## Config Server Depdendencies
Use spring-cloud-config-monitor to monitor configuration changes and broadcast events using RabbitMQ as transport.

- spring-cloud-config-monitor
- spring-cloud-starter-stream-rabbit
- RabbitMQ configs in application.properties

```
spring.rabbitmq.host=localhost
spring.rabbitmq.port=5672
spring.rabbitmq.username=guest
spring.rabbitmq.password=guest
```

## GitHub Webhook

Once the server gets notified about configuration changes, it will broadcast this as a message to RabbitMQ. 
The client will listen to messages and update its configuration when configuration change event is transmitted. 

Need to configure a GitHub Webhook for a server is notified by the modification. Go to GitHub and open our 
repository holding configuration properties. Select Settings and Webhook. Let's click on Add webhook button.
Payload URL is the URL for our config server ‘/monitor' endpoint. In our case the URL will be something like this:
http://root:s3cr3t@REMOTE_IP:8888/monitor

We just need to change Content type in the drop-down menu to application/json. 
