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
- Namespace (virtual cluster)

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

### Namespace
List the current namespaces in a cluster using:
```
kubectl get namespace
NAME          STATUS    AGE
default       Active    1d
kube-system   Active    1d
kube-public   Active    1d
```
Kubernetes starts with three initial namespaces:
- default: The default namespace for objects with no other namespace
- kube-system: The namespace for objects created by the Kubernetes system
- kube-public: This namespace is created automatically and is readable by all users (including those not authenticated).

To set the namespace for a current request, use the --namespace flag.
```
kubectl run nginx --image=nginx --namespace=<insert-namespace-name-here>
kubectl get pods --namespace=<insert-namespace-name-here>
```
or permanently save the namespace for all subsequent kubectl commands in that context
```
kubectl config set-context --current --namespace=<insert-namespace-name-here>
```
When create a Service, it creates a corresponding DNS entry of the form <service-name>.<namespace-name>.svc.cluster.local.

Not all Objects are in a Namespace. low-level resources, such as nodes and persistentVolumes, are not in any namespace.

### [Labels and Selectors](https://kubernetes.io/docs/concepts/overview/working-with-objects/labels/)
Labels can be used to select objects and to find collections of objects that satisfy certain conditions. They are key/value pairs that are attached to objects, such as pods. They are intended to be used to specify identifying attributes of objects that are meaningful and relevant to users, but do not directly imply semantics to the core system.
```
apiVersion: v1
kind: Pod
metadata:
  name: label-demo
  labels:
    environment: production
    app: nginx
```
Via a label selector, the client/user can identify a set of objects. K8S API supports two types of selectors: equality-based and set-based. A label selector can be made of multiple requirements which are comma-separated that all must be satisfied so the comma separator acts as a logical AND (&&) operator. For both equality-based and set-based conditions there is no logical OR (||) operator.

- Equality-based requirement
Equality- or inequality-based requirements allow filtering by label keys and values. Matching objects must satisfy all of the specified label constraints, though they may have additional labels as well. Three kinds of operators are admitted =,==,!=.
```
environment = production
tier != frontend
environment=production,tier!=frontend
```

- Set-based requirement (or operation)
Set-based label requirements allow filtering keys according to a set of values. Three kinds of operators are supported: in,notin and exists (only the key identifier):
```
environment in (production, qa)
tier notin (frontend, backend)
partition   #all resources including a label with key partition;no values are checked
!partition
```
Set-based requirements can be mixed with equality-based requirements:
```
partition in (customerA, customerB),environment!=qa.
```
For Service and ReplicationController:
```
selector:
    component: redis
```
For resources that support set-based requirement, such as Job, Deployment, Replica Set, and Daemon Set:
```
selector:
  matchLabels:
    component: redis
  matchExpressions:
    - {key: tier, operator: In, values: [cache]}
    - {key: environment, operator: NotIn, values: [dev]}
```
Some [recommended label names](https://kubernetes.io/docs/concepts/overview/working-with-objects/common-labels/): app.kubernetes.io/name:instance:version:component:part-of:managed-by

### [Annotations](https://kubernetes.io/docs/concepts/overview/working-with-objects/annotations/)
 Annotations are not used to identify and select objects. They are key/value pairs, and used to attach arbitrary non-identifying metadata to objects:
 ```
apiVersion: v1
kind: Pod
metadata:
  name: annotations-demo
  annotations:
    imageregistry: "https://hub.docker.com/"         
 ```
 Valid annotation keys have two segments: an optional prefix and name, separated by a slash (/). The prefix is optional. If specified, the prefix must be a DNS subdomain: a series of DNS labels separated by dots (.), not longer than 253 characters in total, followed by a slash (/). The kubernetes.io/ and k8s.io/ prefixes are reserved for Kubernetes core components. Labels without a prefix are private to users.
 
### [Field Selectors](https://kubernetes.io/docs/concepts/overview/working-with-objects/field-selectors/)
Field selectors is used tp select Kubernetes resources based on the value of one or more resource fields:
```
metadata.name=my-service
metadata.namespace!=default
status.phase=Pendin

$ kubectl get pods --field-selector status.phase=Running
```
The =, ==, and != operators can be used with field selectors (= and == mean the same thing). 
```
kubectl get services  --all-namespaces --field-selector metadata.namespace!=default
kubectl get pods --field-selector=status.phase!=Running,spec.restartPolicy=Always
```
