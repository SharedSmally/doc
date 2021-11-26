# Netflix Eureka
- [Eureka](https://github.com/Netflix/eureka)
- [Document](https://github.com/Netflix/eureka/wiki)
![Architecture](https://github.com/Netflix/eureka/raw/master/images/eureka_architecture.png)
- Components
    - Eureka Server:
    - Eureka Client for the application client: Query service registration
    - Eureka Client for the application service: Query service registration + register/renew/cancel service 
        
    Eureka Client used for Application:
    
    - Application Client which uses Eureka Client to make requests to the Application Service.
    - Application Service which receives requests from Application Client and sends a response back.

## Configuring Eureka Client
Use the property file *eureka-client.properties, eureka-client-{test,prod}.properties* in the *classpath*. [Sample Files](https://github.com/Netflix/eureka/tree/master/eureka-examples/conf)

At the minimum the following things need to be configured:
```
Application Name (eureka.name)
Application Port (eureka.port)
Virtual HostName (eureka.vipAddress)
Eureka Service Urls (eureka.serviceUrls)
```

## Configuring Eureka Server
