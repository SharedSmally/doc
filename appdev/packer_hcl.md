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

## [Builder](https://www.packer.io/docs/builders)
Create machines and generating images from them for various platforms
- [Community builders](https://www.packer.io/community-tools#community-builders)
- [Jeff Geerling's Vagrant Box Packer Builds](https://github.com/geerlingguy/packer-boxes/blob/master/README.md)
Built-in Builders
- [AWS](https://www.packer.io/docs/builders/amazon)
- [Docker](https://www.packer.io/docs/builders/docker): [centos8 docker](https://hub.docker.com/_/centos)
Must specify (only) one of commit, discard, or export_path:
      - commit (bool): If true, the container will be committed to an image rather than exported.
      - discard (bool): Throw away the container when the build is complete, useful for the artifice post-processor.
      - export_path (string): The path where the final container will be exported as a tar file.
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
Allowed metadata fields that can be changed are:
    - CMD: String, supports both array (escaped) and string form
```
        EX: "CMD [\"nginx\", \"-g\", \"daemon off;\"]" corresponds to Docker exec form
        EX: "CMD nginx -g daemon off;" corresponds to Docker shell form, invokes a command shell first
```        
    - ENTRYPOINT: String, supports both array (escaped) and string form
```    
        EX: "ENTRYPOINT [\"/bin/sh\", \"-c\", \"/var/www/start.sh\"]" corresponds to Docker exec form
        EX: "ENTRYPOINT /var/www/start.sh" corresponds to Docker shell form, invokes a command shell first
```        
    - ENV: String, note there is no equal sign: "ENV HOSTNAME www.example.com" not "ENV HOSTNAME=www.example.com"
    - EXPOSE: String, space separated ports: "EXPOSE 80 443"
    - LABEL: String, space separated key=value pairs: "LABEL version=1.0"
    - ONBUILD: String: EX: "ONBUILD RUN date"
    - MAINTAINER: String, deprecated: "MAINTAINER NAME"
    - USER: String: "USER USERNAME"
    - VOLUME: String: "VOLUME FROM TO"
    - WORKDIR:String: "WORKDIR PATH"
        
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
- [QEMU](https://www.packer.io/docs/builders/qemu)
```
source "qemu" "example" {
  iso_url           = "http://mirror.raystedman.net/centos/6/isos/x86_64/CentOS-6.9-x86_64-minimal.iso"
  iso_checksum      = "md5:af4a1640c0c6f348c6c41f1ea9e192a2"
  output_directory  = "output_centos_tdhtest"
  shutdown_command  = "echo 'packer' | sudo -S shutdown -P now"
  disk_size         = "5000M"
  format            = "qcow2"
  accelerator       = "kvm"
  http_directory    = "path/to/httpdir"
  ssh_username      = "root"
  ssh_password      = "s0m3password"
  ssh_timeout       = "20m"
  vm_name           = "tdhtest"
  net_device        = "virtio-net"
  disk_interface    = "virtio"
  boot_wait         = "10s"
  boot_command      = ["<tab> text ks=http://{{ .HTTPIP }}:{{ .HTTPPort }}/centos6-ks.cfg<enter><wait>"]
}

build {
  sources = ["source.qemu.example"]
}
```

## [variable block](https://www.packer.io/docs/templates/hcl_templates/blocks/variable) and [template](https://www.packer.io/docs/templates/hcl_templates/variables)
- Types:
    - string
    - number
    - bool
    - list(<TYPE>)
    - set(<TYPE>)
    - map(<TYPE>)
    - object({<ATTR NAME> = <TYPE>, \.\.\. })
    - tuple([<TYPE>, \.\.\.])
```
variable "image_id" {
  type        = string
  description = "The id of the machine image (AMI) to use for the server."
}  
```
Build Variables:
  - name Represents the name of the build block being run. This is different than the name of the source block being run.
  - ID: Represents the vm being provisioned. For example, in Amazon it is the instance id; in digitalocean, it is the droplet id; in Vmware, it is the vm name.
  - Host, Port, User and Password: The host, port, user, and password that Packer uses to access the machine. 
  - ConnType: Type of communicator being used. For example, for SSH communicator this will be "ssh".
  - PackerRunUUID: Current build's unique id. Can be used to specify build artifacts. 
  - PackerHTTPIP, PackerHTTPPort, and PackerHTTPAddr: HTTP IP, port, and address of the file server Packer creates to serve items in the "http" dir to the vm. The HTTP address is displayed in the format IP:PORT.
  - SSHPublicKey and SSHPrivateKey: The public and private key that Packer uses to connect to the instance. 

## [locals block](https://www.packer.io/docs/templates/hcl_templates/blocks/locals) and [templates](https://www.packer.io/docs/templates/hcl_templates/locals)
```
local "mylocal" {
  expression = "${var.secret_api_key}"
  sensitive  = true
}

locals {
  instance_ids = "${concat(aws_instance.blue.*.id, aws_instance.green.*.id)}"
}

locals {
  default_name_prefix = "${var.project_name}-web"
  name_prefix         = "${var.name_prefix != "" ? var.name_prefix : local.default_name_prefix}"
}
```

## [packer Block](https://www.packer.io/docs/templates/hcl_templates/blocks/packer)
```
packer {
  required_plugins {
    happycloud = {
      version = ">= 2.7.0"
      source = "github.com/hashicorp/happycloud"
    }
  }
  required_version = ">= 1.2.0, < 2.0.0"
}
```
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

## [Expressions](https://www.packer.io/docs/templates/hcl_templates/expressions)

## [Functions](https://www.packer.io/docs/templates/hcl_templates/functions)


## [Communicators](https://www.packer.io/docs/communicators)
Communicators are the mechanism Packer uses to upload files, execute scripts, etc. on the machine being created, and are configured within the builder section.
- [ssh](https://www.packer.io/docs/communicators/ssh)

## [Provisioners](https://www.packer.io/docs/provisioners)
Provisioners use builtin and third-party software to install and configure the machine image after booting. 
- installing packages
- patching the kernel
- creating users
- downloading application code
```
  "provisioners": [
    {
      "type": "shell",
      "inline": [
        "sudo apt-get install -y python-pip",
        "sudo pip install ifs",
        "sudo ifs install consul --version=0.5.2"
      ]
    },
    {
      "type": "file",
      "source": "/usr/local/bin/consul",
      "destination": "consul",
      "direction": "download"
    }
  ],
```
-[ansible local](https://www.packer.io/docs/provisioners/ansible-local)
```
  provisioner "ansible-local" {
    playbook_file   = "./playbook.yml"
    extra_arguments = ["--extra-vars", "\"pizza_toppings=${var.topping}\""]
  }
```
-[ansible(remote)](https://www.packer.io/docs/provisioners/ansible)
```
    provisioner "ansible" {
      playbook_file = "./playbook.yml"
    }
```
- [Shell(remote)](https://www.packer.io/docs/provisioners/shell)
```
provisioner "shell" {
    inline = ["echo foo"]
}
```
-[Shell-local](https://www.packer.io/docs/provisioners/shell-local)
```
  provisioner "shell-local" {
    inline = ["echo foo"]
  }
```

###[Post Processor](https://www.packer.io/docs/post-processors)
- [aws import](https://www.packer.io/docs/post-processors/amazon-import)
- [docker-import](https://www.packer.io/docs/post-processors/docker-import)
- [docker push](https://www.packer.io/docs/post-processors/docker-push)
- [docker save](https://www.packer.io/docs/post-processors/docker-save)
- [docker tag](https://www.packer.io/docs/post-processors/docker-tag)
- [compress](https://www.packer.io/docs/post-processors/compress)
```
{
  "type": "compress",
  "output": "log_{{.BuildName}}.gz",
  "compression_level": 9
}
```
- [CheckSum](https://www.packer.io/docs/post-processors/checksum) 
```
post-processors "checksum" {
  checksum_types = ["sha1", "sha256"]
  output = "packer_{{.BuildName}}_{{.ChecksumType}}.checksum"
}
```
- [shell local](https://www.packer.io/docs/post-processors/shell-local)
```
  post-processor "shell-local" {
    inline = ["echo foo"]
  }
```
- [vagrant](https://www.packer.io/docs/post-processors/vagrant):  takes a build and converts the artifact into a valid Vagrant box
```
  post-processor "vagrant" {
    keep_input_artifact = true
    provider_override = "virtualbox"
  }
```
- [vagrant cloud](https://www.packer.io/docs/post-processors/vagrant-cloud)
```
  "post-processors": [
    {
      "type": "shell-local",
      "inline": ["echo Doing stuff..."]
    },
    [
      {
        "type": "vagrant",
        "include": ["image.iso"],
        "vagrantfile_template": "vagrantfile.tpl",
        "output": "proxycore_{{.Provider}}.box"
      },
      {
        "type": "vagrant-cloud",
        "box_tag": "hashicorp/precise64",
        "access_token": "{{user `cloud_token`}}",
        "version": "{{user `version`}}"
      }
    ]
  ]
```

Linux VM:
- QEMU is a type 2 hypervisor that runs within user space and performs virtual hardware emulation, can use underline KVM
- KVM is a type 1 hypervisor that runs in kernel space, that allows a user space program access to the hardware virtualization features of various processors.

libvirt:  primarily targets KVM VMs, but also manages Xen and LXC.
Unify the API and CLI of creating and managing VMs, provides CLI tools:
- virsh
- virt-manager
- virt-install
