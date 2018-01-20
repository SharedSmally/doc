# [Spring Boot](https://projects.spring.io/spring-boot/)
- 1.5.7: Spring Framework 4.0/Java 8/Servlet
- [2.0.0](https://docs.spring.io/spring-boot/docs/2.0.0.M7/reference/htmlsingle/): Spring Framework 5.0/Java 9/Reactive  

## Create pom.xml from [Initializer/Starter](https://start.spring.io/)
- Core: Security; Cache; Session; Validation; (JPA); Ops
- Web: REST;
- Web Template: Thymeleaf
- SQL: JPA + PostgreSQL(MySQL; H2; ....)
- NoSQL: (Reactive); Redis; Mongo; ...
- IO: Batch; Integration, LDAP;  ...
- Cloud 
    - Config: Config Client/Server(git/svn); Vault; Zookeeper
    - Service Discovery: 
    - Routing:
    - Circuit Breaker
    - Tracing: 
    - Messaging
    - Contract
    - AWS
    - Azure
    - Foundary
    
## Java Sample
```
import org.springframework.boot.*;
import org.springframework.boot.autoconfigure.*;
import org.springframework.web.bind.annotation.*;

@RestController
@EnableAutoConfiguration
public class Example {
	@RequestMapping("/")
	String home() {
		return "Hello World!";
	}

	public static void main(String[] args) throws Exception {
		SpringApplication.run(Example.class, args);
	}
}
```
