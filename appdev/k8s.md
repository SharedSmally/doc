# Build k8s cluster
## [Architecture]()
![](https://d33wubrfki0l68.cloudfront.net/2475489eaf20163ec0f54ddc1d92aa8d4c87c96b/e7c81/images/docs/components-of-kubernetes.svg)
- [CoreOS](https://getfedora.org/coreos?stream=stable): replaced by Fedora CoreOS: only need kernel; network-flannel; container runtime (k8os)
    - [coreos-vagrant](https://github.com/coreos/coreos-vagrant): 2018
    - [vagrant coreos](https://github.com/meltwater/vagrant-coreos)
- [Container runtime]((https://kubernetes.io/docs/setup/production-environment/container-runtimes/)): for all nodes
    - containerd
    - Docker
    - CRI-O
- [etcd](https://github.com/etcd-io/etcd/blob/release-3.4/Documentation/op-guide/clustering.md): access by master, bootstrapping via:
    - Static
    - etcd Discovery
    - DNS Discovery
- master(Control-Plane): k8os-master=k8os+master components
    - apiServer
    - controllerManager
    - scheduler
    - cloud-controller-manager
- worker: k8os-worker=k8os+worker components
    - kubelet
    - kube-proxy 
- hyberkube (docker image) 
Kubernetes is a set of daemons/binaries:
    - kube-apiserver (AKA the master),
    - kube-scheduler (resources manager)
    - kube-controller-manager (monitor RC, and maintain the desired state)
    - kubelet (start/stop containers, sync conf.),
    - kube-proxy (expose services on each node)
    - kubectl (client CLI)
The hyperkube binary is an all in one binary combining all the previously separate binaries. 
The command runs the daemon kubelet:
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
or
```
sudo docker run \
    --volume=/:/rootfs:ro \
    --volume=/sys:/sys:ro \
    --volume=/dev:/dev \
    --volume=/var/lib/docker/:/var/lib/docker:rw \
    --volume=/var/lib/kubelet/:/var/lib/kubelet:rw \
    --volume=/var/run:/var/run:rw \
    --net=host \
    --privileged=true \
    --pid=host \
    -d gcr.io/google_containers/hyperkube:v${K8S_VERSION} \
    /hyperkube kubelet \
      --api-servers=http://localhost:8080 \
      --v=2 --address=0.0.0.0 --enable-server \
      --hostname-override=127.0.0.1 \
      --config=/etc/kubernetes/manifests-multi \
      --cluster-dns=10.0.0.10 \
      --cluster-domain=cluster.local
```

## [Components](https://kubernetes.io/docs/concepts/overview/components/)
The components on a node include the kubelet, a container runtime, and the kube-proxy

### [etcd Cluster Guide](https://github.com/etcd-io/etcd/blob/release-3.4/Documentation/op-guide/clustering.md)

### [Container runtime](https://kubernetes.io/docs/setup/production-environment/container-runtimes/)
Install a container runtime into each node in the cluster:
- containerd
- Docker
- CRI-O

### flannel for cluster network

### [podman](http://docs.podman.io/en/latest/)
 Tool to find, run, build, share and deploy applications using Open Containers Initiative (OCI) Containers (including docker) and Container Images(docker image).



### Bootstrapping clusters
- [Local with kubeadm](https://kubernetes.io/docs/setup/production-environment/tools/kubeadm/)
- [AWS with kops](https://kubernetes.io/docs/setup/production-environment/tools/kops/)
- [Clouds with Kubespray](https://kubernetes.io/docs/setup/production-environment/tools/kubespray/)
- [Cloud Providers](https://kubernetes.io/docs/setup/production-environment/turnkey-solutions/)

### [kubectl cheatsheet](https://kubernetes.io/docs/reference/kubectl/cheatsheet/)
```
kubectl get svc
kubectl describe svc
kubectl delete svc
kubectl apply -f example-controller.yaml
kubectl exec -it <pod-name> -- /bin/bash
kubectl logs <pod-name>
```
- [Resource Types](https://kubernetes.io/docs/reference/kubectl/overview/#resource-types)
    - configmaps/cm
    - nodes/no
    - pods/po
    - services/svc
    - endpoints/ep
    - daemonsets/ds
    - replicasets/rs	
    - statefulsets/sts
    - cronjobs/cj
    - deployments/deploy
    - ingresses/ing
    - namespaces/ns
    - networkpolicies/netpol
    - podsecuritypolicies/psp
    - priorityclasses/pc
    - storageclasses/sc
    - persistentvolumeclaims/pvc
    - persistentvolumes/pv
    - poddisruptionbudgets/pdb
    - componentstatuses/cs
    - events/ev
    - limitranges/limits


## Setup
- [Setup k8s cluster](https://medium.com/swlh/setup-own-kubernetes-cluster-via-virtualbox-99a82605bfcc)
- [Sample 1](https://gist.github.com/danielepolencic/ef4ddb763fd9a18bf2f1eaaa2e337544)
Vagrantfile for VirtualBox and Vagrant: 
```
Vagrant.configure("2") do |config|
  config.vm.provider :virtualbox do |v|
    v.memory = 1024
    v.cpus = 1
  end

  config.vm.provision :shell, privileged: true, inline: $install_common_tools

  config.vm.define :master do |master|
    master.vm.box = "ubuntu/xenial64"
    master.vm.hostname = "master"
    master.vm.network :private_network, ip: "10.0.0.10"
    master.vm.provision :shell, privileged: false, inline: $provision_master_node
  end

  %w{worker1 worker2}.each_with_index do |name, i|
    config.vm.define name do |worker|
      worker.vm.box = "ubuntu/xenial64"
      worker.vm.hostname = name
      worker.vm.network :private_network, ip: "10.0.0.#{i + 11}"
      worker.vm.provision :shell, privileged: false, inline: <<-SHELL
sudo /vagrant/join.sh
echo 'Environment="KUBELET_EXTRA_ARGS=--node-ip=10.0.0.#{i + 11}"' | sudo tee -a /etc/systemd/system/kubelet.service.d/10-kubeadm.conf
sudo systemctl daemon-reload
sudo systemctl restart kubelet
SHELL
    end
  end

  config.vm.provision "shell", inline: $install_multicast
end


$install_common_tools = <<-SCRIPT
# bridged traffic to iptables is enabled for kube-router.
cat >> /etc/ufw/sysctl.conf <<EOF
net/bridge/bridge-nf-call-ip6tables = 1
net/bridge/bridge-nf-call-iptables = 1
net/bridge/bridge-nf-call-arptables = 1
EOF

# disable swap
swapoff -a
sed -i '/swap/d' /etc/fstab

# Install kubeadm, kubectl and kubelet
export DEBIAN_FRONTEND=noninteractive
apt-get -qq install ebtables ethtool
apt-get -qq update
apt-get -qq install -y docker.io apt-transport-https curl
curl -s https://packages.cloud.google.com/apt/doc/apt-key.gpg | apt-key add -
cat <<EOF >/etc/apt/sources.list.d/kubernetes.list
deb http://apt.kubernetes.io/ kubernetes-xenial main
EOF
apt-get -qq update
apt-get -qq install -y kubelet kubeadm kubectl
SCRIPT

$provision_master_node = <<-SHELL
OUTPUT_FILE=/vagrant/join.sh
rm -rf $OUTPUT_FILE

# Start cluster
sudo kubeadm init --apiserver-advertise-address=10.0.0.10 --pod-network-cidr=10.244.0.0/16 | grep "kubeadm join" > ${OUTPUT_FILE}
chmod +x $OUTPUT_FILE

# Configure kubectl
mkdir -p $HOME/.kube
sudo cp -i /etc/kubernetes/admin.conf $HOME/.kube/config
sudo chown $(id -u):$(id -g) $HOME/.kube/config

# Fix kubelet IP
echo 'Environment="KUBELET_EXTRA_ARGS=--node-ip=10.0.0.10"' | sudo tee -a /etc/systemd/system/kubelet.service.d/10-kubeadm.conf

# Configure flannel
curl -o kube-flannel.yml https://raw.githubusercontent.com/coreos/flannel/v0.9.1/Documentation/kube-flannel.yml
sed -i.bak 's|"/opt/bin/flanneld",|"/opt/bin/flanneld", "--iface=enp0s8",|' kube-flannel.yml
kubectl create -f kube-flannel.yml

sudo systemctl daemon-reload
sudo systemctl restart kubelet
SHELL

$install_multicast = <<-SHELL
apt-get -qq install -y avahi-daemon libnss-mdns
SHELL
```
