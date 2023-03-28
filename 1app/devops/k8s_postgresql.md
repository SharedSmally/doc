# Postgresql
- Zolando Postgres Operator: https://github.com/zalando/postgres-operator
- Postgres Operator Start: https://postgres-operator.readthedocs.io/en/latest/quickstart/
- [Postgres Operator Introduction](https://cloud.redhat.com/blog/introducing-operators-putting-operational-knowledge-into-software)
An Operator is an application-specific controller that extends the Kubernetes API to create, configure, and manage instances of complex stateful applications on behalf of a Kubernetes user; manage multiple stateful instances across the cluster.
- etcd Operator 
- Prometheus Operator

## Postgres operator: https://postgres-operator.readthedocs.io/en/latest/
manages PostgreSQL clusters on Kubernetes (K8s)
- watches additions, updates, and deletions of [PostgreSQL cluster manifests](https://github.com/zalando/postgres-operator/blob/master/manifests/complete-postgres-manifest.yaml) and changes the running clusters accordingly. 
- watches updates to [its own configuration - ConfigMag](https://github.com/zalando/postgres-operator/blob/master/manifests/configmap.yaml) and alters running Postgres clusters if necessary. 
- periodically synchronizes the actual state of each Postgres cluster with the desired state defined in the cluster's manifest.

### Components
- Run Patroni (python) based clusters on K8s
- Spilo: Image include both Patroni + PostgreSQL

### K8S Components
- Stateless: Deployment, Easy
- Stateful: Hard
Concepts: 
- Resources: ReplicaSet, Services, Deployments, and Daemon Sets.
- Controllers.
An Operator builds upon the basic Kubernetes resource and controller concepts and adds a set of knowledge or configuration that allows the Operator to execute common application tasks. 
- Operators should install as a single deployment e.g. kubectl create -f https://coreos.com/operators/etcd/latest/deployment.yaml and take no additional action once installed.
- Operators should create a new third party type when installed into Kubernetes. A user will create new application instance using this type.
- Operators should leverage built-in Kubernetes primitives like Services and Replica Sets when possible to leverage well-tested and well-understood code.
- Operators should be backwards compatible and always understand previous versions of resources a user has created.
- Operators should be designed so application instances continue to run unaffected if the Operator is stopped or removed.
- Operators should give users the ability to declare a desired version and orchestrate application upgrades based on the desired version. Not upgrading software is a common source of operational bugs and security issues and Operators can help users more confidently address this burden.
- Operators should be tested against a "Chaos Monkey" test suite that simulates potential failures of Pods, configuration, and networking.

Helm is a tool for packaging multiple Kubernetes resources into a single package. 

The Postgres WAL (Write-Ahead Log) is the location in the Postgres cluster where all changes to the cluster's data files are recorded before they're written to the heap. When recovering from a crash, the WAL contains enough data for Postgres to restore its state to the last committed transaction. The main advantages of WAL are, it works as a replication of databases
```
kubectl create -f manifests/configmap.yaml
kubectl create -f manifests/operator-service-account-rbac.yaml
kubectl create -f manifests/postgres-operator.yaml
kubectl create -f manifests/minimal-postgres-manifest.yaml
```
