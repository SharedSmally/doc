# coreos
- init management: systemd
- cluster management: etcd
- container: containerd; dockerd; rkt
- master: apiserver; controller-manager; scheduler; proxy (hyperkube)
- nodes: kubelet; proxy

## coreos vagrant
k8s-coreos cluster: build with Vagrant at https://github.com/pires/kubernetes-vagrant-coreos-cluster
- Run in Linux; Need to install nfs server and client packages:
```
Server:
   sudo apt-get update
   sudo apt-get install nfs-kernel-server
Client:
   sudo apt-get update
   sudo apt-get install nfs-common
Start Cluster:
   vagrant up
Login master:
   vagrant ssh master
Login workers: node-01;node-02
   vagrant ssh node-01
```


### coreos vagrant
- Conflicting dependecies[fog-core]: Update vagarnt to latest version
```
wget -c https://releases.hashicorp.com/vagrant/2.2.3/vagrant_2.2.3_x86_64.deb
sudo dpkg -i vagrant_2.2.3_x86_64.deb
```
- clone
```
 git clone https://github.com/coreos/coreos-vagrant
 cd coreos-vagrant/
 cp config.rb.sample config.rb
 vi config.rb to change instatnce number to 3
 cp config.ign.sample config.ign
 curl https://discovery.etcd.io/new?size=3
 vi config.ign to update token form curl.
 vagrant up
 vagrant status
 vagrant ssh core-01
 core-01 $ etcdctl member list
```

## [hypecube](https://github.com/kubernetes/kubernetes/tree/master/cluster/images/hyperkube)
Kubernetes is a set of daemons/binaries:
- kube-apiproxy (AKA the master),
- kube-scheduler (resources manager)
- kube-controller-manager (monitor RC, and maintain the desired state)
- kubelet (start/stop containers, sync conf.),
- kube-proxy (expose services on each node)

The hyperkube binary is an all in one binary (in a way similar to busybox), combining all the previously separate binaries.
The following command:
```
hyperkube kubelet \
  --api-servers=http://localhost:8080 \
  --v=2 \
  --address=0.0.0.0 \
  --enable-server \
  --hostname-override=127.0.0.1 \
  --config=/etc/kubernetes/manifests-multi \
  --cluster-dns=10.0.0.10 \
  --cluster-domain=cluster.local
```
runs the daemon kubelet. So hyperkube in a nutshell is the core for all services and the sole purpose of this hyperkube is to manage all the services inside the Kubernetes cluster so kinda simplify the deployment.
