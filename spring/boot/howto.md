# Spring Boot How To 
- [Reference](https://docs.spring.io/spring-boot/docs/2.2.0.RELEASE/reference/html/howto.html)

## Properties
- Automatically Expand Properties at Build Time: Refer to the Maven ‘[project properties](http://maven.apache.org/ref/3.6.2/maven-model-builder/#Model_Interpolation)’ with @..@ placeholders
```
app.encoding=@project.build.sourceEncoding@
app.java.version=@java.version@
```
If do not use the starter parent, need to include the following element inside the <build/> element of pom.xml:
```
<resources>
    <resource>
        <directory>src/main/resources</directory>
        <filtering>true</filtering>
    </resource>
</resources>
```
and include the following element inside <plugins/>:
```
<plugin>
    <groupId>org.apache.maven.plugins</groupId>
    <artifactId>maven-resources-plugin</artifactId>
    <version>2.7</version>
    <configuration>
        <delimiters>
            <delimiter>@</delimiter>
        </delimiters>
        <useDefaultDelimiters>false</useDefaultDelimiters>
    </configuration>
</plugin>
```
- Externalize the Configuration of SpringApplication: use SpringApplicaton Java API or set properties of spring.main.* in application.properties/.yml:
```
spring.main.web-application-type=none
spring.main.banner-mode=off
```
Properties in external configuration override the values specified with the Java API, with the notable exception of the sources:
```
spring.main.sources=com.acme.Config,com.acme.ExtraConfig  # appends
spring.main.banner-mode=console
```
- Change the Location of External Properties: By default, properties from different sources are added to the Spring Environment in a defined order. Provide the following System properties (or environment variables: -Dxxx=yyy) can change the behavior:
   - spring.config.name (SPRING_CONFIG_NAME): Defaults to application as the root of the file name.
   - spring.config.location (SPRING_CONFIG_LOCATION): The file to load (such as a classpath resource or a URL). A separate Environment property source is set up for this document and it can be overridden by system properties, environment variables, or the command line
   
 - Use ‘Short’ Command Line Arguments: For example, use --port=9000 instead of --server.port=9000 to set configuration properties on the command line.
 ```
 server.port=${port:8080}
 ```
 
 -  Use YAML for External Properties: application.yml
 ```
 spring:
    application:
        name: cruncher
    datasource:
        driverClassName: com.mysql.jdbc.Driver
        url: jdbc:mysql://localhost/test
server:
    port: 9000
 ```
 - Set the Active Spring Profiles
 ```
 $ java -jar -Dspring.profiles.active=production demo-0.0.1-SNAPSHOT.jar
 ```
 or in application.properties:
 ```
spring.profiles.active=production
 ```
 - Change Configuration Depending on the Environment: YAML document contains a spring.profiles key
 ```
 server:
    port: 9000

---
spring:
    profiles: development
server:
    port: 9001

---
spring:
    profiles: production
server:
    port: 0 
 ```
 To do the same thing with properties files, you can use application-${profile}.properties to specify profile-specific values.
 
 - Discover Built-in Options for External Properties
 
 Spring Boot binds external properties from application.properties (or .yml files and other places) into an application at runtime. A running application with the Actuator features has a configprops endpoint that shows all the bound and bindable properties available through @ConfigurationProperties.
