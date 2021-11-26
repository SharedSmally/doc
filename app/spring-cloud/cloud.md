# Spring Cloud
![Architecture](https://spring.io/images/cloud-diagram-1a4cad7294b4452864b5ff57175dd983.svg)
- [Tutorial](https://www.javatpoint.com/microservices)
The services communicate with each other by using lightweight protocols such as HTTP or REST or messaging protocols.
- [Netflix](https://www.optisolbusiness.com/insight/micro-services-architecture-spring-boot-and-netflix-infrastructure)
![Netflix Architecture](https://1nwu8i3sj55rdbw4k4fm55i1-wpengine.netdna-ssl.com/wp-content/uploads/2015/09/MSArchitech.png)
- [Netflix OSS - Open Source Software](https://netflix.github.io/)

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

