# Spring Cloud
![Architecture](https://spring.io/images/cloud-diagram-1a4cad7294b4452864b5ff57175dd983.svg)
- [Web Site](https://spring.io/projects/spring-cloud)
- [Tutorial](https://www.javatpoint.com/microservices)
The services communicate with each other by using lightweight protocols such as HTTP or REST or messaging protocols.
- [Netflix](https://www.optisolbusiness.com/insight/micro-services-architecture-spring-boot-and-netflix-infrastructure)
![Netflix Architecture](https://1nwu8i3sj55rdbw4k4fm55i1-wpengine.netdna-ssl.com/wp-content/uploads/2015/09/MSArchitech.png)
- [Netflix OSS - Open Source Software](https://netflix.github.io/)

| Application |	Port |
|-------------|------|
|Spring Cloud Config Server  | 8888 |
|Netflix Eureka Naming Server | 8761 |
|Netflix Zuul API gateway Server |	8765 |
|Zipkin distributed Tracing Server |	9411 |

## Main Projects

- **Spring Cloud Config**

Centralized external configuration management backed by a git repository. The configuration resources map directly to Spring Environment but could be used by non-Spring applications if desired.

- **Spring Cloud Netflix**

Integration with various Netflix OSS components (Eureka, Hystrix, Zuul, Archaius, etc.).

- **Spring Cloud Zookeeper**

Service discovery and configuration management with Apache Zookeeper.

- **Spring Cloud Cloudfoundry**

Integrates your application with Pivotal Cloud Foundry. Provides a service discovery implementation and also makes it easy to implement SSO and OAuth2 protected resources.

- **Spring Cloud Open Service Broker**

Provides a starting point for building a service broker that implements the Open Service Broker API.

- **Spring Cloud Consul**

Service discovery and configuration management with Hashicorp Consul.

- **Spring Cloud Sleuth**

Distributed tracing for Spring Cloud applications, compatible with Zipkin, HTrace and log-based (e.g. ELK) tracing.

- **Spring Cloud OpenFeign**

Spring Cloud OpenFeign provides integrations for Spring Boot apps through autoconfiguration and binding to the Spring Environment and other Spring programming model idioms.

## Starter Projects
- **Spring Cloud Starters**

Spring Boot-style starter projects to ease dependency management for consumers of Spring Cloud. (Discontinued as a project and merged with the other projects after Angel.SR2.)

- **Spring Cloud Task App Starters**

Spring Cloud Task App Starters are Spring Boot applications that may be any process including Spring Batch jobs that do not run forever, and they end/stop after a finite period of data processing.

- **Spring Cloud CLI**

Spring Boot CLI plugin for creating Spring Cloud component applications quickly in Groovy

## Common Projects
- **Spring Cloud Bus**

An event bus for linking services and service instances together with distributed messaging. Useful for propagating state changes across a cluster (e.g. config change events).

- **Spring Cloud Data Flow**

A cloud-native orchestration service for composable microservice applications on modern runtimes. Easy-to-use DSL, drag-and-drop GUI, and REST-APIs together simplifies the overall orchestration of microservice based data pipelines.

- **Spring Cloud Stream**

A lightweight event-driven microservices framework to quickly build applications that can connect to external systems. Simple declarative model to send and receive messages using Apache Kafka or RabbitMQ between Spring Boot apps.

- **Spring Cloud Stream Applications**

Spring Cloud Stream Applications are out of the box Spring Boot applications providing integration with external middleware systems such as Apache Kafka, RabbitMQ etc. using the binder abstraction in Spring Cloud Stream.

- **Spring Cloud Task**

A short-lived microservices framework to quickly build applications that perform finite amounts of data processing. Simple declarative for adding both functional and non-functional features to Spring Boot apps.

- **Spring Cloud Pipelines**

Spring Cloud Pipelines provides an opinionated deployment pipeline with steps to ensure that your application can be deployed in zero downtime fashion and easilly rolled back of something goes wrong.

- **Spring Cloud Function**

Spring Cloud Function promotes the implementation of business logic via functions. It supports a uniform programming model across serverless providers, as well as the ability to run standalone (locally or in a PaaS).


- **Spring Cloud Cluster**

Leadership election and common stateful patterns with an abstraction and implementation for Zookeeper, Redis, Hazelcast, Consul.

- **Spring Cloud Security**

Provides support for load-balanced OAuth2 rest client and authentication header relays in a Zuul proxy.

- **Spring Cloud Gateway**

Spring Cloud Gateway is an intelligent and programmable router based on Project Reactor.

- **Spring Cloud Connectors**

Makes it easy for PaaS applications in a variety of platforms to connect to backend services like databases and message brokers (the project formerly known as "Spring Cloud").


- **Spring Cloud Contract**

Spring Cloud Contract is an umbrella project holding solutions that help users in successfully implementing the Consumer Driven Contracts approach.


## Principles of Microservices
- Single Responsibility principle
- Modelled around business domain
- Isolate Failure
- Infrastructure automation
- Deploy independently

## Microservices Monitoring Tool
- Hystrix dashboard
- Eureka admin dashboard
- Spring boot admin dashboard 

## Components of Microservices
- Spring Cloud Config Server
- Netflix Eureka Naming Server (Service Discovery)
- Hystrix Server (Circuit Breakers)
- Netflix Zuul API Gateway Server 
- Netflix Ribbon(Dynamic Routing and Load Balancer)
- Zipkin Distributed Tracing Server

## Components
- Service Discovery and Register
    - Netflix Eureka
    - HashiCorp Consul
    - Apache Zookeeper
- API Gateway
    - Netflix Zuul
- Config 
    - Cloud Config  Server (based on git, filesystem, database,...)
    - Vault for Secrets
    - Cloud Config Client
- Load Balance
    - Netflix Zuul : Server-Side LB
    - Client-Side LB (LB among list of servers in client side)
- Circuit breakers
    - Hystrix
    - Resilience4J
    - Sentinel
- Distributed Loagging
    - Sleuth 
    - Zipkin (visualialization)
- Testing
    - Spring Cloud Contract: contract-based testing support for REST and messaging-based APIs with contracts written in Groovy, Java, or Kotlin.

## Major Components of Netflix
- Netflix Eureka – Service Discovery Server

Netflix Eureka allows microservices to register themselves at runtime as they appear in the system landscape.

- Netflix Ribbon – Dynamic Routing & Load BalancerNetflix Ribbon

Netflix Ribbon can be used by service consumers to lookup services at runtime. Ribbon uses the information available in Eureka to locate appropriate service instances. If more than one instance is found, Ribbon will apply load balancing to spread the requests over the available instances. The ribbon does not run as a separate service but instead as an embedded component in each service consumer.

- Netflix Zuul – Edge Server

Zuul is the gatekeeper to the outside world, not allowing any unauthorized external requests to pass through. Zulu also provides a well-known entry point to the microservices in the system landscape. Using dynamically allocated ports is convenient to avoid port conflicts and to minimize administration but it makes it of course harder for any given service consumer. Zuul uses Ribbon to look up available services and routes the external request to an appropriate service instance.

