# [Spring Cloud](https://spring.io/projects/spring-cloud)
- [Document](https://cloud.spring.io/spring-cloud-static/spring-cloud.htm)
- [Tutorial](https://www.javatpoint.com/components-of-spring-cloud)


## Spring Cloud
- [Azure](https://spring.io/projects/spring-cloud-azure)
- [Alibaba](https://spring.io/projects/spring-cloud-alibaba)
- [AWS](https://spring.io/projects/spring-cloud-aws)
- [Cloud Foundry](https://spring.io/projects/spring-cloud-cloudfoundry)
- [GCP](https://spring.io/projects/spring-cloud-gcp)
- [NetFlix](https://spring.io/projects/spring-cloud-netflix)
    - Service Discovery: embedded/standalone Eureka server and Client
    - Circuit Breaker: embedded/standalone Hystrix server and client
    - External Configuration: Archaius
    - Router and Filter: Zuul
    - Client Side Load Balancer: Ribbon
    - Declarative REST Client: Feign
    - Metrics: Spectator, Servo, and Atlas

## Brokers
### [Open Service Broker](https://spring.io/projects/spring-cloud-open-service-broker)
- [Cloud Foundry](https://spring.io/projects/spring-cloud-cloudfoundry-service-broker)
- [Kubernetes](https://spring.io/projects/spring-cloud-kubernetes)
- OpenShift


### [App Broker](https://spring.io/projects/spring-cloud-app-broker)
The Open Service Broker API project allows developers to deliver services to applications running within cloud native platforms 
such as Cloud Foundry, Kubernetes, and OpenShift. Spring Cloud App Broker provides a framework based on Spring Boot that enables
you to quickly create a service broker that deploys applications and services to the platform when managed services are provisioned.

## 

## [Circuit Breaker](https://spring.io/projects/spring-cloud-circuitbreaker)
- Netfix Hystrix
- Resilience4J
- Sentinel
- Spring Retry

- Cloud Bus
- Cloud Stream
- Cloud Trace (Sleuth)



## Spring Cloud (NetFlix)
- Distributed/versioned configuration
- Service registration and discovery: Eureka Clients and Eureka Server
- Routing
- Service-to-service calls
- Distributed messaging: Publish-Subscribe (Pub-Sub) model using Apache Kafka and RabbitMQ
- Load balancing: Ribbon
- Circuit Breakers: Hystrix Clients and Dashboard
- Global locks
- Leadership election and cluster state


## Spring Cloud Components
- ![Configuration](https://static.javatpoint.com/tutorial/spring-cloud/images/components-of-spring-cloud.png)
Spring Cloud config server can use Git, SVN (Apache Subversion), filesystem, and Vault to Store config. 
Config clients (microservice app) retrieve the configuration client from the server on startup.

- ![Service Discovery](https://static.javatpoint.com/tutorial/spring-cloud/images/components-of-spring-cloud2.png)

- ![Circuit Breakers](https://static.javatpoint.com/tutorial/spring-cloud/images/components-of-spring-cloud3.png)

- ![Routing and Messaging](https://static.javatpoint.com/tutorial/spring-cloud/images/components-of-spring-cloud7.png)

- ![API Gateway](https://static.javatpoint.com/tutorial/spring-cloud/images/components-of-spring-cloud8.png)

- ![Tracing]()

- CI Pipeline and Testing

### Configuration

###
Service Discovery



