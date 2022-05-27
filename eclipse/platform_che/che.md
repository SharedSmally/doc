# Eclipse Che
Eclipse Che is a Kubernetes-native IDE and developer collaboration platform.

In Eclipse Che, the IDE is completely decoupled, it can plug a different IDE into Che workspaces: such as Theia (Browser-based IDE with language tools) 

Two parts of  Eclipse Che: the workspace server and the web-based IDE connected to it (Editor in Che):

![Che](https://eclipsesource.com/wp-content/uploads/2018/11/image2-1.png)

The Eclipse Che workspace server creates, manages and orchestrates developer environments that are running on a cloud container platform (Kubernetes, Docker, OpenShift, etc.). Che workspaces run in containers which provide all the dependencies that are needed to code, build, test, run and debug a project.

The Eclipse Che IDE provides a web-based UI for developing code, browsing files, using Git etc.. In version 6 it used to be implemented based on GWT, it is also referred to as the Che GWT IDE. Theia is implemented using TypeScript, HTML, CSS and a couple of JavaScript libraries such as phosphor.js. 
Eclipse Theia is the successor of the Eclipse Che GWT IDE. 

![Che 7](https://eclipsesource.com/wp-content/uploads/2018/11/image1-1.png)

Eclipse Theia or in general a web-based IDE is only one of the pieces needed to create and operate a cloud-based tool. While Theia also comes with its own server part, it needs some place to deploy it. If want to support one user with one workspace, can just deploy your Theia backend somewhere and you are fine.

In any multi-user/-tenancy scenario, it needs to support multiple users and allow them to create multiple workspaces. This is exactly were the Eclipse Che workspace server comes into play. It provides those missing features such as:
- User management (including integration with existing LDAP)
- Workspace management, i.e. users can create multiple workspaces and switch between them
- Workspace sharing, i.e. running workplaces can be shared or cloned among team members
- Workspace configuration management, i.e. there are adaptable templates (called stacks) to create new workspaces from, e.g. a JavaEE workspaces with all tools pre-installed
- Resource management, i.e. assignment of resources like RAM to workspaces or definition of limits per team
    

## Architecture
Che needs a workspace engine to manage the lifecycle of the workspaces. Two workspace engines are available. The choice of a workspace engine defines the architecture.

- Che architecture with Che server
![Che server](https://www.eclipse.org/che/docs/che-7/administration-guide/_images/architecture/che-architecture-with-che-server-engine.png)

- Che architecture with DevWorkspace
![DevWorkSpace](https://www.eclipse.org/che/docs/che-7/administration-guide/_images/architecture/che-interacting-with-devworkspace.png)

- [Installation](https://www.eclipse.org/che/docs/che-7/installation-guide/installing-che/)
    - in cloud
    - on a local single-node cluster
```
$ bash <(curl -sL  https://www.eclipse.org/che/chectl/)
$ which chectl
$ chectl --version
$ minikube start
$ chectl server:deploy --platform=minikube     #minikube|k8s|openshift|microk8s|docker-desktop|crc
```

## Tutorial
- [Document](https://www.eclipse.org/che/docs/che-7/overview/introduction-to-eclipse-che/)
