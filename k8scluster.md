## setup K8S cluster.
Using [ coreos-vagrant repo ](https://github.com/coreos/coreos-vagrant). See [Setup K8S cluster](https://stackoverflow.com/questions/49605297/coreos-cluster-with-vagrant-does-not-start-configure-etcd-correctly?rq=1). Then login node and start etcd service (defined in etcd-member.service) that knows how to fetch and run etcd v3 in a Linux container. No etcd v3-series binary is directly included in the Container Linux filesystem
```
core@core-02 / $ sudo find ./ -name etcd-member.service
./usr/lib64/systemd/system/etcd-member.service
core@core-03 /etc $ sudo systemctl start etcd-member         
core@core-03 /etc $ etcdctl member list
8e9e05c52164694d: name=62cc90c281644510b86c6140c2446494 peerURLs=http://localhost:2380 clientURLs=http://localhost:2379 isLeader=true
```
- Master Nodes (server)
  Run api-server, controller and scheduler. Share data using etcd
- Working Nodes (client)
  Run k
  
### [ Helm ](https://helm.sh/): k8s package manager
- [ Binary Release ](https://github.com/helm/helm/releases/)
- Helm has two parts: a client (helm) and a server (tiller)
- Tiller runs inside of your Kubernetes cluster, and manages releases (installations) of your charts.
- Helm runs on your laptop, CI/CD, or wherever you want it to run.
- Charts are Helm packages that contain at least two things:
     - A description of the package (Chart.yaml)
     -  One or more templates, which contain Kubernetes manifest files
- Charts can be stored on disk, or fetched from remote chart repositories (like Debian or RedHat packages)
