# build docker image rpm file
- copy rpm and deployment yaml ${name}.yaml in a dir  /home/centos/pkg
```
cd /home/centos/pkg
sudo docker build --build-arg RPM_FILE=rpmfile.rpm -t ${name}:${version} # build image
sudo docker image save ${name}:${version}  -o ${name}_${version}.tar
gzip ${name}_${version}.tar

copy the deployment yaml and tar file into k8s master

gunzip ${name}.tar.gz

kubectl apply -f ${name}.yaml
sudo docker load -i ${name}.tar  # load docker image on all k8s VMs

kubectl get pods
kubectl delete pod ${name}-<id>
```

# HA Postgres ON k8S
- [Crunchy PostgreSQL Operator](https://info.crunchydata.com/blog/deploy-high-availability-postgresql-on-kubernetes):Patroni for consensus management
- [Stolon](https://github.com/sorintlab/stolon): Build-in keepers and sentinels, no need VIP/HAProxy

# Kafka/zookeeper

# Redis and Redis Sentinel

# Service Mesh: 
- [istio](https://istio.io):

# Health check:
return 200 OK in the RUNNING state, or 204 for other states with the corresponding message:
```
readinessProbe:
   httpGet:
      path: /v2/query?state="INIT|WARN"
      port:8990
   initialDelaySeconds: 5
   periodSecondes: 5

livenessProbe:
   httpGet:
      path: /v2/query?state="CRIT"
      port:8990
   initialDelaySeconds: 5
   periodSecondes: 5
```   
