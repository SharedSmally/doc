# Configuration in centos/8:

## etcd
- Single Node: https://computingforgeeks.com/how-to-install-etcd-on-rhel-centos-8/
```
#Step 1:  Download Etcd binary
export RELEASE="3.4.15"
#wget https://github.com/etcd-io/etcd/releases/download/v${RELEASE}/etcd-v${RELEASE}-linux-amd64.tar.gz

#Extract downloaded archive file.
tar xvf etcd-v${RELEASE}-linux-amd64.tar.gz

#Change to new file directory
cd etcd-v${RELEASE}-linux-amd64

#Move etcd and etcdctl binary files to /usr/local/bin directory.
sudo mv etcd etcdctl /usr/local/bin

#Confirm version.
#etcd --version

# Step 2: Configure Etcd Systemd service
# create data directory for etcd
sudo mkdir -p /var/lib/etcd/
sudo mkdir -p /etc/etcd

#Create etcd system user
sudo groupadd --system etcd
sudo useradd -s /sbin/nologin --system -g etcd etcd

#Set /var/lib/etcd/ directory ownership to etcd user.
sudo chown -R etcd:etcd /var/lib/etcd/

#Create a new systemd service file for etcd.
#sudo vim /etc/systemd/system/etcd.service
sudo cp /home/vagrant/etcd.service /etc/systemd/system/etcd.service

#Reload systemd service and start etcd on CentOS / RHEL system.
sudo systemctl daemon-reload
sudo systemctl start etcd.service

#If SELinux running in enforcing mode, then generate a 
#local policy module to allow access to data directories.
sudo ausearch -c '(etcd)' --raw | audit2allow -M my-etcd

#To make this policy package active, execute:
sudo semodule -X 300 -i my-etcd.pp
sudo restorecon -Rv /usr/local/bin/etcd

#Restart etcd service.
sudo systemctl restart etcd 

#Check service status to confirm it is running.
#systemctl status etcd
#The service will start on localhost address port 2379
# ss -tunelp | grep 2379
# etcdctl member list

#Step 3: Test Etcd Installation
#Test writing to etcd.
# etcdctl set /message "Hello World"
#
#Read the value of message back:
# etcdctl get /message
#Hello World

#Create directory.
# etcdctl mkdir /myservice
# etcdctl set /myservice/container1 localhost:8080
#
# etcdctl ls /myservice
#
#To watch directory for changes, use:
# etcdctl watch --recursive /myservice

#To delete the key run:
#etcdctl rm /message
#etcdctl rm /myservice/container1
```
etcd.service
```
[Unit]
Description=etcd key-value store
Documentation=https://github.com/etcd-io/etcd
After=network.target

[Service]
User=etcd
Type=notify
Environment=ETCD_DATA_DIR=/var/lib/etcd
Environment=ETCD_NAME=%m
ExecStart=/usr/local/bin/etcd
Restart=always
RestartSec=10s
LimitNOFILE=40000

[Install]
WantedBy=multi-user.target
```
- Cluster: https://computingforgeeks.com/setup-etcd-cluster-on-centos-debian-ubuntu/
Set hostname
```
# Node X
sudo hostnamectl set-hostname etcdX.domain.com --static
sudo hostname etcdX.domain.com
```
Map hostname to IP:
```
sudo tee -a /etc/hosts<<EOF
192.168.18.9  etcd1.domain.com etcd1
192.168.18.10 etcd2.domain.com etcd2
192.168.18.11 etcd3.domain.com etcd3
EOF
```
```
INT_NAME="eth0"
ETCD_HOST_IP=$(ip addr show $INT_NAME | grep "inet\b" | awk '{print $2}' | cut -d/ -f1)
ETCD_NAME=$(hostname -s)
```
- INT_NAME:the name of NIC used for cluster traffic. 
- ETCD_HOST_IP: internal IP address of the specified NIC, used to serve client requests and communicate with etcd cluster peers.
- ETCD_NAME – Each etcd member must have a unique name within an etcd cluster. Command used will set the etcd name to match the hostname of the current compute instance.
    
```
ExecStart=/usr/local/bin/etcd \\
  --name ${ETCD_NAME} \\
  --data-dir=/var/lib/etcd \\
  --initial-advertise-peer-urls http://${ETCD_HOST_IP}:2380 \\
  --listen-peer-urls http://${ETCD_HOST_IP}:2380 \\
  --listen-client-urls http://${ETCD_HOST_IP}:2379,http://127.0.0.1:2379 \\
  --advertise-client-urls http://${ETCD_HOST_IP}:2379 \\
  --initial-cluster-token etcd-cluster-0 \\
  --initial-cluster etcd1=http://etcd1:2380,etcd2=http://etcd2:2380,etcd3=http://etcd3:2380 \\
  --initial-cluster-state new \
```

## container runtime
- docker + containerd
```      

```

## Kubernetes cluster
- Master(s)
- Worker(s)

## K8s Cluster

## K8s services

### PostGresql

### Kafka

### Redis

### NodeJS
