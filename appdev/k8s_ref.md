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
    - spec (JobSpec): Specification of the desired behavior of a job. 
        - template (PodTemplateSpec)*: Describes the pod that will be created when executing a job. 
        - parallelism (int32): the maximum desired number of pods the job should run at any given time. 
        - selector (LabelSelector): A label query over pods that should match the pod count. 
    - status (JobStatus): Current status of a job. 

- [CronJob](): the configuration of a single cron job.
    - spec (CronJobSpec): Specification of the desired behavior of a cron job, including the schedule. 
        - jobTemplate (JobTemplateSpec)*:Specifies the job that will be created when executing a CronJob.
            - .spec (JobSpec): Specification of the desired behavior of the job.
    - status (CronJobStatus):Current status of a cron job. 

- [LabelSelector]()

### [Services Resources]()

- [Service](https://kubernetes.io/docs/reference/kubernetes-api/services-resources/service-v1/): a named abstraction of software service consisting of local port that the proxy listens on, and the selector that determines which pods will answer requests sent through the proxy.
    - spec (ServiceSpec): Spec defines the behavior of a service.
        - selector (map[string]string): Route service traffic to pods with label keys and values matching this selector. 
        - ports ([]ServicePort): The list of ports that are exposed by this service.
    - status (ServiceStatus): Most recently observed status of the service.

- [Endpoints](https://kubernetes.io/docs/reference/kubernetes-api/services-resources/endpoints-v1/): a collection of endpoints that implement the actual service.
    - subsets ([]EndpointSubset): The set of all endpoints is the union of all subsets. 
- [EndpointSlice](https://kubernetes.io/docs/reference/kubernetes-api/services-resources/endpoint-slice-v1beta1/): represents a subset of the endpoints that implement a service.
    - addressType (string)*: addressType specifies the type of address carried by this EndpointSlice. supported: IPv4, IPv6, FQDN
    - endpoints ([]Endpoint)*: a list of unique endpoints in this slice.
- Ingress: a collection of rules that allow inbound connections to reach the endpoints defined by a backend.
    - spec (IngressSpec): the desired state of the Ingress.
        - rules ([]IngressRule): A list of host rules used to configure the Ingress. 
        - tls ([]IngressTLS): TLS configuration. 
    - status (IngressStatus): the current state of the Ingress. 
- IngressClass:represents the class of the Ingress, referenced by the Ingress Spec.
    - spec (IngressClassSpec): Spec is the desired state of the IngressClass.

### [Config and Storage Resources]()
- [ConfigMap](https://kubernetes.io/docs/reference/kubernetes-api/config-and-storage-resources/config-map-v1/): holds configuration data for pods to consume.
    - binaryData (map[string][]byte): contains the binary data. 
    - data (map[string]string): contains the configuration data. 
    - immutable (boolean):
- [Secret](https://kubernetes.io/docs/reference/kubernetes-api/config-and-storage-resources/secret-v1/): holds secret data of a certain type.
    - data (map[string][]byte): contains the secret data. 
    - immutable (boolean): true, stored data cannot be updated 
    - stringData (map[string]string): specifying non-binary secret data in string form. 
    - type (string): Used to facilitate programmatic handling of secret data
- [Volume](https://kubernetes.io/docs/reference/kubernetes-api/config-and-storage-resources/volume/): represents a named volume in a pod that may be accessed by any container in the pod.
    - name (string)\*: Volume's name.
    - persistentVolumeClaim (PersistentVolumeClaimVolumeSource)
    - configMap (ConfigMapVolumeSource)
    - secret (SecretVolumeSource)
    - downwardAPI (DownwardAPIVolumeSource)
    - projected (ProjectedVolumeSource)
    - emptyDir (EmptyDirVolumeSource)
    - awsElasticBlockStore (AWSElasticBlockStoreVolumeSource)
    - azureDisk (AzureDiskVolumeSource)
    - azureFile (AzureFileVolumeSource)
    - cephfs (CephFSVolumeSource)
    - ***
- PersistentVolumeClaim(pvc): a user's request for and claim to a persistent volume.
    - spec (PersistentVolumeClaimSpec): defines the desired characteristics of a volume requested by a pod author. 
        - accessModes ([]string): ontains the desired access modes the volume should have. 
        - selector (LabelSelector): A label query over volumes to consider for binding.
        - resources (ResourceRequirements): represents the minimum resources the volume should have.
        - volumeName (string):the binding reference to the PersistentVolume backing this claim.
        - storageClassName (string): Name of the StorageClass required by the claim.
        - volumeMode (string): volumeMode defines what type of volume is required by the claim. 
    - status (PersistentVolumeClaimStatus): Status represents the current information/status of a persistent volume claim. 
- [PersistentVolume(pv)](https://kubernetes.io/docs/reference/kubernetes-api/config-and-storage-resources/persistent-volume-v1/): a storage resource provisioned by an administrator.
    - spec (PersistentVolumeSpec): defines a specification of a persistent volume owned by the cluster.
        - accessModes ([]string): contains all ways the volume can be mounted. 
        - capacity (map[string]Quantity): A description of the persistent volume's resources and capacity. 
        - claimRef (ObjectReference): a bi-directional binding between PersistentVolume and PersistentVolumeClaim.
        - mountOptions ([]string): A list of mount options, e.g. ["ro", "soft"]. 
        - nodeAffinity (VolumeNodeAffinity): defines constraints that limit what nodes this volume can be accessed from.
        - persistentVolumeReclaimPolicy (string): What happens to a persistent volume when released from its claim. 
        - storageClassName (string): Name of StorageClass to which this persistent volume belongs. 
        - volumeMode (string): if a volume is used with a formatted filesystem or to remain in raw block state. 
        - various sources
    - status (PersistentVolumeStatus):represents the current information/status for the persistent volume. 
- StorageClass: describes the parameters for a class of storage for which PersistentVolumes can be dynamically provisioned.
    - provisioner (string)\*: the type of the provisioner.
    - allowVolumeExpansion (boolean): whether the storage class allow volume expand
    - allowedTopologies ([]TopologySelectorTerm): restrict the node topologies where volumes can be dynamically provisioned. 
    - mountOptions ([]string): Dynamically provisioned PersistentVolumes of this storage class are created with these mountOptions
    - parameters (map[string]string): holds the parameters for the provisioner that should create volumes of this storage class.
    - reclaimPolicy (string): Dynamically provisioned PersistentVolumes of this storage class are created with this reclaimPolicy.
    - volumeBindingMode (string): how PersistentVolumeClaims should be provisioned and bound. 
- VolumeAttachment: captures the intent to attach or detach the specified volume to/from the specified node.
    - spec (VolumeAttachmentSpec)\*: Specification of the desired attach/detach volume behavior.
        - attacher (string)*: the name of the volume driver that MUST handle this request. 
        - nodeName (string)*: The node that the volume should be attached to.
        - source (VolumeAttachmentSource)*: Source represents the volume that should be attached.
    - status (VolumeAttachmentStatus): Status of the VolumeAttachment request. 
- [CSIDriver](https://kubernetes.io/docs/reference/kubernetes-api/config-and-storage-resources/csi-driver-v1/): captures information about a Container Storage Interface (CSI) volume driver deployed on the cluster.
    - spec (CSIDriverSpec)\*: Specification of the CSI Driver.
- [CSINode](https://kubernetes.io/docs/reference/kubernetes-api/config-and-storage-resources/csi-node-v1/): holds information about all CSI drivers installed on a node.
    - spec (CSINodeSpec)\*: the specification of CSINode

### [Authentication Resources](https://kubernetes.io/docs/reference/kubernetes-api/authentication-resources/)
- ServiceAccount: ServiceAccount binds together: * a name, understood by users, and perhaps by peripheral systems, for an identity * a principal that can be authenticated and authorized * a set of secrets.
- TokenRequest: requests a token for a given service account.
- TokenReview: attempts to authenticate a token to a known user.
- CertificateSigningRequest: provide a mechanism to obtain x509 certificates by submitting a certificate signing request, and having it asynchronously approved and issued.

### [Authorization Resources]()
- LocalSubjectAccessReview: checks whether or not a user or group can perform an action in a given namespace.
- SelfSubjectAccessReview: checks whether or the current user can perform an action.
- SelfSubjectRulesReview: enumerates the set of actions the current user can perform within a namespace.
- SubjectAccessReview: checks whether or not a user or group can perform an action.
- ClusterRole:  a cluster level, logical grouping of PolicyRules that can be referenced as a unit by a RoleBinding or ClusterRoleBinding.
- ClusterRoleBinding: ClusterRoleBinding references a ClusterRole, but not contain it.
- Role: Role is a namespaced, logical grouping of PolicyRules that can be referenced as a unit by a RoleBinding.
- RoleBinding: RoleBinding references a role, but does not contain it.

### [Policies Resources]()

### [Extend Resources]()

### [Cluster Resources]()
- Node: Node is a worker node in Kubernetes.
- Namespace: Namespace provides a scope for Names.
- Event: Event is a report of an event somewhere in the cluster.
- APIService: APIService represents a server for a particular GroupVersion.
- Lease: Lease defines a lease concept.
- RuntimeClass: RuntimeClass defines a class of container runtime supported in the cluster.
- FlowSchema: FlowSchema defines the schema of a group of flows.
- PriorityLevelConfiguration: PriorityLevelConfiguration represents the configuration of a priority level.
- Binding: Binding ties one object to another; for example, a pod is bound to a node by a scheduler.
- ComponentStatus: ComponentStatus (and ComponentStatusList) holds the cluster validation info.


| Component | Spec | Template | Status |
| --------- | ---- | -------- | ------ |
| Pod | PodSpec | PodTemplate | PodStatus |
