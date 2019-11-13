# Spring Boot Web Service

## Samples
- [Producing a SOAP web service](https://spring.io/guides/gs/producing-web-service/)
- [Consuming a SOAP web service](https://spring.io/guides/gs/consuming-web-service/)
- [Creating a SOAP Web Service with Spring] (https://www.baeldung.com/spring-boot-soap-web-service)
- [Spring Boot SOAP Webservice Example](https://howtodoinjava.com/spring-boot/spring-boot-soap-webservice-example/)

## Expose a web service from a WSDL file and using Spring Boot
- Generate Java classes from the WSDL definition. There are a number of JAXB Maven plugins 
- Use Spring Boot to take advantage of the spring-boot-starters in order to automatically manage the different needed dependencies.
- Use Spring Web Services in combination with the maven-jaxb2-plugin plugin. 
- Use a framework like Apache CXF in combination with the cxf-codegen-plugin plugin. 
- Easiest: [Use cxf-spring-boot-starter-jaxws](https://github.com/codecentric/cxf-spring-boot-starter): (Only support one wsdl). See https://github.com/codecentric/cxf-spring-boot-starter/tree/master/cxf-spring-boot-starter-samples. See [WSImport mojo](http://www.mojohaus.org/jaxws-maven-plugin/wsimport-mojo.html) for the configurations. 
```
                <configuration>
 				    <wsdlDirectory>src/mywsdls</wsdlDirectory>
     				<wsdlFiles>
         				<wsdlFile>a.wsdl</wsdlFile>
         				<wsdlFile>b/b.wsdl</wsdlFile>
         				<wsdlFile>${project.basedir}/src/mywsdls/c.wsdl</wsdlFile>
     				</wsdlFiles>
     				<wsdlLocation>http://example.com/mywebservices/*</wsdlLocation>
 				</configuration>
```
## WSDL
The WSDL contains 5 key pieces of information:
- Types - <wsdl:types> defines the domain model used by the service. The model is defined via XSD and can be included inline, in the WSDL or imported from a separate XSD. Line 9 above imports the XSD file we created earlier.
- Message - <wsdl:message> defines the request and response messages used by the service. The nested <wsdl:part> section defines the domain types of the request and response messages.
- PortType - <wsdl:portType> defines the service operations, parameters, and response types exposed to clients.
- Binding - <wsdl:binding> defines the protocol and data format.
    - The binding type attribute refers to the portType defined earlier in the WSDL.
    - The soap binding style can be either RPC or document.
    - The transport attribute indicates that the service will be exposed over HTTP. Other options (less common) include JMS and SMTP.
    - The operation element defines each operation that we exposed through the portType.
    - Binding - <wsdl:binding> defines the protocol and data format.
- Service - <wsdl:service> defines the exposed service using the portType and binding we defined above.

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
or  generate Java classes for the domain model and service interface using the CXF codegen plugin to run a WSDL2Java job from WSDL
```

<plugin>
  <groupId>org.apache.cxf</groupId>
  <artifactId>cxf-codegen-plugin</artifactId>
  <executions>
    <execution>
      <id>generate-sources</id>
      <phase>generate-sources</phase>
      <configuration>
        <sourceRoot>src/generated/java</sourceRoot>
        <wsdlOptions>
          <wsdlOption>
            <wsdl>${basedir}/src/main/resources/wsdl/Accounts.wsdl</wsdl>
          </wsdlOption>
        </wsdlOptions>
      </configuration>
      <goals>
        <goal>wsdl2java</goal>
      </goals>
    </execution>
  </executions>
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
