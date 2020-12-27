# [k8s Workload Resources](https://kubernetes.io/docs/concepts/workloads/controllers/)
- **Deployments**: Provides declarative updates for Pods and ReplicaSets. (use/own ReplicaSet)
- **ReplicaSet**: Maintain a stable set of replica Pods running at any given time. The successors to ReplicationControllers. 
- **ReplicationController**: Same as ReplicaSet, except not support set-based selector 
- **StatefulSets**: Manages the deployment and scaling of a set of Pods, and provides guarantees about the ordering and uniqueness of these Pods.
- **DaemonSet**: A DaemonSet ensures that all (or some) Nodes run a copy of a Pod. 
- **Jobs**: A Job creates one or more Pods and ensures that a specified number of them successfully terminate. 
- **CronJob**: A CronJob creates Jobs on a repeating schedule.
- **Garbage Collection**
- **TTL Controller for Finished Resources**

## [Replicaset](https://kubernetes.io/docs/concepts/workloads/controllers/replicaset/)
```
apiVersion: apps/v1
kind: ReplicaSet
metadata:
  name: frontend
  labels:
    app: guestbook
    tier: frontend
spec:
  replicas: 3
  selector:
    matchLabels:
      tier: frontend
  template:
    metadata:
      labels:
        tier: frontend
    spec:
      containers:
      - name: php-redis
        image: gcr.io/google_samples/gb-frontend:v3
```

Non-Template Pod acquisitions:
```
apiVersion: v1
kind: Pod
metadata:
  name: pod1
  labels:
    tier: frontend
spec:
  containers:
  - name: hello1
    image: gcr.io/google-samples/hello-app:2.0

---

apiVersion: v1
kind: Pod
metadata:
  name: pod2
  labels:
    tier: frontend
spec:
  containers:
  - name: hello2
    image: gcr.io/google-samples/hello-app:1.0
```

## (StatefulSet) [https://kubernetes.io/docs/concepts/workloads/controllers/statefulset/]
Like a Deployment, a StatefulSet manages Pods that are based on an identical container spec. 
Unlike a Deployment, a StatefulSet maintains a sticky identity for each of their Pods. 
These pods are created from the same spec, but are not interchangeable: each has a persistent 
identifier that it maintains across any rescheduling.

StatefulSets are valuable for applications that require one or more of the following.
- Stable, unique network identifiers.
- Stable, persistent storage.
- Ordered, graceful deployment and scaling.
- Ordered, automated rolling updates.

```
apiVersion: v1
kind: Service
metadata:
  name: nginx
  labels:
    app: nginx
spec:
  ports:
  - port: 80
    name: web
  clusterIP: None
  selector:
    app: nginx
---
apiVersion: apps/v1
kind: StatefulSet
metadata:
  name: web
spec:
  selector:
    matchLabels:
      app: nginx # has to match .spec.template.metadata.labels
  serviceName: "nginx"
  replicas: 3 # by default is 1
  template:
    metadata:
      labels:
        app: nginx # has to match .spec.selector.matchLabels
    spec:
      terminationGracePeriodSeconds: 10
      containers:
      - name: nginx
        image: k8s.gcr.io/nginx-slim:0.8
        ports:
        - containerPort: 80
          name: web
        volumeMounts:
        - name: www
          mountPath: /usr/share/nginx/html
  volumeClaimTemplates:
  - metadata:
      name: www
    spec:
      accessModes: [ "ReadWriteOnce" ]
      storageClassName: "my-storage-class"
      resources:
        requests:
          storage: 1Gi
```

## [DaemonSet](https://kubernetes.io/docs/concepts/workloads/controllers/daemonset/)
A DaemonSet ensures that all (or some) Nodes run a copy of a Pod. As nodes are added to the cluster, 
Pods are added to them. As nodes are removed from the cluster, those Pods are garbage collected. 
Deleting a DaemonSet will clean up the Pods it created.

Some typical uses of a DaemonSet are:
- running a cluster storage daemon on every node
- running a logs collection daemon on every node
- running a node monitoring daemon on every node

```
apiVersion: apps/v1
kind: DaemonSet
metadata:
  name: fluentd-elasticsearch
  namespace: kube-system
  labels:
    k8s-app: fluentd-logging
spec:
  selector:
    matchLabels:
      name: fluentd-elasticsearch
  template:
    metadata:
      labels:
        name: fluentd-elasticsearch
    spec:
      tolerations:
      # this toleration is to have the daemonset runnable on master nodes
      # remove it if your masters can't run pods
      - key: node-role.kubernetes.io/master
        effect: NoSchedule
      containers:
      - name: fluentd-elasticsearch
        image: quay.io/fluentd_elasticsearch/fluentd:v2.5.2
        resources:
          limits:
            memory: 200Mi
          requests:
            cpu: 100m
            memory: 200Mi
        volumeMounts:
        - name: varlog
          mountPath: /var/log
        - name: varlibdockercontainers
          mountPath: /var/lib/docker/containers
          readOnly: true
      terminationGracePeriodSeconds: 30
      volumes:
      - name: varlog
        hostPath:
          path: /var/log
      - name: varlibdockercontainers
        hostPath:
          path: /var/lib/docker/containers
```

## [Jobs](https://kubernetes.io/docs/concepts/workloads/controllers/job/)

A Job creates one or more Pods and ensures that a specified number of them successfully terminate. 
As pods successfully complete, the Job tracks the successful completions. When a specified number of 
successful completions is reached, the task (ie, Job) is complete. Deleting a Job will clean up the Pods it created.

A simple case is to create one Job object in order to reliably run one Pod to completion. The Job object 
will start a new Pod if the first Pod fails or is deleted (for example due to a node hardware failure or a node reboot).

```
apiVersion: batch/v1
kind: Job
metadata:
  name: pi
spec:
  template:
    spec:
      containers:
      - name: pi
        image: perl
        command: ["perl",  "-Mbignum=bpi", "-wle", "print bpi(2000)"]
      restartPolicy: Never
  backoffLimit: 4
```

## [CronJob](https://kubernetes.io/docs/concepts/workloads/controllers/cron-jobs/)

A CronJob creates Jobs on a repeating schedule. One CronJob object is like one line of a crontab (cron table) file.
It runs a job periodically on a given schedule, written in Cron format.
```
apiVersion: batch/v1beta1
kind: CronJob
metadata:
  name: hello
spec:
  schedule: "*/1 * * * *"
  jobTemplate:
    spec:
      template:
        spec:
          containers:
          - name: hello
            image: busybox
            imagePullPolicy: IfNotPresent
            args:
            - /bin/sh
            - -c
            - date; echo Hello from the Kubernetes cluster
          restartPolicy: OnFailure
```

## [Garbage Collection](https://kubernetes.io/docs/concepts/workloads/controllers/garbage-collection/)

## [TTL Controller for Finished Resources](https://kubernetes.io/docs/concepts/workloads/controllers/ttlafterfinished/)

