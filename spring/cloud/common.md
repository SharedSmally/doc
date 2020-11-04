# [Spring Cloud Commons](https://spring.io/projects/spring-cloud-commons)
- Spring Cloud Context 

Provides utilities and special services for the ApplicationContext of a Spring Cloud application (bootstrap context, encryption, refresh scope and environment endpoints).

    - Bootstrap Context
    - TextEncryptor beans
    - Refresh Scope
    - Spring Boot Actuator endpoints for manipulating the Environment

- Spring Cloud Commons

A set of abstractions and common classes used in different Spring Cloud implementations (eg. Spring Cloud Netflix vs. Spring Cloud Consul).

    - DiscoveryClient interface:  Spring Cloud Netflix Eureka, Spring Cloud Consul Discovery, and Spring Cloud Zookeeper Discovery.
    - ServiceRegistry interface: EurekaRegistration/EurekaServiceRegistry, ConsulRegistration/ConsulServiceRegistry, ZookeeperRegistration/ZookeeperServiceRegistry
```
@Configuration
@EnableDiscoveryClient(autoRegister=false)
public class MyConfiguration {
    private ServiceRegistry registry;
    public MyConfiguration(ServiceRegistry registry) {
        this.registry = registry;
    }

    // called through some external process, such as an event or a custom actuator endpoint
    public void register() {
        Registration registration = constructRegistration();
        this.registry.register(registration);
    }
}
```
    - Instrumentation for RestTemplate to resolve hostnames using DiscoveryClient
    - Use Spring RestTemplate , WebClient, WebFlux (one or multiple) as a Load Balancer Client
    
## [Document](https://spring.io/projects/spring-cloud-commons#learn)
- [Reference doc](https://docs.spring.io/spring-cloud-commons/docs/2.2.4.RELEASE/reference/html/)
