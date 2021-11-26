# Spring Cloud
![Architecture](https://spring.io/images/cloud-diagram-1a4cad7294b4452864b5ff57175dd983.svg)

## Components
- Service Discovery and Register
    - Netflix Eureka
    - HashiCorp Consul
    - Apache Zookeeper
- API Gateway
- Config 
    - Cloud Config  Server (based on git, filesystem, database,...)
    - Vault for Secrets
    - Cloud Config Client
- Load Balance
    - Server-Side LB
    - Client-Side LB (LB among list of servers in client side)
- Circuit breakers
    - Resilience4J
    - Sentinel
    - Hystrix
- Distributed Loagging
    - Sleuth 
    - Zipkin (visualialization)
- Testing
    - Spring Cloud Contract: contract-based testing support for REST and messaging-based APIs with contracts written in Groovy, Java, or Kotlin.
