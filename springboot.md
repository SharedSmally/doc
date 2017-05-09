# Spring Boot

## Generate jar file:
- $ mvn package
- $ mvn package spring-boot:repackage

## Start Spring Boot App without compiling:
- java -Dserver.port=9999 -jar **.jar
-  mvn spring-boot:run -Dserver.port=9999

The App prints the random generated password. User name=user
Change the password by providing a security.user.password 
The default in Spring Boot to “user” and a random password(print in the log).

## Spring boot App metrics: (using Actuator)
- http://localhost:9999/metrics: Check app metrics (using Actuator)
- http://localhost:9999/trace: Check Http Trace
-  /mappings; /info; //auditevents; /health; /configprops; /loggers/; /env; /beans 

# Set the main class:
```
<build>
<plugins>
    <plugin>
        <groupId>org.springframework.boot</groupId>
        <artifactId>spring-boot-maven-plugin</artifactId>
        <configuration>
            <mainClass>myPackage.HelloWorld</mainClass> 
        </configuration>
    </plugin>
    <plugin>
        <artifactId>maven-compiler-plugin</artifactId>
        <configuration>
            <fork>true</fork>
            <executable>D:\jdk1.8\bin\javaw.exe</executable>
        </configuration>
    </plugin>
</plugins>
</build>
```
