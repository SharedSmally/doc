#################################################################
#https://www.centos.org/centos-linux/
CENTOS_VER=8.3.2011

#https://github.com/etcd-io/etcd/releases/
ETCD_VER=v3.4.15

#https://kubernetes.io/docs/setup/release/notes/
#https://github.com/kubernetes/kubernetes
K8S_VER=v1.20.0

#################################################################
main: etcd k8s

#################################################################
##### centos
centos:CentOS-${CENTOS_VER}-x86_64-boot.iso

CentOS-${CENTOS_VER}-x86_64-boot.iso:
	wget http://mirror.umd.edu/centos/${CENTOS_VER}/isos/x86_64/CentOS-${CENTOS_VER}-x86_64-boot.iso -o $@

##### k8s
k8s:kubernetes.tar.gz \
    kubernetes-client-linux-amd64.tar.gz \
    kubernetes-server-linux-amd64.tar.gz \
    kubernetes-node-linux-amd64.tar.gz

kubernetes.tar.gz:
	wget https://dl.k8s.io/${K8S_VER}/kubernetes.tar.gz -O $@
kubernetes-client-linux-amd64.tar.gz:
	wget https://dl.k8s.io/${K8S_VER}/kubernetes-client-linux-amd64.tar.gz -o $@
kubernetes-server-linux-amd64.tar.gz:
	wget https://dl.k8s.io/${K8S_VER}/kubernetes-server-linux-amd64.tar.gz -o $@
kubernetes-node-linux-amd64.tar.gz:
	wget https://dl.k8s.io/${K8S_VER}/kubernetes-node-linux-amd64.tar.gz -o $@

######  etcd
etcd: etcd-${ETCD_VER}-linux-amd64.tar.gz

etcd-${ETCD_VER}-linux-amd64.tar.gz:
	wget https://storage.googleapis.com/etcd/${ETCD_VER}/etcd-${ETCD_VER}-linux-amd64.tar.gz -o $@
 
#################################################################
