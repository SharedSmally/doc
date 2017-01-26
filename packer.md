#[Packer] (https://www.packer.io/)

## [Doc](https://www.packer.io/docs/); [github](https://github.com/mitchellh/packer)

## Command:
```
Usage: packer [--version] [--help] <command> [<args>]

Available commands are:
    build       build image(s) from template
    fix         fixes templates from old versions of packer
    inspect     see components of a template
    push        push a template and supporting files to a Packer build service
    validate    check that a template is valid
    version     Prints the Packer version
```
```
Usage: packer build [options] TEMPLATE
  Will execute multiple builds in parallel as defined in the template.
  The various artifacts created by the template will be outputted.
  
Options:
  -color=false               Disable color output (on by default)
  -debug                     Debug mode enabled for builds
  -except=foo,bar,baz        Build all builds other than these
  -only=foo,bar,baz          Build only the specified builds
  -force                     Force a build to continue if artifacts exist, deletes existing artifacts
  -machine-readable          Machine-readable output
  -on-error=[cleanup|abort|ask] If the build fails do: clean up (default), abort, or ask
  -parallel=false            Disable parallelization (on by default)
  -var 'key=value'           Variable for templates, can be used multiple times.
  -var-file=path             JSON file containing user variables.
```

## [Templates](https://www.packer.io/docs/templates/introduction.html)
Templates are JSON files that configure the various components of Packer in order to create one or more machine images.
- builders (required) is an array of one or more objects that defines the builders that will be used to create machine images for this template, and configures each of those builders. For more information on how to define and configure a builder, read the sub-section on configuring builders in templates.
- description (optional) is a string providing a description of what the template does. This output is used only in the inspect command.
- min_packer_version (optional) is a string that has a minimum Packer version that is required to parse the template. This can be used to ensure that proper versions of Packer are used with the template. A max version can't be specified because Packer retains backwards compatibility with packer fix.
- post-processors (optional) is an array of one or more objects that defines the various post-processing steps to take with the built images. If not specified, then no post-processing will be done. For more information on what post-processors do and how they're defined, read the sub-section on configuring post-processors in templates.
- provisioners (optional) is an array of one or more objects that defines the provisioners that will be used to install and configure software for the machines created by each of the builders. If it is not specified, then no provisioners will be run. For more information on how to define and configure a provisioner, read the sub-section on configuring provisioners in templates.
- variables (optional) is an object of one or more key/value strings that defines user variables contained in the template. If it is not specified, then no variables are defined. For more information on how to define and use user variables, read the sub-section on user variables in templates.

### Builders
A single builder definition maps to exactly one build. A builder definition is a JSON object that requires at least a type key. The type is the name of the builder that will be used to create a machine image for the build.
```
{
  "builders": [
    // ... one or more builder definitions here
     "type": "amazon-ebs",
     "access_key": "...",
     "secret_key": "..."
  ]
}
```
- [Amazon EC2 (AMI)](https://www.packer.io/docs/builders/amazon.html)
- [OpenStack](https://www.packer.io/docs/builders/openstack.html)
- [VirtualBox](https://www.packer.io/docs/builders/virtualbox.html)
- [Docker](https://www.packer.io/docs/builders/docker.html)
- Azure Resource Manager
- CloudStack
- DigitalOcean
- File
- Google Compute Engine
- Hyper-V
- Null
- 1&1
- Parallels
- ProfitBricks
- QEMU
- Triton (Joyent Public Cloud)
- VMware
- Custom

### PROVISIONERS
The provisioners section contains an array of all the provisioners that Packer should use to install and configure software within running machines prior to turning them into machine images.
```
{
  "provisioners": [
    // ... one or more provisioner definitions here
    {
      "type": "shell",
      "script": "script.sh"
    }
  ]
}
```
- Remote Shell
- Local Shell
- File Uploads
- PowerShell
- Windows Shell
- Ansible Local
- Ansible Remote
- Chef Client
- Chef Solo
- Puppet Masterless
- Puppet Server
- Salt
- Windows Restart
- Custom

### [Post-Processor](https://www.packer.io/docs/templates/post-processors.html)
The post-processor section within a template configures any post-processing that will be done to images built by the builders. Examples of post-processing would be compressing files, uploading artifacts, etc.
```
{
  "post-processors": [
    // ... one or more post-processor definitions here
    {
      "type": "compress",
      "format": "tar.gz"
    }
  ]
}
```
- Amazon Import
- Artifice
- Atlas
- Compress
- Checksum
- Docker Import
- Docker Push
- Docker Save
- Docker Tag
- Google Compute Export
- Local Shell
- Manifest
- Vagrant
- Vagrant Cloud
- vSphere

### Communicators
Every build is associated with a single communicator. Communicators are used to establish a connection for provisioning a remote machine (such as an AWS instance or local virtual machine).

### [Plugins](https://www.packer.io/docs/extend/plugins.html)
