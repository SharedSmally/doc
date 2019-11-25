
# Kubernetes

## [Service vs Deployment](https://matthewpalmer.net/kubernetes-app-developer/articles/service-kubernetes-example-tutorial.html)
- A deployment(no attached Volumes)/StatefulSet(with attached Volumes) is responsible for keeping a set of pods running.
- A Job/CronJob for run-on-completion of applications
- A service is responsible for enabling network access to a set of pods by selector (the running pods can be started by Deployment/StatefulSet of manually).

### Service Typs
The type property in the Service's spec determines how the service is exposed to the network. It changes where a Service is able to be accessed from. The possible types are ExternalName, ClusterIP, NodePort, and LoadBalancer:
- ExternalName - maps to the specified externalName.
- ClusterIP – The default value. The service is only accessible from within the Kubernetes cluster – can’t make requests to your Pods from outside the cluster! ClusterIP allocates a cluster-internal IP address for load-balancing to endpoints. Endpoints are determined by the selector or if that is not specified, by manual construction of an Endpoints object. If clusterIP is "None", no virtual IP is allocated and the endpoints are published as a set of endpoints rather than a stable IP.
- NodePort – This makes the service accessible on a static port on each Node in the cluster. This means that the service can handle requests that originate from outside the cluster. NodePort builds on ClusterIP and allocates a port on every node which routes to the clusterIP.
- LoadBalancer – The service becomes accessible externally through a cloud provider's load balancer functionality. GCP, AWS, Azure, and OpenStack offer this functionality. The cloud provider will create a load balancer, which then automatically routes requests to your Kubernetes Service. LoadBalancer builds on NodePort and creates an external load-balancer which routes to the clusterIP.

 ### Service types of ports
 - nodePort - a static port assigned on each the node. The port on each node on which this service is exposed when type=NodePort or LoadBalancer. Usually assigned by the system. If specified, it will be allocated to the service if unused or else creation of the service will fail. Default is to auto-allocate a port if the ServiceType of this Service requires one.
 - port - port exposed internally in the cluster
 - targetPort - the container port to send requests to. Number or name of the port to access on the pods targeted by the service. Number must be in the range 1 to 65535. Name must be an IANA_SVC_NAME. If this is a string, it will be looked up as a named port in the target Pod's container ports. If this is not specified, the value of the 'port' field is used (an identity map). This field is ignored for services with clusterIP=None, and should be omitted or set equal to the 'port' field. 
