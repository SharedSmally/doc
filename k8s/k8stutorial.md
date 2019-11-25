
# Kubernetes

## [Service vs Deployment](https://matthewpalmer.net/kubernetes-app-developer/articles/service-kubernetes-example-tutorial.html)
- A deployment(no attached Volumes)/StatefulSet(with attached Volumes) is responsible for keeping a set of pods running.
- A Job/CronJob for run-on-completion of applications
- A service is responsible for enabling network access to a set of pods by selector (the running pods can be started by Deployment/StatefulSet of manually).

### Service Typs
The type property in the Service's spec determines how the service is exposed to the network. It changes where a Service is able to be accessed from. The possible types are ClusterIP, NodePort, and LoadBalancer
- ClusterIP – The default value. The service is only accessible from within the Kubernetes cluster – you can’t make requests to your Pods from outside the cluster!
- NodePort – This makes the service accessible on a static port on each Node in the cluster. This means that the service can handle requests that originate from outside the cluster.
- LoadBalancer – The service becomes accessible externally through a cloud provider's load balancer functionality. GCP, AWS, Azure, and OpenStack offer this functionality. The cloud provider will create a load balancer, which then automatically routes requests to your Kubernetes Service
