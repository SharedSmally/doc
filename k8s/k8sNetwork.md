# K8S Network

## [Service](https://kubernetes.io/docs/concepts/services-networking/service/)
Service is an abstraction that defines a logical set of Pods and a policy by which to access them (micro-service pattern). The set of Pods targeted by a Service is usually determined by a selector (created by Deployment, StatefulSet, Pods). See [service tutorial](https://www.bmc.com/blogs/kubernetes-services/)

### Service with selector
A service with a set of Pods that each listen on TCP port 9376 and carry a label app=MyApp:
```
apiVersion: v1
kind: Service
metadata:
  name: my-service
spec:
  selector:
    app: MyApp
  ports:
    - protocol: TCP
      port: 80
      targetPort: 9376
```
This specification creates a new Service object named “my-service”, which targets TCP port 9376 on any Pod with the app=MyApp label.

### Service without selector
```
apiVersion: v1
kind: Service
metadata:
  name: my-service
spec:
  ports:
    - protocol: TCP
      port: 80
      targetPort: 9376
```      
The corresponding Endpoint object is not created automatically for this Service has no selector. You can manually map the Service to the network address and port where it’s running, by adding an Endpoint object manually:
```
apiVersion: v1
kind: Endpoints
metadata:
  name: my-service
subsets:
  - addresses:
      - ip: 192.0.2.42
    ports:
      - port: 9376
```      
An ExternalName Service is a special case of Service that does not have selectors and uses DNS names instead.

### Service Type:
- ClusterIP: Services are reachable by pods/services in the Cluster

Exposes the Service on a cluster-internal IP. Choosing this value makes the Service only reachable from within the cluster. This is the default ServiceType. A ClusterIP exposes the following:
    - spec.clusterIp:spec.ports[*].port
    
You can only access this service while inside the cluster. It is accessible from its spec.clusterIp port. If a spec.ports[\*].targetPort is set it will route from the port to the targetPort. The CLUSTER-IP you get when calling kubectl get services is the IP assigned to this service within the cluster internally.

- NodePort: Services are reachable by clients on the same LAN/clients who can ping the K8s Host Nodes (and pods/services in the cluster)

Exposes the Service on each Node’s IP at a static port (the NodePort). A ClusterIP Service, to which the NodePort Service routes, is automatically created. You’ll be able to contact the NodePort Service, from outside the cluster, by requesting <NodeIP>:<NodePort>. A NodePort exposes the following:
    - <NodeIP>:spec.ports[*].nodePort
    - spec.clusterIp:spec.ports[*].port
  
If you access this service on a nodePort from the node's external IP, it will route the request to spec.clusterIp:spec.ports[\*].port, which will in turn route it to your spec.ports[*].targetPort, if set. This service can also be accessed in the same way as ClusterIP.

Your NodeIPs are the external IP addresses of the nodes. You cannot access your service from <ClusterIP>:spec.ports[*].nodePort.

- LoadBalancer:  Services are reachable by everyone connected to the internet.

Exposes the Service externally using a cloud provider’s load balancer. NodePort and ClusterIP Services, to which the external load balancer routes, are automatically created. A LoadBalancer exposes the following:
    - spec.loadBalancerIp:spec.ports[*].port
    - <NodeIP>:spec.ports[*].nodePort
    - spec.clusterIp:spec.ports[*].port
  
You can access this service from your load balancer's IP address, which routes your request to a nodePort, which in turn routes the request to the clusterIP port. You can access this service as you would a NodePort or a ClusterIP service as well.
  
- ExternalName: Maps the Service to the contents of the externalName field (e.g. foo.bar.example.com), by returning a CNAME record with its value. No proxying of any kind is set up.


## Deployment & StatefulSet (with Persistent Volume)

## Jobs

## Pods

## k8s ports type:
- containerPort
- 



