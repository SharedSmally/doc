


## Run docker in cygwin/windows 10:
- set docker path to path:
```
PATH=...;C:\Program Files\Docker\Docker\resources\bin
```
- call the following command from cygwin:
```
docker-machine env --shell=bash
```
- It will show the environment variables needed by docker:
```
export DOCKER_TLS_VERIFY="1"
export DOCKER_HOST="tcp://192.168.xx.xx:2376"
export DOCKER_CERT_PATH="C:\Users\...\machines\default"
export DOCKER_MACHINE_NAME="default"
export COMPOSE_CONVERT_WINDOWS_PATHS="true"
# Run this command to configure your shell:
# eval $(docker-machine env --shell=bash)
```
- Run the following command to set the environment variables:
```
eval $(docker-machine env --shell=bash)
```
- Test
```
$docker version
```
## login centos
- Install winpty: needs mingw64-x86_64-gcc-g++; gcc-g++ and make
```
  clone the winpty repo:
git clone https://github.com/rprichard/winpty.git
  
  cd winpty directory and ran the following commands to setup the winpty package.:
  
./configure
make
make install 

- login running container:
```
winpty docker exec -i -t centos bash
```

## Add user
```
RUN useradd -d /home/ubuntu -ms /bin/bash -g root -G sudo -p ubuntu ubuntu
USER ubuntu
WORKDIR /home/ubuntu

useradd options (see: man useradd):
-d, --home-dir HOME_DIR Home directory of the new account.
-m, --create-home Create the user's home directory.
-s, --shell SHELL Login shell of the new account.
-g, --gid GROUP Name or ID of the primary group.
-G, --groups GROUPS List of supplementary groups.
-p, --password PASSWORD Encrypted password of the new account (e.g. ubuntu).
```
