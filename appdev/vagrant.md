# [Vagrant](https://www.vagrantup.com/)

## [vagrant CLI](https://www.vagrantup.com/docs/cli)
- [Box](https://www.vagrantup.com/docs/cli/box)
     - list
     - add / remove
     - outdated / prune
     - repackage NAME PROVIDER VERSION
     - update

### Create a new vagrant box
- Run vagrant up to create the Virtual Machine and vagrant ssh to login.
- Install your software if not already defined in you Vagrantfile.
- Exit the VM and run ```vagrant package --base my-new-box-name --output my-new-box-name.box```. Vagrant will export the actual VM in a file.
- Run ```vagrant box add my-new-box-name file:///c:/path/to/my-new-box-name.box``` (relative path also works: file://my-new-box-name.box) to import new box.
- vagrant box list will list the new box.

## [Vagrantfile](https://www.vagrantup.com/docs/vagrantfile)
- Run ```vagrant init ``` to init the file Vagrantfile
- Update Vagrantfile
- [Install container runtime](https://kubernetes.io/docs/setup/production-environment/container-runtimes/)
#### [Install Docker in centos](https://docs.docker.com/engine/install/centos/)
- Uninstall old version docker(Docker contents is in /var/lib/docker/)
```
sudo passwd root  # set passowrd for root

 sudo yum remove docker \
                  docker-client \
                  docker-client-latest \
                  docker-common \
                  docker-latest \
                  docker-latest-logrotate \
                  docker-logrotate \
                  docker-engine
```
- Install Docker Engine(docker-ce) using repos
```
 sudo yum install -y yum-utils

 sudo yum-config-manager --add-repo https://download.docker.com/linux/centos/docker-ce.repo
 
 sudo yum install -y docker-ce docker-ce-cli containerd.io   # Install the latest version of Docker Engine and containerd, dep on python3, fuse3
 # journalctl -u sssd
 # sss_cache  -E
```
- Start Docker
```
sudo systemctl start docker
sudo systemctl enable --now docker

# systemctl unmask tmp.mount
Failed to execute operation: Access denied
```
The denial has to do with SELinux. This can be your case if you are running SELinux in enforcing mode:
```
# getenforce
Enforcing
```
/var/log/audit/audit.log shows some errors. To solve it, run:
```
kill -TERM 1
```

- Test Docker
```
sudo docker run hello-world
```
