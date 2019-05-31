# Ansible: https://www.ansible.com/
Ansible is a simple IT automation engine that automates cloud provisioning, configuration management, application deployment, intra-service orchestration, and many other IT needs.

- Document: http://docs.ansible.com/ansible/index.html

## [Inventory](http://docs.ansible.com/ansible/latest/user_guide/intro_inventory.html)
Ansible works against multiple systems in your infrastructure at the same time. It does this by selecting portions of systems listed in Ansible’s inventory, which defaults to being saved in the location */etc/ansible/hosts*. You can specify a different inventory file using the *-i <path>* option on the command line.

- Hosts:  
In INI:
```
[jumper] 
ansible_port=5555
ansible_host=192.0.2.50
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

## Reusable Playbooks
There are 3 ways to reuse files and organize things: [**includes**, **imports**](https://docs.ansible.com/ansible/latest/user_guide/playbooks_reuse_includes.html), and [**roles**](https://docs.ansible.com/ansible/latest/user_guide/playbooks_reuse_roles.html).
- any **import\*** Tasks (import_playbook, import_tasks, etc.) are static: Ansible pre-processes all static imports during Playbook parsing time.
- any **include\*** Tasks (include_tasks, include_role, etc.) are dynamic: Dynamic includes are processed during runtime at the point in which that task is encountered

When it comes to Ansible task options like tags and conditional statements (when:):
- For **static imports**, the parent task options will be copied to all child tasks contained within the import.
- For **dynamic includes**, the task options will only apply to the dynamic task as it is evaluated, and will not be copied to child tasks.

## Ansible Configuration Settings
Ansible supports a few ways of providing configuration variables, mainly through environment variables, 
command line switches and an ini file named ansible.cfg.

Starting at Ansible 2.4 the ansible-config utility allows users to see all the configuration settings available, their defaults, how to set them and where their current value comes from.

Changes can be made and used in a configuration file which will be searched for in the following order:
- ANSIBLE_CONFIG (environment variable if set)
- ansible.cfg (in the current directory)
- ~/.ansible.cfg (in the home directory)
- /etc/ansible/ansible.cfg

Ansible will process the above list and use the first file found, all others are ignored.

 ## [Variable](http://docs.ansible.com/ansible/latest/user_guide/playbooks_variables.html)
 - 
 
 ## [Template jinja2](http://docs.ansible.com/ansible/latest/user_guide/playbooks_templating.html)
 
 - [Conditionas](https://docs.ansible.com/ansible/latest/user_guide/playbooks_conditionals.html)
 
 - [Loop](https://docs.ansible.com/ansible/latest/user_guide/playbooks_loops.html)
 
 ## [Roles](https://docs.ansible.com/ansible/latest/user_guide/playbooks_reuse_roles.html)
 
 
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

## Commands
- ansible
```
ansible <host-pattern> [options]
```
- ansible-playbook
```
ansible-playbook [options] playbook.yml [playbook2 ...]
options:
-i: 
    specify inventory host path (could use *.ini format)
-e, --extra-vars
    set additional variables as key=value or YAML/JSON, if filename prepend with @
```
- ansible-inventory
- ansible-config
- ansible-console 
- ansible-doc 
- ansible-galaxy 
- ansible-pull 
- ansible-vault


## variable files (.yml): can be ref in \*.yml and \*.j2 template files as {{ name }}
```
name: value      # ref as {{ name }}

level1:
   name1: value1   # ref as {{ level1.name1 }}
   name2: value2   # ref as {{ level1.name2 }}

xxConfig: true
yyConfig: true

```

## roles: under roles/
```
roles/${role1}/defaults/main.yml
roles/${role1}/tasks/main.yml
#tasks for ${role}
- name:   desc
  template:
     src: "{{ item }}"
     desc: "destfile"
     owner: "{{ owner }}"
     group: "{{ group }}"
     mode: 0644
  with_filelog:
     - "../template/*.cfg.j2"
     - "../template/profile*.j2"
  when xxxConfigs == true     

- name: Remove  files
  file: path="{{ item }}" state=absent
  with_items:
    - "{{ my_dir }}/cfg/etc/file1.xml"
    - "{{ my_dir }}/cfg/etc/file2.xml"
  when: yyConfig == true
```
