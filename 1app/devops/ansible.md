# [Ansible](https://www.ansible.com/)
- [Ansible reference](https://docs.ansible.com/)
- [Ansible Getting started](https://docs.ansible.com/ansible/latest/getting_started/index.html)
- [Jinja2 API doc](https://jinja.palletsprojects.com/en/3.1.x/)

## Ansible
- Install:
```
python3 -m pip install --user ansibl
```
- Create inventory for the remote nodes(IP or FQDN):
```
[myvirtualmachines]
192.0.2.50
192.0.2.51
192.0.2.52
```
- Verify the hosts in the inventory
```
ansible all --list-hosts
ansible all -m ping -u username
```
All the nodes should be accessible by ssh.

### Ansible playbook    
- Playbook: A list of plays that define the order in which Ansible performs operations, from top to bottom, to achieve an overall goal.
- Play: An ordered list of tasks that maps to managed nodes in an inventory.
- Task: A list of one or more modules that defines the operations that Ansible performs.
playbook.yaml
```
---
- name: Update web servers
  hosts: webservers
  remote_user: root

  tasks:
  - name: Ensure apache is at the latest version
    ansible.builtin.yum:
      name: httpd
      state: latest
  - name: Write the apache config file
    ansible.builtin.template:
      src: /srv/httpd.j2
      dest: /etc/httpd.conf

- name: Update db servers
  hosts: databases
  remote_user: root

  tasks:
  - name: Ensure postgresql is at the latest version
    ansible.builtin.yum:
      name: postgresql
      state: latest
  - name: Ensure that postgresql is started
    ansible.builtin.service:
      name: postgresql
      state: started
```
Run the playbook.
```
$ ansible-lint verify-apache.yml   # verify
$ ansible-playbook -i inventory.yaml playbook.yaml
```


## [Jinja2](https://palletsprojects.com/p/jinja/): Python template engine.
