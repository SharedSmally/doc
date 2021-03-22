# Kubernetes
- [Start up](https://kubernetes.io/docs/setup/)
- [Tutorial](https://kubernetes.io/docs/tutorials/)
- [kubectl CLI](https://kubernetes.io/docs/reference/kubectl/)
- [Reference](https://kubernetes.io/docs/reference/)

## Config

## Components
- Resource
    - apiVersion: v1
    - kind: Xxxxxx
    - metadata ([ObjectMeta](https://kubernetes.io/docs/reference/kubernetes-api/common-definitions/object-meta/#ObjectMeta)): Standard object's metadata. 

### [Pod](https://kubernetes.io/docs/reference/kubernetes-api/workloads-resources/)
- [Pod](https://kubernetes.io/docs/reference/kubernetes-api/workloads-resources/pod-v1/): a collection of containers that can run on a host.
    - spec (PodSpec):Specification of the desired behavior of the pod. 
        - containers (\[\][Container](https://kubernetes.io/docs/reference/kubernetes-api/workloads-resources/container/#Container))*: List of containers belonging to the pod. 
        - initContainers (\[\][Container](https://kubernetes.io/docs/reference/kubernetes-api/workloads-resources/container/#Container)): List of initialization containers belonging to the pod. 
        - imagePullSecrets (\[\][LocalObjectReference](https://kubernetes.io/docs/reference/kubernetes-api/common-definitions/local-object-reference/#LocalObjectReference)):
    - volumes (\[\][Volume](https://kubernetes.io/docs/reference/kubernetes-api/config-and-storage-resources/volume/#Volume)):         
    - status (PodStatus): Most recently observed status of the pod. 
    
- PodTemplate: PodTemplate describes a template for creating copies of a predefined pod.
    - template (PodTemplateSpec): Template defines the pods that will be created from this pod template. 
        - spec ([PodSpec](https://kubernetes.io/docs/reference/kubernetes-api/workloads-resources/pod-v1/#PodSpec)): Specification of the desired behavior of the pod.

- Container: A single application container running within a pod.
    - name (string)\*: Name of the container specified as a DNS_LABEL. 
    - image (string):Docker image name. 
    - imagePullPolicy (string): Image pull policy. One of Always, Never, IfNotPresent.
    - command ([]string): Entrypoint array. 
    - args ([]string): Arguments to the entrypoint.
    - workingDir (string): Container's working directory. 
    - ports ([]ContainerPort):List of ports to expose from the container.
        - containerPort (int32)*: Number of port to expose on the pod's IP address
        - hostIP (string): What host IP to bind the external port to.
        - hostPort (int32): Number of port to expose on the host. 
        - name (string): Each named port in a pod must have a unique name. 
        - protocol (string): Protocol for port. Must be UDP, TCP, or SCTP. Defaults to "TCP".
    - env ([]EnvVar): List of environment variables to set in the container.
        -  name (string)*: Name of the environment variable
        -  value (string): value, references $(VAR_NAME) are expanded 
        -  valueFrom (EnvVarSource): Source for the environment variable's value
             -  configMapKeyRef (ConfigMapKeySelector)
             -  fieldRef (ObjectFieldSelector)
             -  resourceFieldRef (ResourceFieldSelector)
             -  secretKeyRef (SecretKeySelector)
    - envFrom ([]EnvFromSource): List of sources to populate environment variables in the container. 
        -  configMapKeyRef (ConfigMapKeySelector)
        -  secretRef (SecretEnvSource)
    - volumeMounts ([]VolumeMount)
    - volumeDevices ([]VolumeDevice)
    - resources (ResourceRequirements)
    - lifecycle (Lifecycle): Actions that the management system should take in response to container lifecycle events
    - livenessProbe (Probe)
    - readinessProbe (Probe)
    - securityContext (SecurityContext)
    - startupProbe (Probe)
    - state (ContainerState)

- EphemeralContainer: added temporarily to an existing pod for user-initiated activities such as debugging.

### [Workloads Resources](https://kubernetes.io/docs/reference/kubernetes-api/workloads-resources/)
- [Deployment](https://kubernetes.io/docs/reference/kubernetes-api/workloads-resources/deployment-v1/): Stateless-Set, replace ReplicateSet
    - spec (DeploymentSpec): Specification of the desired behavior of the Deployment.
        - selector ([LabelSelector](https://kubernetes.io/docs/reference/kubernetes-api/common-definitions/label-selector/#LabelSelector))*:  Label selector for pods. 
        - template ([PodTemplateSpec](https://kubernetes.io/docs/reference/kubernetes-api/workloads-resources/pod-template-v1/#PodTemplateSpec))*:Template describes the pods that will be created.
        - replicas (int32): Number of desired pods. Defaults to 1.
        - minReadySeconds (int32)
        - strategy (DeploymentStrategy):
    - status (DeploymentStatus): Most recently observed status of the Deployment
- [Stateset](https://kubernetes.io/docs/reference/kubernetes-api/workloads-resources/stateful-set-v1/):
    - spec (StatefulSetSpec): Spec defines the desired identities of pods in this set.
        - selector ([LabelSelector](https://kubernetes.io/docs/reference/kubernetes-api/common-definitions/label-selector/#LabelSelector))*:  Label selector for pods. 
        - template ([PodTemplateSpec](https://kubernetes.io/docs/reference/kubernetes-api/workloads-resources/pod-template-v1/#PodTemplateSpec))*:Template describes the pods that will be created.
        - replicas (int32): Number of desired pods. Defaults to 1.
        - minReadySeconds (int32)
        - updateStrategy (StatefulSetUpdateStrategy):
    - status (StatefulSetStatus): Status is the current status of Pods in this StatefulSet.
- [DaemonSet](https://kubernetes.io/docs/reference/kubernetes-api/workloads-resources/daemon-set-v1/): DaemonSet represents the configuration of a daemon set.
    - spec (DaemonSetSpec): The desired behavior of this daemon set.
        - selector ([LabelSelector](https://kubernetes.io/docs/reference/kubernetes-api/common-definitions/label-selector/#LabelSelector))*:  Label selector for pods. 
        - template ([PodTemplateSpec](https://kubernetes.io/docs/reference/kubernetes-api/workloads-resources/pod-template-v1/#PodTemplateSpec))*:Template describes the pods that will be created.
        - minReadySeconds (int32)
        - updateStrategy (DaemonSetUpdateStrategy):
    - status (DaemonSetStatus): The current status of this daemon set.

- Job:  the configuration of a single job.
- CronJob: the configuration of a single cron job.

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
