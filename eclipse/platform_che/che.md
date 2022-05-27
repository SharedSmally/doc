# Eclipse Che
Eclipse Che is a Kubernetes-native IDE and developer collaboration platform.

In Eclipse Che, the IDE is completely decoupled, it can plug a different IDE into Che workspaces: such as Theia, 

## Architecture
- Che architecture with Che server
![Che server](https://www.eclipse.org/che/docs/che-7/administration-guide/_images/architecture/che-architecture-with-che-server-engine.png)

- Che architecture with DevWorkspace
![DevWorkSpace](https://www.eclipse.org/che/docs/che-7/administration-guide/_images/architecture/che-interacting-with-devworkspace.png)

- [Installation](https://www.eclipse.org/che/docs/che-7/installation-guide/installing-che/)
    - on a local single-node cluster
```
$ bash <(curl -sL  https://www.eclipse.org/che/chectl/)
$ which chectl
$ chectl --version
$ minikube start
$ chectl server:deploy --platform=minikube     #minikube|k8s|openshift|microk8s|docker-desktop|crc
```
    - in cloud

## Tutorial
- [Document](https://www.eclipse.org/che/docs/che-7/overview/introduction-to-eclipse-che/)
- 
