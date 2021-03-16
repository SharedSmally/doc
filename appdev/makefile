#################################################################
#https://www.centos.org/centos-linux/
CENTOS_VER=8.3.2011

#https://getfedora.org/en/coreos/download
COREOS_VER=33.20210217.3.0

#https://github.com/etcd-io/etcd/releases/
ETCD_VER=v3.4.15

#https://kubernetes.io/docs/setup/release/notes/
#https://github.com/kubernetes/kubernetes
K8S_VER=v1.20.0

# https://github.com/coredns/coredns/releases/
COREDNS_VER=1.8.3

#
JAVA_VER=

#################################################################
main: etcd k8s

#################################################################
##### centos
centos:CentOS-${CENTOS_VER}-x86_64-boot.iso \

#716M
CentOS-${CENTOS_VER}-x86_64-boot.iso:
	wget http://mirror.umd.edu/centos/${CENTOS_VER}/isos/x86_64/CentOS-${CENTOS_VER}-x86_64-boot.iso -O $@
#9.26G
CentOS-${CENTOS_VER}-x86_64-dvd1.iso:
	wget http://mirror.umd.edu/centos/${CENTOS_VER}/isos/x86_64/CentOS-${CENTOS_VER}-x86_64-dvd1.iso -O $@

#### coreos
coreos:coreos.iso

# 766M
coreos.iso:
	wget https://builds.coreos.fedoraproject.org/prod/streams/stable/builds/${COREOS_VER}/x86_64/fedora-coreos-${COREOS_VER}-live.x86_64.i
so -O centos.iso

##### k8s
k8s:kubernetes.tar.gz \
    kubernetes-client-linux-amd64.tar.gz \
    kubernetes-server-linux-amd64.tar.gz \
    kubernetes-node-linux-amd64.tar.gz

kubernetes.tar.gz:
	wget https://dl.k8s.io/${K8S_VER}/kubernetes.tar.gz -O $@
kubernetes-client-linux-amd64.tar.gz:
	wget https://dl.k8s.io/${K8S_VER}/kubernetes-client-linux-amd64.tar.gz -O $@
kubernetes-server-linux-amd64.tar.gz:
	wget https://dl.k8s.io/${K8S_VER}/kubernetes-server-linux-amd64.tar.gz -O $@
kubernetes-node-linux-amd64.tar.gz:
	wget https://dl.k8s.io/${K8S_VER}/kubernetes-node-linux-amd64.tar.gz -O $@

######  etcd
etcd: etcd-${ETCD_VER}-linux-amd64.tar.gz

etcd-${ETCD_VER}-linux-amd64.tar.gz:
	wget https://storage.googleapis.com/etcd/${ETCD_VER}/etcd-${ETCD_VER}-linux-amd64.tar.gz -O $@

#### coreDNS
coreDNS:coredns_${COREDNS_VER}_linux_amd64.tgz

coredns_${COREDNS_VER}_linux_amd64.tgz:
	wget https://github.com/coredns/coredns/releases/download/v${CORE_VER}/coredns_${COREDNS_VER}_linux_amd64.tgz -O $@ 
#################################################################
