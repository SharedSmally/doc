# minikube
- [minikube github](https://github.com/kubernetes/minikube)
- [Document](https://minikube.sigs.k8s.io/docs/)
- [CLI reference](https://minikube.sigs.k8s.io/docs/commands/)
- [Tutorial](https://minikube.sigs.k8s.io/docs/tutorials/)
- [Handbook](https://minikube.sigs.k8s.io/docs/handbook/)

## [Start](https://minikube.sigs.k8s.io/docs/start/)
- Install minikube: 57M
```
 curl -LO https://storage.googleapis.com/minikube/releases/latest/minikube-linux-amd64
 sudo install minikube-linux-amd64 ~/app/bin/minikube
```
- Startup k8s cluster
```
minikube start  # as docker
minikube start --driver=virtualbox  # as VM box
minikube pause
minikube stop
minikube delete --all
minikube dashboard  # start a dashboard
```
- Deployment: Deploy using pod as state/stateless/daemonset include
- Deploy a server using  deployment:
```
kubectl create deployment hello-minikube --image=k8s.gcr.io/echoserver:1.4
```
- Exposing a deployment as a service using a NodePort/LoadBalance etc
```
kubectl expose deployment hello-minikube --type=NodePort --port=8080
```
- Open this exposed endpoint in your browser: Access the service endpoint
```
minikube service hello-minikube
```
- Destroy depolyment and service
```
kubectl delete deployment hello-minikube
kubectl delete service hello-minikube
```



Minikube: kubectl is now configured to use "minikube" cluster and "default" namespace by default
##
