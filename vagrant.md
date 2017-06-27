## Vagrant https://www.vagrantup.com/

### Command: https://www.vagrantup.com/docs/cli/
```
Usage: vagrant [options] <command> [<args>]
    -v, --version                    Print the version and exit.
    -h, --help                       Print this help.

Common commands:
     init            initializes a new Vagrant environment by creating a Vagrantfile
     validate        validates the Vagrantfile
     
     up              starts and provisions the vagrant environment
     connect         connect to a remotely shared Vagrant environment
     destroy         stops and deletes all traces of the vagrant machine
     status          outputs status of the vagrant machine
     suspend         suspends the machine
     halt            stops the vagrant machine     
     resume          resume a suspended vagrant machine     

     box             manages boxes: installation, removal, etc.
     package         packages a running vagrant environment into a box
     global-status   outputs status Vagrant environments for this user

     help            shows the help for a subcommand
     login           log in to HashiCorp's Atlas
     plugin          manages plugins: install, uninstall, update, etc.
     port            displays information about guest port mappings
     powershell      connects to machine via powershell remoting
     provision       provisions the vagrant machine
     push            deploys code in this environment to a configured destination
     rdp             connects to machine via RDP
     reload          restarts vagrant machine, loads new Vagrantfile configuration
     share           share your Vagrant environment with anyone in the world
     snapshot        manages snapshots: saving, restoring, etc.
     ssh             connects to machine via SSH
     ssh-config      outputs OpenSSH valid configuration to connect to the machine

     vbguest
```

### Vagrant file: https://www.vagrantup.com/docs/vagrantfile/
- k8s:  
    - coreOS https://coreos.com/kubernetes/docs/latest/kubernetes-on-vagrant.html
    - git:   git clone https://github.com/coreos/coreos-kubernetes.git


### Vagrant Boxes
- Build new Box: (https://blog.engineyard.com/2014/building-a-vagrant-box):  

     Vagrant Box is a tarred, gzip image file to create a new VM. For VBox provider, it contains:
     - Vagrantfile:  information that will be merged into local Vagrantfile created when run vagrant init boxname in a folder
     - box-disk.vmdk: the virtual hard disk drive
     - box.ovf: defines the virtual hardware for the box
     - metadata.json: tells vagrant what provider the box works with
     
     Build a box from a running VM:
     - $ vagrant package --base vagrant-centos64
     
- centOS:  http://cloud.centos.org/centos/7/vagrant/x86_64/images/
- ubuntu:  https://atlas.hashicorp.com/ubuntu
- public Vagrant box catalog:: https://atlas.hashicorp.com/boxes/search
- coreOS: https://github.com/coreos/coreos-vagrant
- coreOS + kubernetes: https://github.com/coreos/coreos-kubernetes
