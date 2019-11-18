# [minishift](https://github.com/minishift/minishift)
Minishift is a tool for application development in local OpenShift clusters. It uses libmachine for provisioning VMs, and OpenShift Origin for running the cluster.
- [Release](https://github.com/minishift/minishift/releases)
- [Document](https://docs.okd.io/latest/welcome/index.html)
- [xterm](https://github.com/xtermjs/xterm.js/releases)
## Quickstart
- Start: creates an OpenShift cluster (download minishift-centos7.iso to start a VM)
```
$ minishift start
-- Starting local OpenShift cluster using 'kvm' hypervisor...
...
   OpenShift server started.
   The server is accessible via web console at:
       https://192.168.99.128:8443
   You are logged in as:
       User:     developer
       Password: developer

   To login as administrator:
       oc login -u system:admin
```

- Use [OpenShift Client CLI](https://docs.okd.io/latest/minishift/openshift/openshift-client-binary.html) (oc) to work with Minishift.
The oc binary is located in the ~/.minishift/cache/oc/v${VERSION}.
```
oc config use-context minishift
```

- Access dashboard
```
$ minishift console
```

## [Minishift Command Reference](https://docs.okd.io/latest/minishift/command-ref/minishift.html)
```
  minishift addons - Manages Minishift add-ons.
  minishift completion - Outputs minishift shell completion for the given shell (bash or zsh)
  minishift config - Modifies Minishift configuration properties.
  minishift console - Opens or displays the OpenShift Web Console URL.
  minishift delete - Deletes the Minishift VM.
  minishift docker-env - Sets Docker environment variables.
  minishift hostfolder - Manages host folders for the Minishift VM.
  minishift image - Exports and imports container images.
  minishift ip - Gets the IP address of the running cluster.
  minishift logs - Gets the logs of the running OpenShift cluster.
  minishift oc-env - Sets the path of the 'oc' binary.
  minishift openshift - Interacts with your local OpenShift cluster.
  minishift profile - Manages Minishift profiles.
  minishift services - Manage Minishift services
  minishift setup - Configures pre-requisites for Minishift on the host machine
  minishift ssh - Log in to or run a command on a Minishift VM with SSH.
  minishift start - Starts a local OpenShift cluster.
  minishift status - Gets the status of the local OpenShift cluster.
  minishift stop - Stops the running local OpenShift cluster.
  minishift update - Updates Minishift to the latest version.
  minishift version - Gets the version of Minishift.
```

## [oc CLI Reference](https://docs.okd.io/latest/cli_reference/get_started_cli.html)
```
```
