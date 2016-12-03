docker
======

## Docker VM (hold docker container)
- VM operations:

**docker-machine _create | rm | start | stop | restart | kill_**

- VM status:

**docker-machine _active | config | env | ip | url | status | ls | inspect_**

- VM setup:

**docker-machine _upgrade | regenerate-cert | provision_**

- VM interaction:

**docker-machine _ssh|scp_**

## [Docker Image](https://docs.docker.com/engine/tutorials/dockerimages/)
 - Image docker commands
```
    images    List images
    build     Build an image from a Dockerfile
    load      Load an image from a tar archive or STDIN
    save      Save one or more images to a tar archive (streamed to STDOUT by default)
    pull      Pull an image or a repository from a registry
    push      Push an image or a repository to a registry
    rmi       Remove one or more images
    history   Show the history of an image
    search    Search the Docker Hub for images
    tag       Tag an image into a repository
    commit    Create a new image from a container's changes
    login     Log in to a Docker registry.
    logout    Log out from a Docker registry.
```    
- Build Image:
**$ docker build -f dockerfiles/Dockerfile.prod  -t myapp_prod . _**
**docker _build -t tagname(a:b) -f dockfile . _**

- List Images:

**docker _images_**


## [Docker Container]()
- container operations:

**docker _create | start | stop | restart | kill | pause | unpause | update_**
```
    docker run -t -i ubuntu:14.04 /bin/bash
```
- containers status:

**docker _ps | top | logs | stats | load | export_**

- container config:

**docker _port | network | service | volume | cp_**

- container interaction:

**docker _run | exec_**
docker run -t -i training/sinatra /bin/bash

- Hub docker:

**docker _pull | push | login | logout | commit_**


## Docker File:  [Reference](https://docs.docker.com/engine/reference/builder/)

- Build Image from docker file:
```
$ docker build .
$ docker build -f /path/to/a/Dockerfile .
```
  - Directive
```
  # directive=value1
```
  - FROM*: sets the Base Image for subsequent instructions (Each FROM create one image)
```
   FROM <image>
   FROM <image>:<tag>
   FROM <image>@<digest>
```

  - Run: execute any commands in a new layer on top of the current image and commit the results.
```
   RUN <command> (shell form, the command is run in a shell [/bin/sh -c on Linux or cmd /S /C on Windows])
   RUN ["executable", "param1", "param2"] (exec form)
```

  - CMD*: provide defaults for an executing container. only one CMD instruction in a Dockerfile
```  
  CMD ["executable","param1","param2"] (exec form, this is the preferred form)
  CMD ["param1","param2"] (as default parameters to ENTRYPOINT)
  CMD command param1 param2 (shell form)
```  
  - ENTRYPOINT*: provide defaults for an executing container. only one CMD instruction in a Dockerfile
```  
   ENTRYPOINT ["executable", "param1", "param2"] (exec form, preferred)
   ENTRYPOINT command param1 param2 (shell form)
```  

  - Expose: informs Docker that the container listens on the specified network ports at runtime
```
    EXPOSE <port> [<port>...]
```
  - VOLUME:creates a mount point and marks it as holding externally mounted volumes from native host or other containers.
```
   VOLUME ["/data"]
```
  - ADD: copy new files, directories or remote file URLs from \<src\> and adds them to the container filesystem at the path \<dest\>.
```
   ADD <src>... <dest>
   ADD ["<src>",... "<dest>"] (required for paths containing whitespace)
ex:
   ADD hom* /mydir/        # adds all files starting with "hom"
   ADD hom?.txt /mydir/    # ? is replaced with any single character, e.g., "home.txt"
```
  - COPY: copy new files, directories from \<src\> and adds them to the container filesystem at the path \<dest\>.
```
   COPY <src>... <dest>
   COPY ["<src>",... "<dest>"] (required for paths containing whitespace)
ex:
   COPY test relativeDir/   # adds "test" to `WORKDIR`/relativeDir/
   COPY test /absoluteDir/  # adds "test" to /absoluteDir/
```
  - ENV
```  
  ENV <key> <value>
  ENV <key>=<value> ...
such as:
  ENV abc=hello
  ENV abc=bye def=$abc
  ENV ghi=$abc
```
  - User: sets the user name or UID to use for running any RUN, CMD and ENTRYPOINT
```
   USER daemon
```
  - WORKDIR: sets the working directory for any RUN, CMD, ENTRYPOINT, COPY and ADD.
```
   WORKDIR /path/to/workdir
```
  - Label:  adds metadata to an image
```
  LABEL <key>=<value> <key>=<value> <key>=<value> ...
```
  - ARG:  defines a variable passed at build-time to the builder using --build-arg \<varname\>=\<value\> flag
```
   ARG <name>[=<default value>]
```
  - STOPSIGNAL:sets the system call signal that will be sent to the container to exit
```  
   STOPSIGNAL signal
```
  - HEALTHCHECK: tells Docker how to test a container to check that it is still working
```
   HEALTHCHECK [OPTIONS] CMD command (check container health by running a command inside the container)
   HEALTHCHECK NONE (disable any healthcheck inherited from the base image)
   
   The options that can appear before CMD are:
     --interval=DURATION (default: 30s)
     --timeout=DURATION (default: 30s)
     --retries=N (default: 3)
  
  ex.   
    HEALTHCHECK --interval=5m --timeout=3s \
    CMD curl -f http://localhost/ || exit 1
```

  - SHELL: allows the default shell used for the shell form of commands to be overridden. 
```
   SHELL ["executable", "parameters"]
```

  - ONBUILD: adds to the image a trigger instruction to be executed at a later time, when the image is used as the base for another build.
```  
   ONBUILD [INSTRUCTION]
ex.   
   [...]
   ONBUILD ADD . /app/src
   ONBUILD RUN /usr/local/bin/python-build --dir /app/src
   [...]
```

```
    FROM ubuntu:14.04
    RUN apt-get update
    RUN apt-get install -y curl
    EXPOSE <port> [<port>...]
    ENV PATH /usr/local/postgres-$PG_MAJOR/bin:$PATH
    
    1 FROM ubuntu
    2 ARG CONT_IMG_VER
    3 ENV CONT_IMG_VER v1.0.0
    4 RUN echo $CONT_IMG_VER

# Multiple images example
# VERSION               0.1
FROM ubuntu
RUN echo foo > bar
# Will output something like ===> 907ad6c2736f

FROM ubuntu
RUN echo moo > oink
# Will output something like ===> 695d7793cbe4

# There are two images, 907ad6c2736f with /bar, and 695d7793cbe4 with /oink.

    $ docker build --build-arg CONT_IMG_VER=v2.0.1 Dockerfile
```

When the Docker container starts, only the **CMD** command is run. The only processes that will be running inside the container is the CMD command, and all processes that it spawns.
