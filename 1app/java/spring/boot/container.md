## Spring Boot for Container

## [Container Images](https://docs.spring.io/spring-boot/docs/current/reference/html/container-images.html)
The Spring Boot executable is a fat jar, better tp unpack the fat jar and layer docker images.
Spring Boot support the following layers are supported via layers.idx:
- dependencies (for regular released dependencies, BOOT-INF/lib/\*.jar)
- spring-boot-loader (for everything under org/springframework/boot/loader)
- snapshot-dependencies (for snapshot dependencies, BOOT-INF/lib/\*SNAPSHOT.jar)
- application (for application classes and resources)

### Build Image using Dockerfile

When create a jar containing the layers index file, the spring-boot-jarmode-layertools jar is added as a dependency to the application jar. Its extract command can be used to easily split the application into layers to be added to the dockerfile. The Dockerfile:
```
FROM eclipse-temurin:11-jre as builder
WORKDIR application
ARG JAR_FILE=target/*.jar
COPY ${JAR_FILE} application.jar
RUN java -Djarmode=layertools -jar application.jar extract

FROM eclipse-temurin:11-jre
WORKDIR application
COPY --from=builder application/dependencies/ ./
COPY --from=builder application/spring-boot-loader/ ./
COPY --from=builder application/snapshot-dependencies/ ./
COPY --from=builder application/application/ ./
ENTRYPOINT ["java", "org.springframework.boot.loader.JarLauncher"]
```
To build the image:
```
$ docker build --build-arg JAR_FILE=path/to/myapp.jar .
```

## [Cloud Native Buildpacks](https://docs.spring.io/spring-boot/docs/2.7.3/maven-plugin/reference/htmlsingle/#build-image)
Spring Boot includes buildpack support directly for both Maven and Gradle:
```
<build>
    <plugins>
        <plugin>
            <groupId>org.springframework.boot</groupId>
            <artifactId>spring-boot-maven-plugin</artifactId>
            <executions>
                <execution>
                    <goals>
                        <goal>repackage</goal>
                        <goal>build-image</goal>
                    </goals>
                </execution>
            </executions>
        </plugin>
    </plugins>
</build>
```
then run the command:
```
mvn spring-boot:build-image
```
parameters:
- docker.\*
- docker.builderRegistry.\*
- docker.publishRegistry.\*
- spring-boot.build-image.\*

### [Spring Boot Maven Plugin](https://docs.spring.io/spring-boot/docs/2.7.3/maven-plugin/reference/htmlsingle/)
Run the application
```
$ mvn spring-boot:run -Dspring-boot.run.profiles=dev,local
```
Goals: Each could have many config parameters.
| Goal | 	Description |
|------|--------------|
| spring-boot:build-image | Package an application into an OCI image using a buildpack. |
| spring-boot:build-info  | Generate a build-info.properties file based on the content of the current MavenProject.|
| spring-boot:help | Display help information on spring-boot-maven-plugin. |
| spring-boot:repackage| Repackage existing JAR and WAR archives so that they can be executed from the command line using java -jar. |
|spring-boot:run | Run an application in place.|
| spring-boot:start | Start a spring application. not block for other goals, typically for integration test |
| spring-boot:stop | Stop an application that has been started by the "start" goal.|
  
