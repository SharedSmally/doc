# Ansible
Based on Python, Shell and OpenSSH
- [Documents](https://docs.ansible.com/ansible/latest/index.html)
- [Modules](https://docs.ansible.com/ansible/latest/modules/modules_by_category.html)
- [GitHub](https://github.com/ansible/ansible)
- [Commands](https://docs.ansible.com/ansible/latest/user_guide/command_line_tools.html)
    - ansible: define and run a single task ‘playbook’ against a set of hosts
    ```
      $ ansible [pattern] -m [module] -a "[module options]"  -u username
    ```
    - ansible-playbook: run Ansible playbooks, executing the defined tasks on the targeted hosts.
    - ansible-config: view, edit, and manage ansible configuration from ANSIBLE_CONFIG, ./ansible.cfg, ~/.ansible.cfg or /etc/ansible/ansible.cfg.
    - ansible-connection
    - ansible-console: REPL console for executing Ansible tasks
    - ansible-doc: plugin documentation tool
    - ansible-galaxy: manage Ansible roles in shared repositories
    - ansible-inventory: display or dump the configured inventory
    - ansible-pull: pull playbooks from a VCS repo and executes them for the local host
    ```
    ansible-playbook playbook.yml -f 10 -i inventory-file
    ```
    - ansible-vault: encryption/decryption utility for Ansible data files
    
## Ansible Basic 
- Tools
    - Verify ansible file
    ```
    ansible-lint playbook.yml
    ```
    - Run ansible
    ```
    ansible-playbook -i hosts main.yml 
    ```
    - Roles management
    ```
    ansible-galaxy init xxxrole
    ```
    - [Playbook, Role, Block, Task top levels](https://docs.ansible.com/ansible/latest/reference_appendices/playbooks_keywords.html)
    ```
    hosts; vars; var_files; tasks; handlers
    ```
    
- [Playbook Introduction](https://docs.ansible.com/ansible/latest/user_guide/playbooks_intro.html)
playbook is a YAML file to map a group of hosts to some well defined roles, represented by tasks. a task is nothing more than a call to an ansible module.
```
---
- hosts: webservers
  vars:
    http_port: 80
    max_clients: 200
  remote_user: root
  tasks:
  - name: ensure apache is at the latest version
    yum:
      name: httpd
      state: latest
  - name: write the apache config file
    template:
      src: /srv/httpd.j2
      dest: /etc/httpd.conf
    notify:
    - restart apache
  - name: ensure apache is running
    service:
      name: httpd
      state: started
  handlers:
    - name: restart apache
      service:
        name: httpd
        state: restarted
```
- [Best Practices](https://docs.ansible.com/ansible/latest/user_guide/playbooks_best_practices.html)  

## [Roles](https://docs.ansible.com/ansible/latest/user_guide/playbooks_reuse_roles.html)
Roles are ways of automatically loading certain vars_files, tasks, and handlers based on a known file structure. 
```
site.yml
webservers.yml
fooservers.yml
roles/
   common/
     tasks/
     handlers/
     files/
     templates/
     vars/
     defaults/
     meta/
   webservers/
     tasks/
     defaults/
     meta/
```
- tasks - contains the main list of tasks to be executed by the role.
- handlers - contains handlers, which may be used by this role or even anywhere outside this role.
- defaults - default variables for the role 
- vars - other variables for the role 
- files - contains files which can be deployed via this role.
- templates - contains templates which can be deployed via this role.
- meta - defines some meta data for this role. 

webservers.yml:
```
---
- hosts: webservers
  roles:
    - common
    - webservers
```

tasks/main.yml
```
# roles/example/tasks/main.yml
- name: added in 2.4, previously you used 'include'
  import_tasks: redhat.yml
  when: ansible_facts['os_family']|lower == 'redhat'
- import_tasks: debian.yml
  when: ansible_facts['os_family']|lower == 'debian'

# roles/example/tasks/redhat.yml
- yum:
    name: "httpd"
    state: present

# roles/example/tasks/debian.yml
- apt:
    name: "apache2"
    state: present
```

## Ansible Tutorial
- [Tutorial](https://www.tutorialspoint.com/ansible/index.htm)
    - [role tutorial](https://www.tutorialspoint.com/ansible/ansible_roles.htm)


## [User Guide](https://docs.ansible.com/ansible/latest/user_guide/index.html)


## [Play Books](https://docs.ansible.com/ansible/latest/user_guide/playbooks.html)

- [variables](https://docs.ansible.com/ansible/latest/user_guide/playbooks_variables.htm)
    - Define variables
```
- hosts: all
  remote_user: root
  vars:
    favcolor: blue
  vars_files:
    - /vars/external_vars.yml
  tasks:
    ```
    
    - Access variable
    ```
    {{ ansible_facts["eth0"]["ipv4"]["address"] }}
    {{ ansible_facts.eth0.ipv4.address }}
    {{ foo[0] }} # for array
    ```
    - Register Variables
    ```
 name: test play
  hosts: all
  tasks:
      - shell: cat /etc/motd
        register: motd_contents
      - shell: echo "motd contains the word hi"
        when: motd_contents.stdout.find('hi') != -1
    ```

- [conditionals](https://docs.ansible.com/ansible/latest/user_guide/playbooks_conditionals.html): when statement
```
tasks:
  - name: "shut down CentOS 6 and Debian 7 systems"
    command: /sbin/shutdown -t now
    when: (ansible_facts['distribution'] == "CentOS" and ansible_facts['distribution_major_version'] == "6") or
          (ansible_facts['distribution'] == "Debian" and ansible_facts['distribution_major_version'] == "7")

tasks:
    - command: echo {{ item }}
      loop: [ 0, 2, 4, 6, 8, 10 ]
      when: item > 5          
```
- [loop](https://docs.ansible.com/ansible/latest/user_guide/playbooks_loops.html):  loop and with_<lookup>
```
- name: add several users
  user:
    name: "{{ item }}"
    state: present
    groups: "wheel"
  loop:   #loop: "{{ somelist }}"
     - testuser1
     - testuser2
```
- [Block](https://docs.ansible.com/ansible/latest/user_guide/playbooks_blocks.html)

## [Jinja2 template](https://docs.ansible.com/ansible/latest/user_guide/playbooks_templating.html)

## [Modules](https://docs.ansible.com/ansible/latest/modules/modules_by_category.html)

## [Plugins](https://docs.ansible.com/ansible/latest/plugins/action.html)

## [YAML](https://docs.ansible.com/ansible/latest/reference_appendices/YAMLSyntax.html)
- All YAML files can optionally begin with --- and end with .... to indicate the start and end of a document.
- All members of a list are lines beginning at the same indentation level starting with a "- " (a dash and a space):
```
---
# A list of tasty fruits
- Apple
- Orange
- Strawberry
- Mango
...
```
- A dictionary is represented in a simple key: value form (the colon must be followed by a space):
```
# An employee record
martin:
    name: Martin D'vloper
    job: Developer
    skill: Elite
```
A space followed by the pound sign " #" starts a comment.
- Dictionaries and lists can also be represented in an abbreviated form if you really want to:
```
---
martin: {name: Martin D'vloper, job: Developer, skill: Elite}
['Apple', 'Orange', 'Strawberry', 'Mango']
```
- a boolean value (true/false) can be specified in several forms:
```
create_key: yes
needs_agent: no
knows_oop: True
likes_emacs: TRUE
uses_cvs: false
```
- use double quotes(can use escapes) or single quotes to quote hash values to the end of the line:
```
foo: 'somebody said I should put a colon here: so I did'
windows_drive: 'c:'

foo: "somebody said I should put a colon here: so I did"
windows_drive: "c:"
foo: "a \t TAB and a \n NEWLINE"
```
- uses “{{ var }}” for variables. If value starts with a quote the entire value must be quoted, not just part of it.
```
foo: "{{ variable }}"
foo: "{{ variable }}/additional/string/literal"
```
- More complicated data structures are possible, such as lists of dictionaries, dictionaries whose values are lists or a mix of both:
```
# Employee records
-  martin:
    name: Martin D'vloper
    job: Developer
    skills:
      - python
      - perl
      - pascal
-  tabitha:
    name: Tabitha Bitumen
    job: Developer
    skills:
      - lisp
      - fortran
      - erlang
```
- Values can span multiple lines using | or >. Spanning multiple lines using a “Literal Block Scalar” | will include the newlines and any trailing spaces. Using a “Folded Block Scalar” > will fold newlines to spaces; 
```
include_newlines: |
            exactly as you see
            will appear these three
            lines of poetry

fold_newlines: >
            this is really a
            single line of text
            despite appearances
```


