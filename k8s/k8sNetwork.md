# K8S Network

## [Service](https://kubernetes.io/docs/concepts/services-networking/service/)
Service is an abstraction that defines a logical set of Pods and a policy by which to access them (micro-service pattern). The set of Pods targeted by a Service is usually determined by a selector (created by Deployment, StatefulSet, Pods)

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

## Deployment & StatefulSet (with Persistent Volume)

## Jobs

## Pods

## k8s ports type:
- containerPort
- 



