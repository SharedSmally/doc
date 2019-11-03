# [Spring Boot](https://spring.io/projects/spring-boot)
Auto Config for the basic services

## Spring Boot CLI
- Install sdkman
```
$ curl -s "https://get.sdkman.io" | bash
$ source "$HOME/.sdkman/bin/sdkman-init.sh"
$ sdk version
$ sdk help
$ sdk list
```
- Install Spring Boot CLI
```
$ sdk install springboot
$ spring version
$ sdk ls springboot
$ spring help
```
- Simple Spring Boot App

app.groovy
```
@RestController
class ThisWillActuallyRun {    
    @RequestMapping("/")    
    String home() {       
        "Hello World!"    
    }
}
```
Run application
```
$spring run app.groovy
```

## Application

Common Layout: Domain Xxx class, with Repository interface, Service(using Repository to access data) and Controller(Web page to use Service to access data). data-rest automatically provides CRUD REST Controllers for Repository. 
```
com
 +- example
     +- myapplication
         +- Application.java
         |
         +- customer
         |   +- Customer.java
         |   +- CustomerController.java
         |   +- CustomerService.java
         |   +- CustomerRepository.java
         |
         +- order
             +- Order.java
             +- OrderController.java
             +- OrderService.java
             +- OrderRepository.java
```
The Application.java file declares main method(the primary @Configuration), along with the basic @SpringBootApplication:
```
package com.example.myapplication;

import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;

@SpringBootApplication
public class Application {

    public static void main(String[] args) {
        SpringApplication.run(Application.class, args);
    }
}
```
A single [@SpringBootApplication](https://docs.spring.io/spring-boot/docs/current/api/org/springframework/boot/autoconfigure/SpringBootApplication.html) annotation can be used to enable those three features, that is:
- @EnableAutoConfiguration: enable Spring Boot’s auto-configuration mechanism
- @ComponentScan: enable @Component scan on the package where the application is located
- @ConfigurationPropertiesScan: enable @ConfigurationProperties scan on the package where the application is located 
- @Configuration: allow to register extra beans in the context or import additional configuration classes


