# Kubernetes
- [Start up](https://kubernetes.io/docs/setup/)
- [Tutorial](https://kubernetes.io/docs/tutorials/)
- [kubectl CLI](https://kubernetes.io/docs/reference/kubectl/)
- [Reference](https://kubernetes.io/docs/reference/)

## Config

## Components
### [Workloads Resources]()
- [Deployment](https://kubernetes.io/docs/reference/kubernetes-api/workloads-resources/deployment-v1/): Stateless-Set, replace ReplicateSet
    - metadata ([ObjectMeta](https://kubernetes.io/docs/reference/kubernetes-api/common-definitions/object-meta/#ObjectMeta)): Standard object metadata.
    - spec (DeploymentSpec): Specification of the desired behavior of the Deployment.
        - selector ([LabelSelector](https://kubernetes.io/docs/reference/kubernetes-api/common-definitions/label-selector/#LabelSelector))*:  Label selector for pods. 
        - template ([PodTemplateSpec](https://kubernetes.io/docs/reference/kubernetes-api/workloads-resources/pod-template-v1/#PodTemplateSpec))*:Template describes the pods that will be created.
        - replicas (int32): Number of desired pods. Defaults to 1.
        - minReadySeconds (int32)
        - strategy (DeploymentStrategy):
    - status (DeploymentStatus): Most recently observed status of the Deployment
- Stateset:
- DaemonSet:

### [Services Resources]()

### [Config and Storage Resources]()

### [Authentication Resources]()

### [Authorization Resources]()

### [Policies Resources]()

### [Extend Resources]()

### [Cluster Resources]()



| Component | Spec | Template | Status |
| --------- | ---- | -------- | ------ |
| Pod | PodSpec | PodTemplate | PodStatus |
