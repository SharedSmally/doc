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
 
 ## [Variable](http://docs.ansible.com/ansible/latest/user_guide/playbooks_variables.html)
 - 
 
 ## [Template jinja2](http://docs.ansible.com/ansible/latest/user_guide/playbooks_templating.html)
 
 ## [Conditionas]()
 
 ## [Loop]()
 
 ## [Roles]()
 
 ## [Modules](http://docs.ansible.com/ansible/latest/user_guide/modules.html)
 - In command line, using *-m* for module, *-a* for module arguments
 ```
ansible webservers -m service -a "name=httpd state=started"
ansible webservers -m ping
ansible webservers -m command -a "/sbin/reboot -t now"
 ```
- In playbook of full format 
 ```
 - name: reboot the servers
  action: command /sbin/reboot -t now
  ```
- In playbook of short format
```
- name: reboot the servers
  command: /sbin/reboot -t now
```
- In playboo using yaml syntax for ‘complex args’
```
- name: restart webserver
  service:
    name: httpd
    state: restarted
 ```
 - List all modules or module document
 ```
 ansible-doc -l
 ansible-doc yum
 ```
