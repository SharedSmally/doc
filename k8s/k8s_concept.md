# [K8S Concepts](https://kubernetes.io/docs/concepts/)

## K8S Cluster
- Deployment Platforms
![Platform](https://d33wubrfki0l68.cloudfront.net/26a177ede4d7b032362289c6fccd448fc4a91174/eb693/images/docs/container_evolution.svg)
- K8S Components
![Kubernetes Components](https://d33wubrfki0l68.cloudfront.net/817bfdd83a524fed7342e77a26df18c87266b8f4/3da7c/images/docs/components-of-kubernetes.png)
- Master Nodes: responsible for maintaining the desired state for your cluster (using etcd)
    - kube-apiserver: the front end for the Kubernetes control plane to exposes the Kubernetes API.
    - etcd: Consistent and highly-available key value store used as Kubernetes’ backing store for all cluster data
    - kube-scheduler: watches newly created pods that have no node assigned, and selects a node for them to run on.
    - kube-controller-manager: runs controllers ((may in one process)
         - Node Controller: Responsible for noticing and responding when nodes go down.
         - Replication Controller: Responsible for maintaining the correct number of pods for every replication controller object in the system.
         - Endpoints Controller: Populates the Endpoints object (that is, joins Services & Pods).
         - Service Account & Token Controllers: Create default accounts and API access tokens for new namespaces.
    - cloud-controller-manager: runs controllers that interact with the underlying cloud providers.
    
- Working Nodes: the machines (VMs, physical servers, etc) that run the applications and cloud workflows
    - kubelet, which communicates with the Kubernetes Master.
    - kube-proxy, a network proxy which reflects Kubernetes networking services on each node.
    - Container Runtime: k8s supports Docker, containerd, cri-o, rktlet and any implementation of the Kubernetes CRI (Container Runtime Interface).
- [kubectl](https://kubernetes.io/docs/reference/kubectl/overview/): CLI to communicate with api-server in Master Nodes using [K8S API](https://kubernetes.io/docs/reference/kubernetes-api/api-index/)
- [Addons](https://kubernetes.io/docs/concepts/cluster-administration/addons/): use Kubernetes resources (DaemonSet, Deployment, etc) to implement cluster features, such as
    - DNS
    - Web UI (Dashboard)
    - Container Resource Monitoring
    - Cluster-level Logging


## K8S Objects
Basic Objects: Every includes two nested object fields that govern the object’s configuration: the object spec and the object status,  and metadata.
- Pod
- Service
- Volume
- Namespace

 Higher-level abstractions rely on Controllers to build upon the basic objects:
- Deployment
- DaemonSet
- StatefulSet
- ReplicaSet
- Job and CronJob
- Service
- Load Balance
- Networking (DNS, Registry)

In the .yaml file for the Kubernetes object to create, the following fields are required:
- apiVersion - Which version of the Kubernetes API you’re using to create this object
- kind - What kind of object you want to create
- metadata - Data that helps uniquely identify the object, including a name string, UID, and optional namespace
- spec - What state you desire for the object


