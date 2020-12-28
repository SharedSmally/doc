# Kubernetes
- [documents](https://kubernetes.io/docs/home/)
- [API Access Control](https://kubernetes.io/docs/reference/access-authn-authz/)
- [Command line tools](https://kubernetes.io/docs/reference/command-line-tools-reference/): 
    - kubeadm
    - kubelet
    - kube-apiserver
    - kube-controller-manager
    - kube-proxy
    - kube-scheduler
- [kubectl CLI](https://kubernetes.io/docs/reference/kubectl/)
- [API reference](https://kubernetes.io/docs/reference/kubernetes-api/api-index/)

## [Components](https://kubernetes.io/docs/concepts/overview/components/)
![k8s components](https://d33wubrfki0l68.cloudfront.net/2475489eaf20163ec0f54ddc1d92aa8d4c87c96b/e7c81/images/docs/components-of-kubernetes.svg)
### Control Plane Components
- **kube-apiserver**: exposes the Kubernetes API, the front end for the Kubernetes control plane.
- **etcd**:  Consistent and highly-available key value store used as Kubernetes' backing store for all cluster data.
- **kube-scheduler**: watches for newly created Pods with no assigned node, and selects a node for them to run on.
- **kube-controller-manager**: runs controller processes. Logically, each controller is a separate process, they are all compiled into a single binary and run in a single process to reduce complexity. The controllers include:
    - **Node controller**: Responsible for noticing and responding when nodes go down.
    - **Replication controller**: Responsible for maintaining the correct number of pods for every replication controller object in the system.
    - **Endpoints controller**: Populates the Endpoints object (that is, joins Services & Pods).
    - **Service Account & Token controllers**: Create default accounts and API access tokens for new namespaces.
- **cloud-controller-manager**: embeds cloud-specific control logic, only runs controllers specific to the cloud provider. It combines several logically independent control loops into a single binary running as a single process:
    - **Node controller**: For checking the cloud provider to determine if a node has been deleted in the cloud after it stops responding
    - **Route controller**: For setting up routes in the underlying cloud infrastructure
    - **Service controller**: For creating, updating and deleting cloud provider load balancers

The running Processes:
```
sshd
lib/systemd/systemd-journald

kube-apiserver
etcd
kube-scheduler
kube-controller-manager
cloud-controller-manager
```

### Node Components
- **kubelet**: An agent runs on each node in the cluster. It makes sure that containers are running in a Pod.
- **kube-proxy**: A network proxy that runs on each node, implementing part of the Kubernetes Service concept: maintains network rules on nodes, filters or  forwards the traffic 
- **Container runtime**: responsible for running containers. supports Docker, containerd, CRI-O, and any implementation of the Kubernetes CRI (Container Runtime Interface).

The running Processes:
```
/var/lib/minikube/binaries/v1.19.4/kubelet 
/usr/bin/containerd
containerd-shim
/usr/bin/dockerd
```

### [Addons](https://kubernetes.io/docs/concepts/cluster-administration/addons/)
- **DNS**: cluster DNS serves DNS records for Kubernetes services.
- **Web UI (Dashboard)**
- **Container Resource Monitoring**: records generic time-series metrics about containers in a central database, and provides a UI for browsing that data.
- **Cluster-level Logging**: responsible for saving container logs to a central log store with search/browsing interface.
```
/coredns -conf /etc/coredns/Corefile
/dashboard --insecure-bind-address=0.0.0.0 --bind-address=0.0.0.0 
/metrics-sidecar
/storage-provisioner
```
```
root           1       0  0 16:38 ?        00:00:01 /sbin/init
root         130       1  0 16:38 ?        00:00:00 /lib/systemd/systemd-journald
root         146       1  0 16:38 ?        00:00:10 /usr/bin/containerd
root         153       1  0 16:38 ?        00:00:00 sshd: /usr/sbin/sshd -D [listener] 0 of 10-100 startups
root         165       1  3 16:38 ?        00:02:31 /usr/bin/dockerd -H tcp://0.0.0.0:2376 -H unix:///var/run/docker.sock --default-ulimit=nofile=1048
root         798       1  9 16:38 ?        00:06:49 /var/lib/minikube/binaries/v1.19.4/kubelet --bootstrap-kubeconfig=/etc/kubernetes/bootstrap-kubele
root        1711     146  0 16:38 ?        00:00:00 containerd-shim -namespace moby -workdir /var/lib/containerd/io.containerd.runtime.v1.linux/moby/a
```
```
docker@minikube:~$ ls /var/lib/minikube/binaries/v1.19.4/
kubeadm  kubectl  kubelet
docker@minikube:~$ ls /var/lib/minikube/
binaries  certs  etcd  images  kubeconfig
```

### [minikube](https://github.com/kubernetes/minikube)

