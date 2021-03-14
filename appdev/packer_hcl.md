# Packer [HCL](https://www.packer.io/docs/templates/hcl_templates)

## Syntax
The main purpose of the HCL language is defining builds and sources in .pkr.hcl files:
```
source "amazon-ebs" "main" {
  ami_name = "main-ami"
}

<BLOCK TYPE> "<BLOCK LABEL>" "<BLOCK LABEL>" {
  # Block body
  <IDENTIFIER> = <EXPRESSION> # Argument
}
```
- Blocks are containers for other content and usually represent the configuration of some kind of object, like a source. 
- Blocks have a block type, can have zero or more labels, and have a body that contains any number of arguments and nested blocks. 
- Arguments assign a value to a name. They appear within blocks.
- Expressions represent a value, either literally or by referencing and combining other values. They appear as values for arguments, or within other expressions.

A block has a type (source here). Each block type defines how many labels must follow the type keyword. 

## [build block](https://www.packer.io/docs/templates/hcl_templates/blocks/build)
Defines what builders are started (```source```), how to provision them using ```provisioner``` and what to do with the artifacts using ```post-processor(s)```.
```
# build.pkr.hcl
build {
    # use the `name` field to name a build in the logs.
    name = "buildname"

    sources = [
        # use the optional plural `sources` list to simply use a `source` without changing any field.
        "source.amazon-ebs.example-1",
    ]

    source "source.amazon-ebs.example-2" {
        output = "different value"
        name = var.foo
    }

    provisioner "shell" {
        scripts = fileset(".", "scripts/{install,secure}.sh")
    }

    post-processor "shell-local" {
        inline = ["echo Hello World from ${source.type}.${source.name}"]
    }
}
```

## [source block](https://www.packer.io/docs/templates/hcl_templates/blocks/source)
The top-level source block defines reusable builder configuration blocks:
```
# sources.pkr.hcl
source "amazon-ebs" "example-1" {
    // ...
}

build {
  sources = [
    # Here Packer will use a default ami_name when saving the image.
    "source.amazon-ebs.example",
    "source.amazon-ebs.foo",
  ]
  # can access the source name and type from provisioners and post-processors
  provisioner "shell-local" {
    inline = ["echo ${source.name} and ${source.type}"]
  }
}
```

## [Builder]
Create machines and generating images from them for various platforms
- [Community builders](https://www.packer.io/community-tools#community-builders)
- [Jeff Geerling's Vagrant Box Packer Builds](https://github.com/geerlingguy/packer-boxes/blob/master/README.md)
Built-in Builders
- [AWS](https://www.packer.io/docs/builders/amazon)
- [Docker](https://www.packer.io/docs/builders/docker): [centos8 docker](https://hub.docker.com/_/centos)
```
source "docker" "centos8" {
    image = "centos:8"
    export_path = "centos8.tar"
    #commit = true
    changes = [
      "USER www-data",
      "WORKDIR /var/www",
      "ENV HOSTNAME www.example.com",
      "VOLUME /test1 /test2",
      "EXPOSE 80 443",
      "LABEL version=1.0",
      "ONBUILD RUN date",
      "CMD [\"nginx\", \"-g\", \"daemon off;\"]",
      "ENTRYPOINT /var/www/start.sh"
    ]
}
```
- [Vagrant](https://www.packer.io/docs/builders/vagrant): [centos8 vagrant]()
```
source "vagrant" "example" {
  communicator = "ssh"
  source_path = "centos/8"
  provider = "virtualbox"
  add_force = true
}

build {
  sources = ["source.vagrant.example"]
}
```

## [variable block](https://www.packer.io/docs/templates/hcl_templates/blocks/variable)

## [locals block](https://www.packer.io/docs/templates/hcl_templates/blocks/locals)

## [packer Block](https://www.packer.io/docs/templates/hcl_templates/blocks/packer)

## [data block](https://www.packer.io/docs/templates/hcl_templates/datasources):
Defines data sources within Packer configuration, used in locals and sources configuration.
It requests that Packer read from a given data source ("amazon-ami") and export the result under the given local name ("example"). 
```
# datasource.pkr.hcl
data "amazon-ami" "example" {
    filters = {
        virtualization-type = "hvm"
        name = "ubuntu/images/*ubuntu-xenial-16.04-amd64-server-*"
        root-device-type = "ebs"
    }
    owners = ["099720109477"]
    most_recent = true
}
```
A data source can output one or more attributes, which can be used by adding their key name to the data source unique identifier, 
like ```data.<TYPE>.<NAME>.<ATTRIBUTE>```, such as used in:
```
// in a local
locals {
  source_ami_id = data.amazon-ami.example.id
  source_ami_name = data.amazon-ami.example.name
 }
```
Packer support [Amazon Data Sources](https://www.packer.io/docs/datasources/amazon) now:
- amazon-ami: Filter and fetch an Amazon AMI to output all the AMI information.
- amazon-secretsmanager: Retrieve information about a Secrets Manager secret version, including its secret value.

Linux VM:
- QEMU is a type 2 hypervisor that runs within user space and performs virtual hardware emulation
- KVM is a type 1 hypervisor that runs in kernel space, that allows a user space program access to the hardware virtualization features of various processors.
