# [Storage](https://kubernetes.io/docs/concepts/storage/)

## [Volumes](https://kubernetes.io/docs/concepts/storage/volumes/)
Kubernetes supports many types of volumes. A Pod can use any number of volume types simultaneously. 
Ephemeral volume types have a lifetime of a pod, but persistent volumes exist beyond the lifetime of a pod. 
Consequently, a volume outlives any containers that run within the pod, and data is preserved across container restarts. 
When a pod ceases to exist, the volume is destroyed.

To use a volume, specify the volumes to provide for the Pod in **.spec.volumes** and declare where to mount those volumes into containers in **.spec.containers[*].volumeMounts**. 

- Persistent Volumes
- Volume Snapshots
- CSI Volume Cloning
- Storage Classes
- Volume Snapshot Classes
- Dynamic Volume Provisioning
- Storage Capacity
- Ephemeral Volumes
- Node-specific Volume Limits
