# [helm](https://helm.sh/)
- [Tutorial](https://computingforgeeks.com/install-and-use-helm-3-on-kubernetes-cluster/)
- [docs](https://helm.sh/docs/)

## Helm Tutorial

A Chart is a Helm package. It contains all of the resource definitions necessary to run an application, tool, or service inside of a Kubernetes cluster. 

A Repository is the place where charts can be collected and shared. It's the archive for Kubernetes packages.

A Release is an instance of a chart running in a Kubernetes cluster. One chart can often be installed many times into the same cluster. And each time it is installed, a new release is created. Each one will have its own release, which will in turn have its own release name.

Helm installs charts into Kubernetes, creating a new release for each installation. And to find new charts, you can search Helm chart repositories.

- Install Helm 3 on Linux
```
$ curl -fsSL -o get_helm.sh https://raw.githubusercontent.com/helm/helm/master/scripts/get-helm-3
$ chmod 700 get_helm.sh
$ ./get_helm.sh
$ helm version
```
Installation output:
```
Downloading https://get.helm.sh/helm-v3.4.0-linux-amd64.tar.gz
Verifying checksum... Done.
Preparing to install helm into /usr/local/bin
helm installed into /usr/local/bin/helm
```

- Add Helm Chart repository
```
$ helm repo rm stable
$ helm repo add stable https://charts.helm.sh/stable
$ helm search repo stable   # list all charts in given repository
$ helm search hub # searches the Artifact Hub, charts from different repositories.
```
| Name	| Old Location |	New Location |
| :---: | :---: | :---: |
| stable |	https://kubernetes-charts.storage.googleapis.com |	https://charts.helm.sh/stable |
| incubator	| https://kubernetes-charts-incubator.storage.googleapis.com | https://charts.helm.sh/incubator |


-  Install Applications on Helm Chart
```
$ kubectl config get-contexts
$ kubectl config current-context
$ kubectl config use-context k3s
Switched to context "k3s".

$ helm repo update  
$ helm show chart stable/nginx-ingress  # Get chart features:
$ helm install nginx-ingress stable/nginx-ingress  # Install the chart
$ helm ls  # Confirm installation: release
$ helm status nginx-ingress  #
$ helm uninstall nginx-ingress  # uninstall the release
$ helm list  
```

## Helm Charts and repositories
- Adding an external Helm repository
- Private repository - HTTP
- Private repository - S3:  s3://bucketname
- Private repository - GCS:  gs://bucketname
- Private repository - Azure


## Helm CLI command
- Common actions for Helm:
    - helm search:    search for charts
    - helm pull:      download a chart to your local directory to view
    - helm install:   upload the chart to Kubernetes
    - helm list:      list releases of charts
    
- Available Commands:
```
Usage:
  helm [command]

  completion  generate autocompletions script for the specified shell
  create      create a new chart with the given name
  dependency  manage a chart's dependencies
  env         helm client environment information
  get         download extended information of a named release
  help        Help about any command
  history     fetch release history
  install     install a chart
  lint        examine a chart for possible issues
  list        list releases
  package     package a chart directory into a chart archive
  plugin      install, list, or uninstall Helm plugins
  pull        download a chart from a repository and (optionally) unpack it in local directory
  repo        add, list, remove, update, and index chart repositories
  rollback    roll back a release to a previous revision
  search      search for a keyword in charts
  show        show information of a chart
  status      display the status of the named release
  template    locally render templates
  test        run tests for a release
  uninstall   uninstall a release
  upgrade     upgrade a release
  verify      verify that a chart at the given path has been signed and is valid
  version     print the client version information
```
