# [OpenStack Installation](https://docs.openstack.org/install-guide/index.html) [pdf](https://docs.openstack.org//install-guide/InstallGuide.pdf)

## prerequisite install in centos
### Networking
![networking](https://docs.openstack.org/install-guide/_images/networklayout.png)
- Management on 10.0.0.0/24 with gateway 10.0.0.1
    This network requires a gateway to provide Internet access to all nodes for administrative purposes such as package installation, security updates, DNS, and NTP.

- Provider on 203.0.113.0/24 with gateway 203.0.113.1
   This network requires a gateway to provide Internet access to instances in your OpenStack environment.

### Configure network interfaces
- Edit the **/etc/sysconfig/network-scripts/ifcfg-INTERFACE_NAME**
```
DEVICE=INTERFACE_NAME
TYPE=Ethernet
ONBOOT="yes"
BOOTPROTO="none"
```
### Configure name resolution
- Edit the **/etc/hosts**
```
# controller
10.0.0.11       controller
# compute1
10.0.0.31       compute1
# block1
10.0.0.41       block1
# object1
10.0.0.51       object1
# object2
10.0.0.52       object2
```
### NTP - Chrony
- In Coontroller Node
1. Install chrony
```
# yum install chrony
```
2. Edit **/etc/chrony.conf**:
```
server NTP_SERVER iburst
```
NTP_SERVER is hostname or IP of more accurate (lower stratum) NTP server, supports multiple server keys.
```
allow 10.0.0.0/24
```
Enable other nodes to connect to chrony daemon on the controller node. Subnet is 10.0.0.0/24.
3. Restart the NTP service:
```
# systemctl enable chronyd.service
# systemctl start chronyd.service
```
4: Verify
```
# chronyc sources
```
- In Compute Node, update **/etc/chrony.conf** to use controller NTP:
```
server controller iburst
```
### OpenStack Package
- See [https://releases.openstack.org/] for OpenStack release
- Xena (latest release)
- Wallaby
- Victoria (latet centos openstack)
- ...
```
# yum install centos-release-openstack-victoria
# yum config-manager --set-enabled PowerTools
```
For all nodes:
```
# yum upgrade
# yum install python3-openstackclient
# yum install openstack-selinux
```
### SQL Database - MySQL
```
# yum install mariadb mariadb-server python2-PyMySQL
```
Create and edit /etc/my.cnf.d/openstack.cnf file (backup existing configuration files in /etc/my.cnf.d/)
```
[mysqld]
bind-address = 10.0.0.11

default-storage-engine = innodb
innodb_file_per_table = on
max_connections = 4096
collation-server = utf8_general_ci
character-set-server = utf8
```
Finalize db setup and set the password for root.
```
# systemctl enable mariadb.service
# systemctl start mariadb.service
# mysql_secure_installation
```

### Message - Rabbit Message
```
# yum install rabbitmq-server
# systemctl enable rabbitmq-server.service
# systemctl start rabbitmq-server.service

# rabbitmqctl add_user openstack RABBIT_PASS
# rabbitmqctl set_permissions openstack ".*" ".*" ".*"
```
### MemCached
```
 # yum install memcached python3-memcached
```
Edit /etc/sysconfig/memcached 
```
OPTIONS="-l 127.0.0.1,::1,controller"
```
Eenable/start the service
```:q!

# systemctl enable memcached.service
# systemctl start memcached.service
```
### Etcd
```
# yum install etcd
```
Edit **/etc/etcd/etcd.conf**:
```
#[Member]
ETCD_DATA_DIR="/var/lib/etcd/default.etcd"
ETCD_LISTEN_PEER_URLS="http://10.0.0.11:2380"
ETCD_LISTEN_CLIENT_URLS="http://10.0.0.11:2379"
ETCD_NAME="controller"
#[Clustering]
ETCD_INITIAL_ADVERTISE_PEER_URLS="http://10.0.0.11:2380"
ETCD_ADVERTISE_CLIENT_URLS="http://10.0.0.11:2379"
ETCD_INITIAL_CLUSTER="controller=http://10.0.0.11:2380"
ETCD_INITIAL_CLUSTER_TOKEN="etcd-cluster-01"
ETCD_INITIAL_CLUSTER_STATE="new"
```
Enable/Start the service
```
# systemctl enable etcd
# systemctl start etcd
```

# sudo yum install -y https://rdoproject.org/repos/rdo-release.rpm
# yum update
# yum install -y openstack-packstack

