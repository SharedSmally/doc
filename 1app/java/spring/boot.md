# Spring Boot
Auto Configuration based on Dependencies

## Reference
- [Site](https://spring.io/projects/spring-boot/)
- [Quick Start](https://spring.io/quickstart)
- [User Guide](https://docs.spring.io/spring-boot/docs/current/reference/html/)
- [API Javadoc](https://docs.spring.io/spring-boot/docs/current/api/)
- [Starters]()
- [AutoConfig Properties](https://docs.spring.io/spring-boot/docs/current/reference/html/application-properties.html#appendix.application-properties)
    - [Auto-configuration Properties Classes](https://docs.spring.io/spring-boot/docs/current/reference/html/auto-configuration-classes.html#appendix.auto-configuration-classes)

Includes Properties for **Core, Cache, Mail, JSON, Data, Transaction, Data, Integration, Web, Templating, Server, Security, RSocket, Actuator, Devtools and
Testing**.



## Tutorial
-

## [Properties](https://docs.spring.io/spring-boot/docs/current/reference/html/configuration-metadata.html#appendix.configuration-metadata) 

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
