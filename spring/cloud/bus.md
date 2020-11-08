# Spring Cloud Bus: Based on Cloud Stream

Spring Cloud Bus uses lightweight message broker to link distributed system nodes. The primary usage is to broadcast configuration changes 
or other management information. We can think about it as a distributed Actuator. The project uses AMQP broker as the transport, 
but Apache Kafka or Redis can be utilized instead of RabbitMQ. Other transports are not supported yet.

- [Reference](https://spring.io/projects/spring-cloud-bus)
- [Tutorial](https://www.baeldung.com/spring-cloud-bus)

## Config Client Depdendencies
- spring-cloud-starter-bus-amqp: cloud config client can subscribe to RabbitMQ exchange
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
