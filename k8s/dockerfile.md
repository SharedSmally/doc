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

