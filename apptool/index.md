# Application K8s Tools: helm

## App environments
- docker
- kubenetes
- helm

## k8s cluster: minikube
https://minikube.sigs.k8s.io/docs/start/
- Install
```
$ minikube start
$ kubectl get po -A
```

## calico

## Database
### postgresql
bitnami => zalando

## zookeeper (2n+1_

## kafka (2n+1)

## redis
- install
```
$ helm repo add bitnami https://charts.bitnami.com/bitnami
$ helm install my-release bitnami/redis   # need k8s cluster ready
```
After installation:
```
can be accessed on the following DNS names from within your cluster:
    my-release-redis-master.default.svc.cluster.local for read/write operations (port 6379)
    my-release-redis-replicas.default.svc.cluster.local for read-only operations (port 6379)

To get your password run:
    export REDIS_PASSWORD=$(kubectl get secret --namespace default my-release-redis -o jsonpath="{.data.redis-password}" | base64 --decode)

To connect to your Redis&trade; server:
1. Run a Redis&trade; pod that you can use as a client:
   kubectl run --namespace default redis-client --restart='Never'  --env REDIS_PASSWORD=$REDIS_PASSWORD  --image docker.io/bitnami/redis:6.2.7-debian-10-r23 --command -- sleep infinity

 Use the following command to attach to the pod:
   kubectl exec --tty -i redis-client \
   --namespace default -- bash

2. Connect using the Redis&trade; CLI:
   REDISCLI_AUTH="$REDIS_PASSWORD" redis-cli -h my-release-redis-master
   REDISCLI_AUTH="$REDIS_PASSWORD" redis-cli -h my-release-redis-replicas

To connect to your database from outside the cluster execute the following commands:
    kubectl port-forward --namespace default svc/my-release-redis-master 6379:6379 &
    REDISCLI_AUTH="$REDIS_PASSWORD" redis-cli -h 127.0.0.1 -p 6379
```

## HAproxy

