# [Packer](https://www.packer.io/): Build Automated Machine Images on many platforms
- [Documents](https://www.packer.io/docs/)
- [packer CLI](https://www.packer.io/docs/commands)
- [Quick Start](https://learn.hashicorp.com/collections/packer/getting-started)

## [packer CLI](https://www.packer.io/docs/commands)
- [init](https://www.packer.io/docs/commands/init): download Packer plugin binaries.
      - ```-upgrade```: get the latest versions for all plugins.
- [build](https://www.packer.io/docs/commands/build):takes a template and runs all the builds within it to generate a set of artifacts.
      - ```-var```: Set a variable in your packer template. 
      - ```-var-file```: Set template variables from a file.   
- [console](https://www.packer.io/docs/commands/console): print out the variables
- [fmt](https://www.packer.io/docs/commands/fmt): format HCL2 configuration files to a canonical format and style
- [fix](https://www.packer.io/docs/commands/fix):finds backwards incompatible parts
- [inspect](https://www.packer.io/docs/commands/inspect):outputs the various components a template defines.
- [validate](https://www.packer.io/docs/commands/validate): validate the syntax and configuration of a template
- [hcl2_upgrade](https://www.packer.io/docs/commands/hcl2_upgrade): transpile a JSON configuration template to HCL2

The format with ```-machine-readable``` flag is:
```
timestamp,target,type,data...
```
 The Message Types for ```packer build```:
- ui: human-readable string that would be sent to stdout even not in machine-readable mode
     - say: in a non-machine-readable format, this would be bolded. Normally it is used for anouncements about beginning new steps in the build process
     - message: the most commonly used message type, used for basic updates during the build process.
     - error: reserved for errors
- artifact-count: how many artifacts a particular build produced.
- artifact: about what Packer created during its build. An example output pattern:```timestamp, buildname, artifact, artifact_number, key, value``` where key and value contain information about the artifact.


## [Template](https://www.packer.io/docs/templates): 
The configuration file to define what  and how a image will be built use the Hashicorp Configuration Language (HCL). 
- [HCL template](https://www.packer.io/docs/templates/hcl_templates):New template
- [JSON template](https://www.packer.io/docs/templates/legacy_json_templates)

### [HCL template](https://www.packer.io/docs/templates/hcl_templates)
- [Guide](https://www.packer.io/guides/hcl)
#### Comments:
- # begins a single-line comment, ending at the end of the line.
- // also begins a single-line comment, as an alternative to #.
- /* and */ are start and end delimiters for a comment that might span over multiple lines.

#### Multi-line strings
```
variable "long_key" {
  type = "string"
  default = <<EOF
This is a long key.
Running over several lines.
It could be super handy for a boot_command.
EOF
}
```
#### Building blocks 
Currently Packer offers the ```source``` and ```build``` root blocks. They can be defined in any order and a build can import one or more source. Usually a source defines what we currently call a builder and a build can apply multiple provisioning steps to a source.
```
# folder/sources.pkr.hcl
source "amazon-ebs" "example-1" {
  ami_name = "example-1-ami"
}

source "virtualbox-iso" "example-2" {
  boot_command = <<EOF
<esc><esc><enter><wait>
/install/vmlinuz noapic
...
EOF
}
```
      
```
# folder/build.pkr.hcl
build {
  sources = [
    "source.amazon-ebs.example-1",
    "source.virtualbox-iso.example-2"
  ]

  provisioner "shell" {
    inline = [
      "echo 'it is alive !'"
    ]
  }
}
```



#### [variable Types](https://www.packer.io/guides/hcl/variables)
Defining Variables and locals in a file variables.pkr.hcl:
```
variable "weekday" {}

variable "sudo_password" {
  type =  string
  default = "mypassword"
  sensitive = true  // Sensitive vars are hidden from output
}

variable "flavor" {
  type = string
  default = "strawberry"
}

variable "exit_codes" {
  type = list(number)
  default = [0]
}

locals {
  ice_cream_flavor = "${var.flavor}-ice-cream"
  foo             = "bar"
}
```
Variable can be assigned from CLI or environment variables:
```
$ packer build -var region=us-west-2
$ packer build -var 'cidrs="10.0.0.0/16", "10.1.0.0/16"'
$ packer build -var-file="secret.pkrvars.hcl" -var-file="production.pkrvars.hcl" .
```
From file variables.pkrvars.hcl:
```
sudo_password = "partyparrot"
weekday       = "Sunday"
```
From file variables.json:
```
{
  "weekday": "sunday",
  "flavor": "mint"
}
```
- List
```
# implicitly by using brackets [...]
variable "cidrs" { default = [] }

# explicitly
variable "cidrs" { type = list }
```
variables.pkrvars.hcl file:
```
cidrs = [ "10.0.0.0/16", "10.1.0.0/16" ]
```
- Map
```
variable "amis" {
  type = map
  default = {
    "us-east-1" = "ami-b374d5a5"
    "us-west-2" = "ami-4b32be2b"
  }
}
```    
provided in CLI or variables file
```
$ packer build -var 'amis={ us-east-1 = "foo", us-west-2 = "bar" }'
amis = {
  "us-east-1" = "ami-abc123"
  "us-west-2" = "ami-def456"
}
```
## [Builder/Plugin](https://www.packer.io/docs/builders)
- [Docker](https://www.packer.io/docs/builders/docker)
- [OpenStack](https://www.packer.io/docs/builders/openstack)
- [Vagrant](https://www.packer.io/docs/builders/vagrant)

## [Provisioners](https://www.packer.io/docs/provisioners)
Install and configure the image after booting to prepare the system for use:
- installing packages
- patching the kernel
- creating users
- downloading application code

## [Post-Processors](https://www.packer.io/docs/post-processors)
Run after the image is built by the builder and provisioned by the provisioner(s):
- Compress
- Checksum
- Tag
- Import/Export
- Push

## [Plugin](https://www.packer.io/docs/plugins)


## Sample
- sample template file: example.pkr.hcl
```
variable "ami_name" {
  type    = string
  default = "my-custom-ami"
}

locals { timestamp = regex_replace(timestamp(), "[- TZ:]", "") }
# source blocks configure the builder plugins;
source "amazon-ebs" "example" {
  access_key    = "${var.aws_access_key}"
  ami_name      = "packer example ${local.timestamp}"
  instance_type = "t2.micro"
  region        = "us-east-1"
  secret_key    = "${var.aws_secret_key}"
  source_ami_filter {
    filters = {
      name                = "ubuntu/images/*ubuntu-xenial-16.04-amd64-server-*"
      root-device-type    = "ebs"
      virtualization-type = "hvm"
    }
    most_recent = true
    owners      = ["099720109477"]
  }
  ssh_username = "ubuntu"
}

# a build block invokes sources and runs provisioning steps on them.
build {
  sources = ["source.amazon-ebs.example"]
  provisioner "file" {
    destination = "/home/ubuntu/"
    source      = "./welcome.txt"
  }
  provisioner "shell" {
    inline = ["ls -al /home/ubuntu", "cat /home/ubuntu/welcome.txt"]
  }
  provisioner "shell" {
    script = "./example.sh"
  }
}

```
- Build a image
```
$ export AWS_ACCESS_KEY_ID=YOUR_ACCESS_KEY
$ export AWS_SECRET_ACCESS_KEY=YOUR_SECRET_KEY
$ packer validate example.pkr.hcl
$ packer build \
    -var 'ami_name=packer-tutorial' \
    example.pkr.hcl
```
