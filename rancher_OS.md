# [Rancher OS]()
- Start with docker machine
```
$ docker-machine create -d virtualbox \
        --virtualbox-boot2docker-url https://releases.rancher.com/os/latest/rancheros.iso \
        --virtualbox-memory 2048 \
        <MACHINE-NAME>
$ docker-machine ssh <MACHINE-NAME>  #login machine        
```
- [Rancher](https://rancher.com/): Manager k8s cluster
```
 sudo docker run -d --restart=unless-stopped -p 80:80 -p 443:443 rancher/rancher:latest
 https://<server_ip>
```
- [Rancher_OS release](https://github.com/rancher/os/releases/)
- [docker machine Release](https://github.com/docker/machine/releases/)
- Command: [*ros*]()
