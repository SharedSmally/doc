# Spring Cloud Config

Spring Cloud Config provides server-side and client-side support for externalized configuration in a distributed system,
Have a central place to manage external properties for applications across all environments. The concepts on both client 
and server map identically to the Spring Environment and PropertySource abstractions. 

The default implementation of the server storage backend uses git. Spring Cloud Config Server pulls configuration for 
remote clients from various sources. Other sources are any JDBC compatible database, Subversion, Hashicorp Vault, 
Credhub, Redis, AWS and local filesystems.

- [Reference](https://cloud.spring.io/spring-cloud-config/reference/html/)
- Config Server
- Config Client
- Implementations:
    - Vault Configuration
    - Zookeeper Configuration
    - Consul Configuration
    
## Config Server
Needs spring-cloud-config-server dependencies
- Stand up a Config Server
```
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.cloud.config.server.EnableConfigServer;

@EnableConfigServer
@SpringBootApplication
public class ConfigurationServiceApplication {
  public static void main(String[] args) {
    SpringApplication.run(ConfigurationServiceApplication.class, args);
  }
}
```
Need a Config Service to act as a sort of intermediary between Spring applications and a version-controlled repository of 
configuration files. Use Spring Cloud’s @EnableConfigServer to standup a config server that can communicate with other applications.

The Config Server needs to know which repository to manage: 
- start with a Git-based filesystem repository. 
- point the Config Server to a Github or GitLab repository
- Specify the Git repository path by spring.cloud.config.server.git.uri property in src/main/resources/application.properties:
```
server.port=8888
spring.cloud.config.server.git.uri=${HOME}/Desktop/config
spring.cloud.config.server.git.uri: file://${user.home}/config-repo  
#${user.home}/config-repo is a local git repository containing YAML and properties files.
```
spring.cloud.config.server can specify multiple resources that the config server can pull. It  has a clone of the remote git repository after check-outing branch to local repo.

On the file system, 
- Create a new directory and run git init in it. 
- Add a file called a-bootiful-client.properties to the Git repository. 
- Run git commit in it
- Connect to the Config Server with a Spring Boot application whose spring.application.name property identifies it as a-bootiful-client to the Config Server.
- Add a simple property and value (message = Hello world) to the newly created a-bootiful-client.properties file and then git commit the change.

The Config Server knows which set of configuration to send to a specific client.
It also sends all the values from any file named application.properties or application.yml in the Git repository. 
Property keys in more specifically named files (such as a-bootiful-client.properties) override those in application.properties or application.yml.


## Config Client
Needs the Config Client, Spring Boot Actuator, and Spring Web dependencies.

- In src/main/resources/application.properties:
```
management.endpoints.web.exposure.include=*
```

- In src/main/resources/bootstrap.properties to config Config Server:
```
spring.application.name=a-bootiful-client
spring.cloud.config.uri=http://localhost:8888
```

Spring sees the configuration property files, as it would any property file loaded from application.properties or application.yml or any other PropertySource
The client can access any value in the Config Server by using the traditional mechanisms (such as @ConfigurationProperties or @Value("${...}") or through the Environment abstraction). 

When Spring Cloud Config Client starts, it binds to the Config Server (via spring.cloud.config.uri in bootstrap.yml) and initializes Spring Environment with remote property sources. It consumes the Config Server with the server address set in spring.cloud.config.uri. 

The Config Service serves property sources from /{application}/{profile}/{label}:
- name = ${spring.application.name}
- profile = ${spring.profiles.active} (actually Environment.getActiveProfiles())
- label = "master"

## Refresh Config
- Update a-bootiful-client.properties, then run git commands:
```
git add -A .
git commit -m "xxx"
```
- Refresh client application: 
```
curl localhost:8080/actuator/refresh -d {} -H "Content-Type: application/json"
```
- Show the updated config value:
```
http://localhost:8080/message
```

## Push Notifications and Spring Cloud Bus
- [Refresh](https://tech.asimio.net/2017/02/02/Refreshable-Configuration-using-Spring-Cloud-Config-Server-Spring-Cloud-Bus-RabbitMQ-and-Git.html)
  ![work-flow](https://tech.asimio.net/images/config-server-spring-cloud-bus-rabbitmq-git-workflow.png); using Rabbit/Redis for PUB/SUB.
