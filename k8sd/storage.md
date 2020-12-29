# [Storage](https://kubernetes.io/docs/concepts/storage/)

## [Volume vs PersistVolume](https://matthewpalmer.net/kubernetes-app-developer/articles/kubernetes-volumes-example-nfs-persistent-volume.html)

Pod includes multiple containers.

In Kubernetes, each container can read and write to its own, isolated filesystem. But, data on that filesystem will be destroyed when the container is restarted.

To solve this, Kubernetes has volumes. Volumes let your pod write to a filesystem that exists as long as the pod exists. Volumes also let you share data between containers in the same pod. But, data in that volume will be destroyed when the pod is restarted.

To solve this, Kubernetes has persistent volumes. Persistent volumes are long-term storage in your Kubernetes cluster. Persistent volumes exist beyond containers, pods, and nodes. A pod uses a persistent volume claim to to get read and write access to the persistent volume.

| Type of storage |	How long does it last? |
| :---: | :---: | 
| Container filesystem |	Container lifetime |
| Volume 	| Pod lifetime, used by container via volumeMounts |
| Persistent volume |	Cluster lifetime, used by Pod via Persistent Volume Claim |

There are two steps for using a volume:
- First, the pod defines the volume (Persistent volume, host filesystem, pod filesystem, PersistVolumeClaim, etc).
- Second, the container uses volumeMounts to add that volume at a specific path (mountPath) in its filesystem.
```
kind: Pod
apiVersion: v1
metadata:
  name: simple-volume-pod
spec:
  # Volumes are declared by the pod. They share its lifecycle and are communal across containers.
  volumes:
    # Volumes have a name and configuration based on the type of volume. we use the emptyDir volume type here
    - name: simple-vol
      emptyDir: {} # No extra configuration

  # Now, one of our containers can mount this volume and use it like any other directory.
  containers:
    - name: my-container
      volumeMounts:
        - name: simple-vol # This is the name of the volume we set at the pod level
          mountPath: /var/simple # Where to mount this directory in our container
      
      # Now that we have a directory mounted at /var/simple, let's write to a file inside it!
      image: alpine
      command: ["/bin/sh"]
      args: ["-c", "while true; do date >> /var/simple/file.txt; sleep 5; done"]
```


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

## [Persistent Volumes](https://kubernetes.io/docs/concepts/storage/persistent-volumes/)

A PersistentVolume (PV) is a piece of storage in the cluster that has been provisioned by an administrator or dynamically provisioned using Storage Classes. It is a resource in the cluster just like a node is a cluster resource. PVs are volume plugins like Volumes, but have a lifecycle independent of any individual Pod that uses the PV. This API object captures the details of the implementation of the storage, be that NFS, iSCSI, or a cloud-provider-specific storage system.

A PersistentVolumeClaim (PVC) is a request for storage by a user. It is similar to a Pod. Pods consume node resources and PVCs consume PV resources. Pods can request specific levels of resources (CPU and Memory). Claims can request specific size and access modes (e.g., they can be mounted ReadWriteOnce, ReadOnlyMany or ReadWriteMany).  via storageClass to match PV or StorageClass to claim storage.

## [Volume Snapshots](https://kubernetes.io/docs/concepts/storage/volume-snapshots/)
A VolumeSnapshot represents a snapshot of a volume on a storage system.

Similar to how API resources PersistentVolume and PersistentVolumeClaim are used to provision volumes for users and administrators, VolumeSnapshotContent and VolumeSnapshot API resources are provided to create volume snapshots for users and administrators.

A VolumeSnapshotContent is a snapshot taken from a volume in the cluster that has been provisioned by an administrator. It is a resource in the cluster just like a PersistentVolume is a cluster resource.

A VolumeSnapshot is a request for snapshot of a volume by a user. It is similar to a PersistentVolumeClaim.

## [CSI Volume Cloning](https://kubernetes.io/docs/concepts/storage/volume-pvc-datasource/)

## [Storage Classes](https://kubernetes.io/docs/concepts/storage/storage-classes/)
A StorageClass provides a way for administrators to describe the "classes" of storage they offer. Each StorageClass contains the fields provisioner, parameters, and reclaimPolicy, which are used when a PersistentVolume belonging to the class needs to be dynamically provisioned.

## [Volume Snapshot Classes](https://kubernetes.io/docs/concepts/storage/volume-snapshot-classes/)
VolumeSnapshotClass provides a way to describe the "classes" of storage when provisioning a volume snapshot.

## [Dynamic Volume Provisioning](https://kubernetes.io/docs/concepts/storage/dynamic-provisioning/)
Dynamic volume provisioning allows storage volumes to be created on-demand. It automatically provisions storage when it is requested by users.

## Storage Capacity

## [Ephemeral Volumes](https://kubernetes.io/docs/concepts/storage/ephemeral-volumes/)
Some application need additional storage but don't care whether that data is stored persistently across restarts. For example, caching services are often limited by memory size and can move infrequently used data into storage that is slower than memory with little impact on overall performance.

Other applications expect some read-only input data to be present in files, like configuration data or secret keys.

Ephemeral volumes are designed for these use cases. Because volumes follow the Pod's lifetime and get created and deleted along with the Pod, Pods can be stopped and restarted without being limited to where some persistent volume is available.

Ephemeral volumes are specified inline in the Pod spec, which simplifies application deployment and management.
Types of ephemeral volumes

Kubernetes supports several different kinds of ephemeral volumes for different purposes:

- **emptyDir**: empty at Pod startup, with storage coming locally from the kubelet base directory (usually the root disk) or RAM
- **configMap, downwardAPI, secret**: inject different kinds of Kubernetes data into a Pod
- **CSI ephemeral volumes**: similar to the previous volume kinds, but provided by special CSI drivers which specifically support this feature
- **generic ephemeral volumes**: can be provided by all storage drivers that also support persistent volumes
    
emptyDir, configMap, downwardAPI, secret are provided as local ephemeral storage. They are managed by kubelet on each node.

CSI ephemeral volumes must be provided by third-party CSI storage drivers.
```
kind: Pod
apiVersion: v1
metadata:
  name: my-csi-app
spec:
  containers:
    - name: my-frontend
      image: busybox
      volumeMounts:
      - mountPath: "/data"
        name: my-csi-inline-vol
      command: [ "sleep", "1000000" ]
  volumes:
    - name: my-csi-inline-vol
      csi:
        driver: inline.storage.kubernetes.io
        volumeAttributes:
          foo: bar
```
## Node-specific Volume Limits
