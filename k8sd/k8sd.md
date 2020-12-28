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

### Node Components
- **kubelet**: An agent runs on each node in the cluster. It makes sure that containers are running in a Pod.
- **kube-proxy**: A network proxy that runs on each node, implementing part of the Kubernetes Service concept: maintains network rules on nodes, filters or  forwards the traffic 
- **Container runtime**: responsible for running containers. supports Docker, containerd, CRI-O, and any implementation of the Kubernetes CRI (Container Runtime Interface).

### [Addons](https://kubernetes.io/docs/concepts/cluster-administration/addons/)
- **DNS**: cluster DNS serves DNS records for Kubernetes services.
- **Web UI (Dashboard)**
- **Container Resource Monitoring**: records generic time-series metrics about containers in a central database, and provides a UI for browsing that data.
- **Cluster-level Logging**: responsible for saving container logs to a central log store with search/browsing interface.
