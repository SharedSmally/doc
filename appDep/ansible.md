# Ansible
- **ansible**: execute one task against hosts: **ansible -m ping -i inventory all**
- **ansible-playbook**: executable playbook, ansible script file (tasks): **ansible-playbook test.yml -i inventory all**
- **ansible-lint**: verify the ansible playbook
- ansible-inventory
- ansible-galaxy:
- ansible-vault: encrypt/decrypt messages
- ansible-pull/doc/config/console

## Tutorial
- Docs:https://docs.ansible.com/
    - core: https://docs.ansible.com/ansible-core/devel/index.html
    - playbook: https://docs.ansible.com/ansible/latest/user_guide/playbooks_intro.html
    - Galaxy: a free site for finding, downloading, and sharing community developed roles. https://docs.ansible.com/ansible/latest/galaxy/user_guide.html

## Install
Nodes environment:
- One control node: Run ansible; need Python 3.8
- Managed nodes: Ansible makes a connection over SSH and transfers modules using SFTP/SCP; need Python 2 or 3. 

SELinux needs libselinux-python.
- Install pip
```
$ curl https://bootstrap.pypa.io/get-pip.py -o get-pip.py
$ python get-pip.py --user
```
- Install ansible (2 collections: ansible-core, ansible-base)
```
$ python -m pip install --user ansible
```
- Install globally
```
$ sudo python get-pip.py
$ sudo python -m pip install ansible
```
- In centos
```
$ sudo yum install epel-release
$ sudo yum install ansible
```
- In ubuntu
```
$ sudo apt update
$ sudo apt install software-properties-common
$ sudo add-apt-repository --yes --update ppa:ansible/ansible
$ sudo apt install ansible
```

## Config
The config file: **/etc/ansible/ansible.cfg** and  **/etc/ansible/hosts**(default inventory, specified by **-i** _inventory_)

## [Inventory](https://docs.ansible.com/ansible/latest/user_guide/intro_inventory.html#intro-inventory)
Ansible works against multiple managed nodes or “hosts” in your infrastructure at the same time, using a list or group of lists known as inventory. Once your inventory is defined, Ansible use patterns to select the hosts or groups to run against.

- Inventory: a list of groups; default groups: all, ungrouped
- Group: a list of hosts, could include variables for the group, can be inheriting
- Host: host name with host variables and alias

Host and group variables can be stored in the file (/etc/ansible/group_vars/_group_name_,/etc/ansible/host_vars/_host_name_).

Can use multiple inventory sources with multiple -i: 
```
-i staging -i production
```
## Ansible Facts 
Ansible Facts is used for system information of the managed nodes, such as OS distribution, release, processor, IP address etc. The task of colleting this remote system information is referred as "Gathering facts" and the collected data or gathered information is referred as facts or variable.
```
$ ansible server2 -m file -a "path=/etc/ansible/facts.d state=directory" --become
```
