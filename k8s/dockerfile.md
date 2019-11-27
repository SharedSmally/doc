# Dockerfile
Dockerfile is used to build docker image. The complete reference is at https://docs.docker.com/reference/builder/:

Common commands for Dockerfile:

| Command | Description | Example  |
| ------- | ----------- |------------- |
| FROM    | First non-comment instruction in _Dockerfile_ | `FROM ubuntu`|
| COPY    | Copies mulitple source files from the context to the file system of the container at the specified path | `COPY .bash_profile /home`|
| ENV     | Sets the environment variable | `ENV HOSTNAME=test`|
| RUN     | Executes a command | `RUN apt-get update`|
| CMD     | Defaults for an executing container | `CMD ["/bin/echo", "hello world"]`|
| EXPOSE  | Informs the network ports that the container will listen on | `EXPOSE 8093`|

- [Docker for Java](https://github.com/docker/labs/tree/master/developer-tools/java/)

Docker Maven Plugin allows you to manage Docker images and containers using Maven. It comes with predefined goals:

| Goal |	Description |
| ---- | ----------- |
|docker:build|Build images||
|docker:start|Create and start containers|
|docker:stop|Stop and destroy containers|
|docker:push|Push images to a registry|
|docker:remove|Remove images from local docker host|
|docker:logs|Show container logs|

Complete set of goals are listed at https://github.com/fabric8io/docker-maven-plugin.

   - Create the Docker image:
    ```
     mvn -f docker-java-sample/pom.xml package -Pdocker
    ```
   - Run the Docker container:
    ```
    mvn -f docker-java-sample/pom.xml install -Pdocker
    ```
   - Update pom.xml to enable Docker packaging and running:
```
<profiles>
    <profile>
        <id>docker</id>
        <build>
            <plugins>
                <plugin>
                    <groupId>io.fabric8</groupId>
                    <artifactId>docker-maven-plugin</artifactId>
                    <version>0.22.1</version>
                    <configuration>
                        <images>
                            <image>
                                <name>hello-java</name>
                                <build>
                                    <from>openjdk:latest</from>
                                    <assembly>
                                        <descriptorRef>artifact</descriptorRef>
                                    </assembly>
                                    <cmd>java -cp maven/${project.name}-${project.version}.jar org.examples.java.App</cmd>
                                </build>
                                <run>
                                    <wait>
                                        <log>Hello World!</log>
                                    </wait>
                                </run>
                            </image>
                        </images>
                    </configuration>
                    <executions>
                        <execution>
                            <id>docker:build</id>
                            <phase>package</phase>
                            <goals>
                                <goal>build</goal>
                            </goals>
                        </execution>
                        <execution>
                            <id>docker:start</id>
                            <phase>install</phase>
                            <goals>
                                <goal>start</goal>
                                <goal>logs</goal>
                            </goals>
                        </execution>
                    </executions>
                </plugin>
            </plugins>
        </build>
    </profile>
</profiles>  
```

### CMD vs ENTRYPOINT

`CMD` will work for most of the cases. Default entry point for a container is `/bin/sh`, the default shell.

Running a container as `docker container run -it ubuntu` uses that command and starts the default shell:

```
> docker container run -it ubuntu
root@88976ddee107:/#
```

`ENTRYPOINT` allows to override the entry point to some other command, and even customize it:

```
> docker container run -it --entrypoint=/bin/cat ubuntu /etc/passwd
root:x:0:0:root:/root:/bin/bash
daemon:x:1:1:daemon:/usr/sbin:/usr/sbin/nologin
bin:x:2:2:bin:/bin:/usr/sbin/nologin
. . .
```

This command overrides the entry point to the container to `/bin/cat`. The argument(s) passed to the CLI are used by the entry point.

### ADD vs COPY

`COPY` will work for most of the cases. `ADD` has all capabilities of `COPY` and has the following additional features:

- Allows tar file auto-extraction in the image, for example, `ADD app.tar.gz /opt/var/myapp`.
- Allows files to be downloaded from a remote URL.

### Import and export images

Docker images can be saved using `image save` command to a `.tar` file:
```
  docker image save helloworld > helloworld.tar
```
These tar files can then be imported using `load` command:
```
  docker image load -i helloworld.tar
```
