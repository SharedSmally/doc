# [minishift](https://github.com/minishift/minishift/) in Linux (use kvm)
- [Document](https://docs.okd.io/index.html)
- [Prepare kvm env](https://docs.okd.io/latest/minishift/getting-started/setting-up-virtualization-environment.html)
- [Install minishift release](https://github.com/minishift/minishift/releases)
   - minishift start [--vm-driver virtualbox/kvm]  [--show-libmachine-logs -v5]
   - minishift ssh/oc-env/docker-env/ip/console/image/addons
   - minishift status/update/stop/delete
   
- Web Console to start project/deploy applications

## [Container Image ISO](https://docs.okd.io/latest/minishift/using/choosing-iso-image.html)
  - centos iso
  - fedora iso
  - b2d iso (boot2docker)
  - [docker image] (https://hub.docker.com/) for [ openshift ](https://hub.docker.com/r/openshift/origin-control-plane/)
  
## Commands
  - minishift: manage minishift cluster
  - oc: client to minishift cluster
  
## Application Images
