# [Docker file](https://docs.docker.com/engine/reference/builder/)

Docker can build images automatically by reading the instructions from a Dockerfile. 
A Dockerfile is a text document that contains all the commands a user could call on the command line to assemble an image. 

The docker build command builds an image from a Dockerfile and a context. The build’s context is the set of files at a 
specified location PATH or URL. The PATH is a directory on your local filesystem. The URL is a Git repository location.

```
$ docker build -f /path/to/a/Dockerfile .
$ docker build -t shykes/myapp:1.0.2 -t shykes/myapp:latest .
```

## Docker file Format
```
# Comment
INSTRUCTION arguments
```
Docker runs instructions in a Dockerfile in order. A Dockerfile must begin with a FROM instruction. 
This may be after parser directives, comments, and globally scoped ARGs. 
The FROM instruction specifies the Parent Image from which you are building. FROM may only be preceded by one or 
more ARG instructions, which declare arguments that are used in FROM lines in the Dockerfile.

- FROM
- ENV
- RUN
- ADD
- COPY
- VOLUME
- EXPOSE
- LABEL
- STOPSIGNAL
- USER
- WORKDIR
- ONBUILD 

## Environment replacement
Environment variables can also be used in certain instructions as variables to be interpreted by the Dockerfile.

Environment variables are notated in the Dockerfile either with **$variable_name** or **${variable_name}**. They are treated equivalently and the brace syntax is typically used to address issues with variable names with no whitespace, like ${foo}_bar.

The ${variable_name} syntax also supports a few of the standard bash modifiers:
- **${variable:-word}**: if variable is set then the result will be that value. If variable is not set then word will be the result.
- **${variable:+word}**: if variable is set then word will be the result, otherwise the result is the empty string.

Environment variable substitution will use the same value for each variable throughout the entire instruction:
```
ENV abc=hello
ENV abc=bye def=$abc   # def has a value of hello, not bye
ENV ghi=$abc           # ghi has a value of bye
```

## [ADD vs COPY](https://phoenixnap.com/kb/docker-add-vs-copy)

The basic syntax for the ADD command is:
```
ADD <src> … <dest>
```
It includes the source you want to copy (<src>) followed by the destination where you want to store it (<dest>). If the source is a directory, ADD copies everything inside of it (including file system metadata).

For instance, if the file is locally available and you want to add it to the directory of an image, you type:
```
ADD /source/file/path  /destination/path
```
ADD can also copy files from a URL. It can download an external file and copy it to the wanted destination. For example:
```
ADD http://source.file/url  /destination/path
```
An additional feature is that it copies compressed files, automatically extracting the content in the given destination. This feature only applies to locally stored compressed files/directories.
```
ADD source.file.tar.gz /temp
```
Cannot download and extract a compressed file/directory from a URL. The command does not unpack external packages when copying them to the local filesystem.


COPY only has only one assigned function: duplicate files/directories in a specified location in their existing format. This means that it doesn’t deal with extracting a compressed file, but rather copies it as-is.

To use the COPY instruction, follow the basic command format:
```
COPY <src> … <dest> 
```
For example:
```
COPY /source/file/path  /destination/path 
```

If you need to copy from the local build context into a container, stick to using COPY.
To sum up – use COPY. Avoid the ADD command unless you need to extract a local tar file.

## Parser directives
The following parser directives are supported:
- syntax
- escape
### syntax
```
# syntax=[remote image reference]
```
This feature is only enabled if the BuildKit backend is used. Example:
```
# syntax=docker/dockerfile
# syntax=docker/dockerfile:1.0
# syntax=docker.io/docker/dockerfile:1
# syntax=docker/dockerfile:1.0.0-experimental
# syntax=example.com/user/repo:tag@sha256:abcdef...
```
### escape
```
# escape=\ (backslash)
```
Or
```
# escape=` (backtick)
```

## .dockerignore file
```
# comment
*/temp*
*/*/temp*
temp?
**/*.go
```
Excluded from the context:
```
*.md
!README*.md
README-secret.md
```

## FROM
```
FROM [--platform=<platform>] <image> [AS <name>]
```
Or
```
FROM [--platform=<platform>] <image>[:<tag>] [AS <name>]
```
Or
```
FROM [--platform=<platform>] <image>[@<digest>] [AS <name>]
```

## RUN: execute any commands in a new layer on top of the current image and commit the results.
```
RUN <command> (shell form, the command is run in a shell, which by default is /bin/sh -c on Linux or cmd /S /C on Windows)
```
or
```
RUN ["executable", "param1", "param2"] (exec form)
```

## CMD: provide defaults for an executing container.
```
CMD ["executable","param1","param2"] (exec form, this is the preferred form)
CMD ["param1","param2"] (as default parameters to ENTRYPOINT)
CMD command param1 param2 (shell form)
```
There can only be one CMD instruction in a Dockerfile. If you list more than one CMD then only the last CMD will take effect.

## LABEL: adds metadata to an image.
```
LABEL <key>=<value> <key>=<value> <key>=<value> ...
```
command to view image labels:
```
docker image inspect --format='' myimage
```

## EXPOSE: informs Docker that the container listens on the specified network ports at runtime
```
EXPOSE <port> [<port>/<protocol>...]
```
By default, EXPOSE assumes TCP. You can also specify UDP:
```
EXPOSE 80/udp
```
egardless of the EXPOSE settings, you can override them at runtime by using the -p flag:
```
docker run -p 80:80/tcp -p 80:80/udp ...
```

## ENV: sets the environment variable <key> to the value <value>
```
ENV <key>=<value> ...
```
The environment variables set using ENV will persist when a container is run from the resulting image. 
ARG is not persisted in the final image.

## ADD: copies new files, directories or remote file URLs and adds them to the filesystem of the image:
```
ADD [--chown=<user>:<group>] <src>... <dest>
ADD [--chown=<user>:<group>] ["<src>",... "<dest>"]
```
Multiple <src> resources may be specified but if they are files or directories, their paths are interpreted as relative to the source of the context of the build.
```
ADD hom* /mydir/
ADD hom?.txt /mydir/
ADD test.txt relativeDir/  #a relative path, <WORKDIR>/relativeDir/:
ADD test.txt /absoluteDir/

ADD --chown=55:mygroup files* /somedir/
ADD --chown=bin files* /somedir/
ADD --chown=1 files* /somedir/
ADD --chown=10:11 files* /somedir/
```

## COPY: copies new files or directories from <src> and adds them to the filesystem of the container at the path <dest> 
```
COPY [--chown=<user>:<group>] <src>... <dest>
COPY [--chown=<user>:<group>] ["<src>",... "<dest>"]
```

## ENTRYPOINT:  configure a container that will run as an executable.
```
ENTRYPOINT ["executable", "param1", "param2"]   # exec form
ENTRYPOINT command param1 param2    #shell form
```
Example:
```
FROM ubuntu
ENTRYPOINT ["top", "-b"]
CMD ["-c"]
```
Run the container
```
$ docker run -it --rm --name test  top -H
$ docker exec -it test ps aux
```
Another example:
```
FROM debian:stable
RUN apt-get update && apt-get install -y --force-yes apache2
EXPOSE 80 443
VOLUME ["/var/www", "/var/log/apache2", "/etc/apache2"]
ENTRYPOINT ["/usr/sbin/apache2ctl", "-D", "FOREGROUND"]
```
If need to write a starter script for a single executable, ensure that the final executable receives the Unix signals by using exec and gosu commands:
```
#!/usr/bin/env bash
set -e

if [ "$1" = 'postgres' ]; then
    chown -R postgres "$PGDATA"

    if [ -z "$(ls -A "$PGDATA")" ]; then
        gosu postgres initdb
    fi

    exec gosu postgres "$@"
fi

exec "$@"
```

Both CMD and ENTRYPOINT instructions define what command gets executed when running a container. There are few rules that describe their co-operation.
- Dockerfile should specify at least one of CMD or ENTRYPOINT commands.
- ENTRYPOINT should be defined when using the container as an executable.
- CMD should be used as a way of defining default arguments for an ENTRYPOINT command or for executing an ad-hoc command in a container.
- CMD will be overridden when running the container with alternative arguments.

## VOLUME: creates a mount point and marks it as holding externally mounted volumes from native host or other containers. 
```
VOLUME ["/data"]
```

## USER
```
USER <user>[:<group>]
USER <UID>[:<GID>]
```
Sets the user name (or UID) and optionally the user group (or GID) to use when running the image and for any RUN, CMD and ENTRYPOINT 
instructions that follow it in the Dockerfile

## WORKDIR
```
WORKDIR /path/to/workdir
```
Sets the working directory for any RUN, CMD, ENTRYPOINT, COPY and ADD instructions that follow it in the Dockerfile.

The WORKDIR instruction can be used multiple times in a Dockerfile. If a relative path is provided, it will be relative to the path of the previous WORKDIR instruction. 
```
WORKDIR /a
WORKDIR b
WORKDIR c
RUN pwd   #final pwd would be /a/b/c
```

## ARG
```
ARG <name>[=<default value>]
```
Defines a variable that users can pass at build-time to the builder with the docker build command using the --build-arg <varname>=<value> flag.
If a user specifies a build argument that was not defined in the Dockerfile, the build outputs a warning.
```
FROM busybox
ARG user1
ARG buildno

FROM busybox
ARG user1=someuser
ARG buildno=1

FROM ubuntu
ARG CONT_IMG_VER
RUN echo $CONT_IMG_VER
```

## ONBUILD
```
ONBUILD <INSTRUCTION>
```
Adds to the image a trigger instruction to be executed at a later time, when the image is used as the base for another build. 
The trigger will be executed in the context of the downstream build, as if it had been inserted immediately after the FROM instruction in the downstream Dockerfile.
```
ONBUILD ADD . /app/src
ONBUILD RUN /usr/local/bin/python-build --dir /app/src
```

## STOPSIGNAL
```
STOPSIGNAL signal
```
Sets the system call signal that will be sent to the container to exit. This signal can be a valid unsigned number that matches a 
position in the kernel’s syscall table, for instance 9, or a signal name in the format SIGNAME, for instance SIGKILL.

## HEALTHCHECK
```
HEALTHCHECK [OPTIONS] CMD command (check container health by running a command inside the container)
HEALTHCHECK NONE (disable any healthcheck inherited from the base image)
```
tells Docker how to test a container to check that it is still working. 
```
HEALTHCHECK --interval=5m --timeout=3s \
  CMD curl -f http://localhost/ || exit 1
```

## SHELL
```
SHELL ["executable", "parameters"]
```
Allows the default shell used for the shell form of commands to be overridden.

The SHELL instruction can appear multiple times. Each SHELL instruction overrides all previous SHELL instructions, and affects all subsequent instructions. 
```
FROM microsoft/windowsservercore

# Executed as cmd /S /C echo default
RUN echo default

# Executed as cmd /S /C powershell -command Write-Host default
RUN powershell -command Write-Host default

# Executed as powershell -command Write-Host hello
SHELL ["powershell", "-command"]
RUN Write-Host hello

# Executed as cmd /S /C echo hello
SHELL ["cmd", "/S", "/C"]
RUN echo hello
```


Can use an ARG or an ENV instruction to specify variables that are available to the RUN instruction. 
Environment variables defined using the ENV instruction always override an ARG instruction of the same name.

```
USER ${user:-some_user}

```

Docker has a set of predefined ARG variables that you can use without a corresponding ARG instruction in the Dockerfile.
- HTTP_PROXY/http_proxy
- HTTPS_PROXY/https_proxy
- FTP_PROXY/ftp_proxy
- NO_PROXY/no_proxy

The following ARG variables are set automatically:
- TARGETPLATFORM - platform of the build result. Eg linux/amd64, linux/arm/v7, windows/amd64.
- TARGETOS - OS component of TARGETPLATFORM
- TARGETARCH - architecture component of TARGETPLATFORM
- TARGETVARIANT - variant component of TARGETPLATFORM
- BUILDPLATFORM - platform of the node performing the build.
- BUILDOS - OS component of BUILDPLATFORM
- BUILDARCH - architecture component of BUILDPLATFORM
- BUILDVARIANT - variant component of BUILDPLATFORM


To use these, simply pass them on the command line using the flag:
```
--build-arg <varname>=<value>
```





