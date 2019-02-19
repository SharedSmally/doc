## setup K8S cluster.
Using [ coreos-vagrant repo ](https://github.com/coreos/coreos-vagrant). See [Seyup K8S cluster](https://stackoverflow.com/questions/49605297/coreos-cluster-with-vagrant-does-not-start-configure-etcd-correctly?rq=1)
- Master Nodes (server)
  Run api-server, controller and scheduler. Share data using etcd
- Working Nodes (client)
  Run k
  
### [ Helm ](https://helm.sh/): k8s package manager
- Helm has two parts: a client (helm) and a server (tiller)
- Tiller runs inside of your Kubernetes cluster, and manages releases (installations) of your charts.
- Helm runs on your laptop, CI/CD, or wherever you want it to run.
- Charts are Helm packages that contain at least two things:
     - A description of the package (Chart.yaml)
     -  One or more templates, which contain Kubernetes manifest files
- Charts can be stored on disk, or fetched from remote chart repositories (like Debian or RedHat packages)
