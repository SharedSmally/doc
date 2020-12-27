# [Storage](https://kubernetes.io/docs/concepts/storage/)

## [Volumes](https://kubernetes.io/docs/concepts/storage/volumes/)
Kubernetes supports many types of volumes. A Pod can use any number of volume types simultaneously. 
Ephemeral volume types have a lifetime of a pod, but persistent volumes exist beyond the lifetime of a pod. 
Consequently, a volume outlives any containers that run within the pod, and data is preserved across container restarts. 
When a pod ceases to exist, the volume is destroyed.

To use a volume, specify the volumes to provide for the Pod in **.spec.volumes** and declare where to mount those volumes into containers in **.spec.containers[*].volumeMounts**. 

```
apiVersion: v1
kind: Pod
metadata:
  name: test-ebs
spec:
  containers:
  - image: k8s.gcr.io/test-webserver
    name: test-container
    volumeMounts:
    - mountPath: /test-ebs
      name: test-volume
  volumes:
  - name: test-volume
    # This AWS EBS volume must already exist.
    awsElasticBlockStore:
      volumeID: "<volume id>"
      fsType: ext4
```

    - [configMap](https://kubernetes.io/docs/tasks/configure-pod-container/configure-pod-configmap/)
    - secret:  pass sensitive information, such as passwords, to Pods.
    - emptyDir: An emptyDir volume is first created when a Pod is assigned to a node, and exists as long as that Pod is running on that node.
    - hostPath:  mounts a file or directory from the host node's filesystem into your Pod. 
    - local: A local volume represents a mounted local storage device such as a disk, partition or directory.
    - projected: maps several existing volume sources into the same directory.
    - persistentVolumeClaim: mount a PersistentVolume into a Pod
    
    - awsElasticBlockStore
    - azureDisk/azureFile
    - cephfs
    - cinder
    - fc (fibre channel)
    - gcePersistentDisk
    - glusterfs
    - iscsi
    - nfs
    - portworxVolume
    - quobyte 
    - rbd
    - storageOS
    - vsphereVolume   

- Persistent Volumes
- Volume Snapshots
- CSI Volume Cloning
- Storage Classes
- Volume Snapshot Classes
- Dynamic Volume Provisioning
- Storage Capacity
- Ephemeral Volumes
- Node-specific Volume Limits
