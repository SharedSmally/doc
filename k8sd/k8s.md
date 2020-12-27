# Kerbenetes

## [Service](https://kubernetes.io/docs/concepts/services-networking/service/)

A service enables network access to a set of Pods in Kubernetes.

Services select Pods based on their labels. When a network request is made to the service, it selects all Pods in the cluster 
matching the service's selector, chooses one of them, and forwards the network request to it.

![service](https://matthewpalmer.net/kubernetes-app-developer/articles/service-annotated.png)

The type property in the Service's spec determines how the service is exposed to the network. 
It changes where a Service is able to be accessed from. The possible types are ClusterIP, NodePort, and LoadBalancer.

- ClusterIP – The default value. The service is only accessible from within the Kubernetes cluster – you can’t make requests to your Pods from outside the cluster!
- NodePort – This makes the service accessible on a static port on each Node in the cluster. This means that the service can handle requests that originate from outside the cluster.
- LoadBalancer – The service becomes accessible externally through a cloud provider's load balancer functionality. GCP, AWS, Azure, and OpenStack offer this functionality. The cloud provider will create a load balancer, which then automatically routes requests to your Kubernetes Service

selector: When the node receives a request on the static port (30163), "select pods with the label 'app' set to 'echo-hostname'", and forward the request to one of them
  
Three types of ports for a service (in ports):
- nodePort - a static port assigned on each the node
- port - port exposed internally in the cluster
- targetPort - the container port to send requests to


## [Deployment](https://kubernetes.io/docs/concepts/workloads/controllers/deployment/)
```
apiVersion: apps/v1
kind: Deployment
metadata:
  name: nginx-deployment
  labels:
    app: nginx
spec:
  replicas: 3
  selector:
    matchLabels:
      app: nginx
  template:
    metadata:
      labels:
        app: nginx
    spec:
      containers:
      - name: nginx
        image: nginx:1.14.2
        ports:
        - containerPort: 80
```



## Service vs Deployment

A service is responsible for enabling network access to a set of pods. 

A deployment is responsible for keeping a set of pods running.

We could use a deployment without a service to keep a set of identical pods running in the Kubernetes cluster. 
The deployment could be scaled up and down and pods could be replicated. Each pod could be accessed individually 
via direct network requests (rather than abstracting them behind a service), but keeping track of this for a
lot of pods is difficult.

We could also use a service without a deployment. We'd need to create each pod individually (rather than "all-at-once"
like a deployment). Then our service could route network requests to those pods via selecting them based on their labels.

Services and Deployments are different, but they work together nicely.

 
