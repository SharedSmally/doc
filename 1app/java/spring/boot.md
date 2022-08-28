# Spring Boot
Auto Configuration based on Dependencies

## Reference
- [Site](https://spring.io/projects/spring-boot/)
- [Quick Start](https://spring.io/quickstart)
- [User Guide](https://docs.spring.io/spring-boot/docs/current/reference/html/)
- [API Javadoc](https://docs.spring.io/spring-boot/docs/current/api/)
- [Starters](https://docs.spring.io/spring-boot/docs/current/reference/html/using.html#using.build-systems.starters): spring-boot-starter-\*, a set of convenient dependency descriptors that can be included in the application. 
- [AutoConfig Properties](https://docs.spring.io/spring-boot/docs/current/reference/html/application-properties.html#appendix.application-properties):
Core,Cache,Mail,JSON,Data,Transaction,Data,Integration,Web,Templating,Server,Security,RSocket,Actuator,Devtools and Testing.
- [Auto-configuration Classes](https://docs.spring.io/spring-boot/docs/current/reference/html/auto-configuration-classes.html#appendix.auto-configuration-classes)
- [Test Auto Configuration Annotations](https://docs.spring.io/spring-boot/docs/current/reference/html/test-auto-configuration.html#appendix.test-auto-configuration):
@DataCassandraTest,@DataCouchbaseTest,@DataElasticsearchTest,@DataJdbcTest,@DataJpaTest,@DataLdapTest,@DataMongoTest,@DataNeo4jTest,@DataR2dbcTest,@DataRedisTest,@GraphQlTest,@JdbcTest,@JooqTest,@JsonTest,@RestClientTest,@WebFluxTest,@WebMvcTest,@WebServiceClientTest,@WebServiceServerTest
- [Dependency Versions](https://docs.spring.io/spring-boot/docs/current/reference/html/dependency-versions.html#appendix.dependency-versions)

## Tutorial



## Misc
### [Production-ready Features](https://docs.spring.io/spring-boot/docs/current/reference/html/actuator.html)

### [Deploying Spring Boot Applications](https://docs.spring.io/spring-boot/docs/current/reference/html/deployment.html)

### [Spring Boot CLI](https://docs.spring.io/spring-boot/docs/current/reference/html/cli.html)

### [Build Tool Plugins](https://docs.spring.io/spring-boot/docs/current/reference/html/build-tool-plugins.html)

### [How-to Guides](https://docs.spring.io/spring-boot/docs/current/reference/html/howto.html)




## [Properties](https://docs.spring.io/spring-boot/docs/current/reference/html/configuration-metadata.html#appendix.configuration-metadata) sample
```java
import org.springframework.boot.context.properties.ConfigurationProperties;
import org.springframework.boot.context.properties.DeprecatedConfigurationProperty;

@ConfigurationProperties("my.app")
public class MyProperties {
    private String name;
    public String getName() {
        return this.name;
    }
    public void setName(String name) {
        this.name = name;
    }
    @Deprecated
    @DeprecatedConfigurationProperty(replacement = "my.app.name")
    public String getTarget() {
        return this.name;
    }
    @Deprecated
    public void setTarget(String target) {
        this.name = target;
    }
}
```
## Auto Configuration
