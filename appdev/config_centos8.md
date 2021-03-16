# Configuration in centos/8:

## etcd
- Single Node: https://computingforgeeks.com/how-to-install-etcd-on-rhel-centos-8/
Download etcd
```
# Download Etcd binary
export RELEASE="3.3.13"
wget https://github.com/etcd-io/etcd/releases/download/v${RELEASE}/etcd-v${RELEASE}-linux-amd64.tar.gz

#Extract downloaded archive file.
tar xvf etcd-v${RELEASE}-linux-amd64.tar.gz

#Change to new file directory
cd etcd-v${RELEASE}-linux-amd64

#Move etcd and etcdctl binary files to /usr/local/bin directory.
sudo mv etcd etcdctl /usr/local/bin 
```
- Cluster: https://computingforgeeks.com/setup-etcd-cluster-on-centos-debian-ubuntu/

## Kubernetes cluster
- Master(s)
- Worker(s)

## K8s Cluster

## K8s services

### PostGresql

### Kafka

### Redis

### NodeJS
