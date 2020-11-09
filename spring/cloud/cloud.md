# [Spring Cloud](https://spring.io/projects/spring-cloud)
- [Document](https://cloud.spring.io/spring-cloud-static/spring-cloud.htm)
- [Tutorial](https://www.javatpoint.com/components-of-spring-cloud)

## Cloud Commons
- Config Server: Bus/Stream
- Service Restry/Discovery
- Circuit Breaker
- Gateway: LoadBalance; Gateway; Zuul
- Trace: Sleuth
- Deploy: Skipper
- Implementations:
    - Consul:Config;Discovery;LoadBalance;Router
    - Netfliex:Config;Discovery;LoadBalance;Router;Feign
    - Zookeeper: Config; Discovery
    - Vault: store security info
    - Kubernetes: Discovery; Config; CS-LoadBalance
- Common: Task; Function; Service/App Broker;

CS-LB: Client-Side Load Balance

## Projects
- Spring Cloud Commons
- Spring Cloud [Gateway](https://docs.spring.io/spring-cloud-gateway/docs/2.2.5.RELEASE/reference/html/) and Client-side Load Balancer
- Spring Cloud [Config](https://docs.spring.io/spring-cloud-config/docs/2.2.5.RELEASE/reference/html/) and Service/Schema Registry
    - Spring Cloud Netflix: Eureka; 
    - Spring Cloud Consul:
    - Spring Cloud Zookeeper: (etcd,...)
- Spring Cloud [Circuit Breaker](https://spring.io/projects/spring-cloud-circuitbreaker):
    - Netflix Hystrix
    - Resilience4J
    - Sentinel
    - Spring Retry
- Security:
    - Spring Cloud Security
    - Spring Cloud Vault
- Application
    - Spring Cloud Cluster
    - Spring Cloud Connectors:  Java CFEnv
    - Spring Cloud Bus
    - Spring Cloud Contract
    - Spring Cloud Function
    - Spring Cloud Pipelines
    - Spring Cloud Stream
    - Spring Cloud Stream Applications
    - Spring Cloud Stream App Starters
    - Spring Cloud Task
    - Spring Cloud Task App Starters
- Cloud Tools:    
    - Spring Cloud Skipper: A tool to discover Spring Boot applications and manage their lifecycle on multiple Cloud Platforms. 
    - Spring Cloud Sleuth/zipkin: Provides Spring Boot auto-configuration for distributed tracing.
    - Spring Cloud OpenFeign: Declarative REST Client: Feign creates a dynamic implementation of an interface decorated with JAX-RS or Spring MVC annotations   
- Broker
    - Spring Cloud - Cloud Foundry Service Broker
    - Spring Cloud Open Service Broker
    - Spring Cloud App Broker
- Cloud Deployment    
    - Spring Cloud for Cloud Foundry (CLI: CF)    
    - Spring Cloud Kubernetes (CLI: kubctl)
    - Spring Cloud CLI: CLI to provide Spring Boot command line features for Spring Cloud.
- Cloud Platform
    - Spring Cloud Azure
    - Spring Cloud Alibaba
    - Spring Cloud AWS
    - Spring Cloud GCP

## Spring Cloud
- [Azure](https://spring.io/projects/spring-cloud-azure)
- [Alibaba](https://spring.io/projects/spring-cloud-alibaba)
- [AWS](https://spring.io/projects/spring-cloud-aws)
- [GCP](https://spring.io/projects/spring-cloud-gcp)
- [Cloud Foundry](https://spring.io/projects/spring-cloud-cloudfoundry)
- [Kubernetes](https://spring.io/projects/spring-cloud-kubernetes)
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
- Configuration:

![Configuration](https://static.javatpoint.com/tutorial/spring-cloud/images/components-of-spring-cloud.png)

Spring Cloud config server can use Git, SVN (Apache Subversion), filesystem, and Vault to Store config. 
Config clients (microservice app) retrieve the configuration client from the server on startup.

- Service Discover

![Service Discovery](https://static.javatpoint.com/tutorial/spring-cloud/images/components-of-spring-cloud2.png)

There are two discovery patterns: Client-side discovery and Server-side discovery.

- Circuit Breakers

![Circuit Breakers Flow](https://static.javatpoint.com/tutorial/spring-cloud/images/components-of-spring-cloud3.png)

![Close State](https://static.javatpoint.com/tutorial/spring-cloud/images/components-of-spring-cloud4.png)

![OpenState](https://static.javatpoint.com/tutorial/spring-cloud/images/components-of-spring-cloud5.png)

![HalfOpenState](https://static.javatpoint.com/tutorial/spring-cloud/images/components-of-spring-cloud6.png)

Circuit breakers calculate when to open and close the circuit and what to do in case of failure. When all services fail at some point, the circuit breaker handles these failures gracefully. The circuit breakers have three states: OPEN, CLOSED, and HALF-OPEN State.


- Routing and Messaging

![Routing and Messaging](https://static.javatpoint.com/tutorial/spring-cloud/images/components-of-spring-cloud7.png)

Spring Cloud supports communication via messaging or HTTP request. Routing uses Netflix Ribbon and Open Feign while messaging uses Kafka or Rabbit MQ.


- API Gateway

![API Gateway](https://static.javatpoint.com/tutorial/spring-cloud/images/components-of-spring-cloud8.png)

API Gateway allows us to route API request (external or internal) to connect services.

- Tracing: Sleuth/Zipkin

Tracing is a single request to get data from the application. We can add Spring Cloud Sleuth library in our project to enable tracing. Sleuth is responsible for recording timing, which is used for latency analysis. We can export this timing to Zipkin.

- CI Pipeline and Testing

### Configuration

###
Service Discovery



