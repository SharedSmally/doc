# Ansible: https://www.ansible.com/
Ansible is a simple IT automation engine that automates cloud provisioning, configuration management, application deployment, intra-service orchestration, and many other IT needs.

- Document: http://docs.ansible.com/ansible/index.html

## [Inventory](http://docs.ansible.com/ansible/latest/user_guide/intro_inventory.html)
Ansible works against multiple systems in your infrastructure at the same time. It does this by selecting portions of systems listed in Ansible’s inventory, which defaults to being saved in the location */etc/ansible/hosts*. You can specify a different inventory file using the *-i <path>* option on the command line.

- Hosts:  
In INI:
```
jumper ansible_port=5555 ansible_host=192.0.2.50
```
In YAML:
```
...
  hosts:
    jumper:
      ansible_port: 5555
      ansible_host: 192.0.2.50
```
- Group:
  
