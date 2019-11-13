# Spring Boot Web Service

## Samples
- [Producing a SOAP web service](https://spring.io/guides/gs/producing-web-service/)
- [Consuming a SOAP web service](https://spring.io/guides/gs/consuming-web-service/)
- [Creating a SOAP Web Service with Spring] (https://www.baeldung.com/spring-boot-soap-web-service)
- [Spring Boot SOAP Webservice Example](https://howtodoinjava.com/spring-boot/spring-boot-soap-webservice-example/)

8

## Expose a web service from a WSDL file and using Spring Boot
- Generate Java classes from the WSDL definition. There are a number of JAXB Maven plugins 
- Use Spring Boot to take advantage of the spring-boot-starters in order to automatically manage the different needed dependencies.
- Use Spring Web Services in combination with the maven-jaxb2-plugin plugin. 
- Use a framework like Apache CXF in combination with the cxf-codegen-plugin plugin. 
- Easiest: [Use cxf-spring-boot-starter-jaxws](https://github.com/codecentric/cxf-spring-boot-starter): See https://github.com/codecentric/cxf-spring-boot-starter/tree/master/cxf-spring-boot-starter-samples 

## Spring Boot
- Dependencies
```
dependency>
    <groupId>org.springframework.boot</groupId>
    <artifactId>spring-boot-starter-web-services</artifactId>
</dependency>
<dependency>
    <groupId>wsdl4j</groupId>  <!-- for publishing WSDL for our Service -->
    <artifactId>wsdl4j</artifactId>
</dependency>
```
- xjc plugin: generate java classes from XSD
```
<plugin>
    <groupId>org.codehaus.mojo</groupId>
    <artifactId>jaxb2-maven-plugin</artifactId>
    <version>1.6</version>
    <executions>
        <execution>
            <id>xjc</id>
            <goals>
                <goal>xjc</goal>
            </goals>
        </execution>
    </executions>
    <configuration>
        <schemaDirectory>${project.basedir}/src/main/resources/</schemaDirectory>
        <outputDirectory>${project.basedir}/src/main/java</outputDirectory>
        <clearOutputDir>false</clearOutputDir>
    </configuration>
</plugin>
```
- Create the SOAP Web Service Endpoint

- Configure web service beans
```
@EnableWs
@Configuration
public class WebServiceConfig extends WsConfigurerAdapter {
    @Bean
    public ServletRegistrationBean messageDispatcherServlet(ApplicationContext applicationContext) {
        MessageDispatcherServlet servlet = new MessageDispatcherServlet();
        servlet.setApplicationContext(applicationContext);
        servlet.setTransformWsdlLocations(true);
        return new ServletRegistrationBean(servlet, "/ws/*");
    }

    //http://localhost:8080/ws/services.wsdl --bean name is set to 'services'
    @Bean(name = "services")
    public Wsdl11Definition defaultWsdl11Definition() {
        SimpleWsdl11Definition wsdl11Definition = new SimpleWsdl11Definition();
        wsdl11Definition.setWsdl(new ClassPathResource("/schema/MyWsdl.wsdl")); //your wsdl location
        return wsdl11Definition;
    }
}
```
