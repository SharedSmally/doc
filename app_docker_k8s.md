# docker
- Install docker: 
```
sudo yum install -y docker
```
- Start docker daemon:
```
sudo systemctl start docker
sudo systemctl status docker
sudo systemctl enable docker
```
- Enable user to use docker
```
sudo groupadd docker
sudo usermod -aG docker $(whoami)
#relogin;  docker related data are stored in /var/lib/docker, 
# containers  image  network  overlay2  plugins  swarm  tmp  trust  volumes
```
- docker info
```
docker info  # system info
docker stats|logs|diff|events|inspect # container stats
```
- docker image
```
docker images
docker history
docker pull/push _image_  (from remote repository)
docker build/commit (from Dockerfile or a container )
docker export/import (from running container as tar file)
docker save/load (from image tar file)
docker tag|rmi 
docker login/logout|search
```
- docker container
```
docker ps | top 
docker exec command
docker run hello-world
docker create|kill|attach
docker start|stop|restart|rm
docker pause|unpause|wait|rename
docker cp
docker port
```
- Login a container:
Start a container, and let it running (both are the same):
```
docker run -dt centos:7
docker run -dt centos:7 /bin/bash
```
Using the following command to exec the command in the container:
        - Use *docker ps* to get the name of the existing container
        - Use *docker exec -it \<container name\> /bin/bash* to get a bash shell in the container
        - Use *docker exec -it \<container name\> <command>* to execute command  in the container.


# k8s
