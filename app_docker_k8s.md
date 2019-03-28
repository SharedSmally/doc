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
#relogin and run docker info for system info.
#docker related data are stored in /var/lib/docker, 
# containers  image  network  overlay2  plugins  swarm  tmp  trust  volumes
```
- Start a docker container
```
docker run hello-world
docker ps -a
```

# k8s
