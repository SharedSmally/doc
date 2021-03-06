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

## Tips
- [run-cmd-entry](https://goinbigdata.com/docker-run-vs-cmd-vs-entrypoint/)
    - RUN executes command(s) in a new layer and creates a new image. often used for installing software packages.
    - CMD sets default command and/or parameters, which can be overwritten from command line when docker container runs.
    - ENTRYPOINT configures a container that will run as an executable (default command). optional configs are specified in CMD

- [add vs copy](https://medium.com/@Grigorkh/dockerfile-add-vs-copy-d120e72d09dd)
    - COPY takes in a src and destination. It only copy a local file or directory from host into the Docker image
    - ADD can do the same, but it also supports 2 other sources: use a URL instead of a local file/director, or extract a tar file from the source directly into the destination.

## dockerfile format: # for comments
- FROM

Initializes a new build stage and sets the Base Image for subsequent instructions. ARG is the only instruction that may precede FROM in the Dockerfile. FROM can appear multiple times within a single Dockerfile to create multiple images or use one build stage as a dependency for another. 
```
FROM <image> [AS <name>]
FROM <image>[:<tag>] [AS <name>]
FROM <image>[@<digest>] [AS <name>]
```

- RUN
```
RUN <command> (shell form, the command is run in a shell, default is /bin/sh -c on Linux or cmd /S /C on Windows)
RUN ["executable", "param1", "param2"] (exec form)
```

- CMD
```
CMD ["executable","param1","param2"] (exec form, this is the preferred form)
CMD ["param1","param2"] (as default parameters to ENTRYPOINT)
CMD command param1 param2 (shell form)
```

- LABEL
```
LABEL <key>=<value> <key>=<value> <key>=<value> ...
```

- EXPOSE: protocol=TCP or UDP
```
EXPOSE <port> [<port>/<protocol>...]
```

- ENV
```
ENV <key> <value>
ENV <key>=<value> ...
```

- ADD
```
ADD [--chown=<user>:<group>] <src>... <dest>
ADD [--chown=<user>:<group>] ["<src>",... "<dest>"] (required for paths containing whitespace)
```

- COPY
```
COPY [--chown=<user>:<group>] <src>... <dest>
COPY [--chown=<user>:<group>] ["<src>",... "<dest>"] (required for paths containing whitespace)
```  

- ENTRYPOINT
```
ENTRYPOINT ["executable", "param1", "param2"] (exec form, preferred)
ENTRYPOINT command param1 param2 (shell form)
```

- VOLUME
```
VOLUME ["/data"]
```

- USER
```
USER <user>[:<group>] or
USER <UID>[:<GID>]
```

- WORKDIR
```
WORKDIR /path/to/workdir
```

- ARG
```
ARG <name>[=<default value>]
```

- ONBUILD
```
ONBUILD [INSTRUCTION]
```

- STOPSIGNAL
```
STOPSIGNAL signal
```

- HEALTHCHECK
```
HEALTHCHECK [OPTIONS] CMD command (check container health by running a command inside the container)
HEALTHCHECK NONE (disable any healthcheck inherited from the base image)
```

- SHELL
```
SHELL ["executable", "parameters"]
```

## Environment replacement
Environment variables (declared with the ENV statement) can be used in certain instructions as variables to be interpreted by the Dockerfile. Escapes are also handled for including variable-like syntax into a statement literally.

Environment variables are notated in the Dockerfile either with ```$variable_name``` or ```${variable_name}```. They are treated equivalently and the brace syntax is typically used to address issues with variable names with no whitespace, like ${foo}_bar.

## docker build: Build an image from a Dockerfile

The docker build command builds an image from a Dockerfile and a context. The build’s context is the set of files at a specified location PATH or URL. The PATH is a directory on your local filesystem. The URL is a Git repository location.
```
Usage:  docker build [OPTIONS] PATH | URL | -
  -f, --file=                     Name of the Dockerfile (Default is 'PATH/Dockerfile')
  -t, --tag=                      Repository name (and optionally a tag) for the image
  --build-arg=[]                  Set build-time variables
  --cpu-shares=0                  CPU shares (relative weight)
  --cgroup-parent=                Optional parent cgroup for the container
  --cpu-period=0                  Limit the CPU CFS (Completely Fair Scheduler) period
  --cpu-quota=0                   Limit the CPU CFS (Completely Fair Scheduler) quota
  --cpuset-cpus=                  CPUs in which to allow execution (0-3, 0,1)
  --cpuset-mems=                  MEMs in which to allow execution (0-3, 0,1)
  -m, --memory=                   Memory limit
  --memory-swap=                  Total memory (memory + swap), '-1' to disable swap
  --disable-content-trust=true    Skip image verification
  --force-rm=false                Always remove intermediate containers
  --help=false                    Print usage
  --no-cache=false                Do not use cache when building the image
  --pull=false                    Always attempt to pull a newer version of the image
  -q, --quiet=false               Suppress the verbose output generated by the containers
  --rm=true                       Remove intermediate containers after a successful build
  --ulimit=[]                     Ulimit options
```

The build is run by the Docker daemon, not by the CLI. The first thing a build process does is send the entire context (recursively) to the daemon. In most cases, it’s best to start with an empty directory as context and keep your Dockerfile in that directory. Add only the files needed for building the Dockerfile.

To use a file in the build context, the Dockerfile refers to the file specified in an instruction, for example, a COPY instruction. To increase the build’s performance, exclude files and directories by adding a .dockerignore file to the context directory. For information about how to create a .dockerignore file see the documentation on this page.

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
