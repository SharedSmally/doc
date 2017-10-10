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
vagrant home directory: ~/.vagrant.d, including box/, keys, data, gem, ...


### Vagrantfile: https://www.vagrantup.com/docs/vagrantfile/
```
Vagrant.configure("2") do |config|
   # Specifying the base box: https://www.vagrantup.com/docs/vagrantfile/machine_settings.html
   config.vm.box = "primalskill/ubuntu-trusty64"
   # how to get the Box
   config.vm.box_url = "http://sea-repolvm-1:8081/artifactory/vagrant-local/uberdev-virtualbox-centos72-0.1.0.box"
   
   # Network configurations: app in VM listening on :80, access from the host machine on :8931
   config.vm.hostname = "dev"  # set hostname
   config.vm.network :forwarded_port, guest: 80, host: 8931, auto_correct: true
   config.vm.network "private_network", ip: "172.31.40.15"   # additional nets/IPs
   
   # Syncing files
   config.vm.synced_folder "./", "/var/www", create: true, group: "www-data", owner: "www-data"
   
   # VirtualBox specific configurations: See https://virtualbox.org. :id is the virtual machine’s ID
   config.vm.provider "virtualbox" do |vb|
      vb.customize ["modifyvm", :id, "--cpuexecutioncap", "90"] # CPU utilization cap (percentage)
      vb.customize ['modifyvm', :id, '--natnet1', '172.31.39.0/24'] # default provided by vbox is typically 10.0.2.0/24
      vb.gui = false     # default is headless (but can enable autostart of the gui here)
      vb.memory = "4096" # default is 1gb 
      vb.cpus = 2        # default is 1 cpu
   end

   # Shell script provisioning
    config.vm.provision "shell",
      env: {"DEVUSERNAME" => ENV['USER']},
      inline: <<-SHELL
#!/bin/bash -v
###################################
# /etc/hosts inline setup
###################################
cat <<EOF >/etc/hosts
127.0.0.1     localhost localhost.localdomain localhost4 localhost4.localdomain4
::1           localhost localhost.localdomain localhost6 localhost6.localdomain6
172.31.39.15  uberdev  tcsapp0  aapp0  app0  dapp0  aadm0  adm0  tcsapp0.localdomain  tcsapp04  tcsapp04.localdomain4

# aliases for repos
10.32.118.67  dlprep1
10.32.118.68  dlprep2
10.32.243.80  sea-repolvm-1  artifactory
10.32.243.66  sea-perflvm-1  perforce
EOF
   # Change max files per user
   cp /vagrant/limits.conf /etc/security

   # Update rsyslog so that agents will log correctly and dev user can view
   chmod a+r /var/log/messages
   systemd-machine-id-setup
   systemctl restart systemd-journald.socket
   cp /vagrant/rsyslog.conf /etc
   systemctl restart rsyslog.service

   # Allow multicast for agent communication
   firewall-cmd --permanent --direct --add-rule ipv4 filter INPUT 0 -m udp -p udp -m pkttype --pkt-type multicast -j ACCEPT

   #############################################################
   ## database setup
   /usr/pgsql-9.5/bin/postgresql95-setup initdb
   systemctl enable postgresql-9.5

   ## $PGDATA/pg_hba.conf inline setup
   cat >/tmp/pg_hba.conf <<EOF
# TYPE  DATABASE        USER            ADDRESS                 METHOD
local   all             all                                     trust
host    all             all             127.0.0.1/32            trust
host    all             all             ::1/128                 trust
host    all             all             172.31.39.15/24         password
EOF
   su - postgres -c 'cat /tmp/pg_hba.conf >$PGDATA/pg_hba.conf'
   perl -pi -e "s|.*listen_addresses = .*|listen_addresses = '*'|g" /var/lib/pgsql/9.5/data/postgresql.conf
   systemctl restart postgresql-9.5

   ## initialize database and user
   for DBUSER in $DEVUSERNAME tcsapp; do
      cat >/tmp/pg_init.psql <<EOF
create database ${DBUSER}db;
create user ${DBUSER} with password '${DBUSER}';
grant all privileges on database ${DBUSER}db to ${DBUSER};
EOF
       su - postgres -c 'psql -f /tmp/pg_init.psql 2>/dev/null'
       su - postgres -c 'psql -c "CREATE EXTENSION adminpack;" 2>/dev/null'
     done

#############################################################
     updatedb # force refresh of locate db
   end
   
   # External script files
   config.vm.provision "shell" do |s|
       s.path "provision/setup.sh"
   end
end
```

########################
provision/setup.sh
```
#!/bin/bash

# apt-get install pkg -y > /dev/null
# yum -y -q install python-pip
# pip install <PyPI-packageList>
# gem install <gemList>
# npm install <npmList>
 
echo "Installing Git"
apt-get install git -y > /dev/null
    
echo "Installing Nginx"
apt-get install nginx -y > /dev/null

echo "Configuring Nginx"
cp /var/www/provision/config/nginx_vhost /etc/nginx/sites-available/nginx_vhost > /dev/null
ln -s /etc/nginx/sites-available/nginx_vhost /etc/nginx/sites-enabled/   
rm -rf /etc/nginx/sites-available/default
service nginx restart > /dev/null
```

########################
provision/config/nginx_vhost:
```
server {
        listen 80;
        server_name localhost;
        
        root /var/www/src/;
        index index.php index.html;
        
        # Important for VirtualBox
        sendfile off;
        
        location / {
            try_files $uri $uri/ =404;
        }
        
        location ~* \.php {
            include fastcgi_params;
            
            fastcgi_pass unix:/var/run/php5-fpm.sock;
            
            fastcgi_param SCRIPT_FILENAME $document_root$fastcgi_script_name;
            fastcgi_cache off;
            fastcgi_index index.php;
        }
    }
```
Vagrant provisions VM only once on the first run, any subsequent provisioning must be executed with the --provision flag either vagrant up --provision or vagrant reload --provision. The provisioning will re-run also if you destroy the VM and rebuild it with vagrant destroy and vagrant up.

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
- k8s + coreOS https://coreos.com/kubernetes/docs/latest/kubernetes-on-vagrant.html

- Commands:
     - vagrant package --base mybox --output /path/to/mybox.box
     - vagrant box add mybox /path/to/mybox.box
     - vagrant box list
     
### Create a new VM in VirtualBox
```
Name: vagrant-<distro><arch> i.e. vagrant-centos64
Type: Linux
Version: <distro> (64-bit)
Memory Size: 1024MB*
New Virtual Disk:
Type: VMDK (Dynamically allocated)
Max Size: 40GB
Modify the VM’s settings:

Disable audio
Disable USB
Ensure Network Adapter 1 is set to NAT
Add a port forwarding rule as follows:
Name: SSH
Protocol: TCP
Host IP:
Host Port: 2222
Guest IP:
Guest Port: 22
Mount the Linux distro ISO
```


