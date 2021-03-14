# [Vagrant](https://www.vagrantup.com/)
- [Vagrantfile](https://www.vagrantup.com/docs/vagrantfile)

## [vagrant CLI](https://www.vagrantup.com/docs/cli)
- [Box](https://www.vagrantup.com/docs/cli/box)
     - list
     - add / remove
     - outdated / prune
     - repackage NAME PROVIDER VERSION
     - update

### Create a new vagrant box
- Run vagrant up to create the Virtual Machine and vagrant ssh to login.
- Install your software if not already defined in you Vagrantfile.
- Exit the VM and run ```vagrant package --base my-new-box-name --output my-new-box-name.box```. Vagrant will export the actual VM in a file.
- Run ```vagrant box add my-new-box-name file:///c:/path/to/my-new-box-name.box``` (relative path also works: file://my-new-box-name.box) to import new box.
- vagrant box list will list the new box.
