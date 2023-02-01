# Ansible Playbook

## [YAML Syntax](https://docs.ansible.com/ansible/latest/reference_appendices/YAMLSyntax.html)
```
---
# A list of tasty fruits
- Apple
- Orange
- Strawberry
- Mango
fruits: ['Apple', 'Orange', 'Strawberry', 'Mango']

# An employee record
martin:
  name: Martin D'vloper
  job: Developer
  skill: Elite
martin: {name: Martin D'vloper, job: Developer, skill: Elite}  

# Values can span multiple lines using | or >
include_newlines: |
            exactly as you see
            will appear these three
            lines of poetry

fold_newlines: >
            this is really a
            single line of text
            despite appearances

#uses “{{ var }}” for variables. If a value after a colon starts with a “{”, YAML will think it is a dictionary, it must be quoted:
foo: "{{ variable }}"

#YAML converts certain strings into floating-point values, need to quote the value if it looks like a floating-point value:
version: "1.0"
```
## [variable](https://docs.ansible.com/ansible/latest/playbook_guide/playbooks_variables.html)
- [facts](https://docs.ansible.com/ansible/latest/playbook_guide/playbooks_vars_facts.html#vars-and-facts)
Variables related to remote systems are called facts.
```
- name: Print all available facts
  ansible.builtin.debug:
    var: ansible_facts   # json format of facts: ansible_facts and ansible_* variables
```
Use the facts/variable:
```
{{ ansible_facts['devices']['xvda']['model'] }}
{{ ansible_facts['nodename'] }}
{{ foo['field1'] }}
{{ foo.field1 }}  # may be quoted if starting with {{
```
- define variables: in inventory, in playbooks, in reusable files, in roles, and at the command line
```
- hosts: webservers
  vars:
    http_port: 80

- hosts: all
  remote_user: root
  vars:
    favcolor: blue
  vars_files:
    - /vars/external_vars.yml

# in the above example, this would be vars/external_vars.yml
somevar: somevalue
password: magic

# runtime
ansible-playbook release.yml --extra-vars "version=1.23.45 other_variable=foo"
ansible-playbook arcade.yml --extra-vars '{"pacman":"mrs","ghosts":["inky","pinky","clyde","sue"]}'

ansible-playbook release.yml --extra-vars "@some_file.json"
ansible-playbook release.yml --extra-vars "@some_file.yaml"
```
- 

## [loop](https://docs.ansible.com/ansible/latest/playbook_guide/playbooks_loops.html)
- The **with_<lookup\>** keywords rely on Lookup plugins - even items is a lookup.
- The **loop** keyword is equivalent to with_list, and is the best choice for simple loops.
```
- name: Add several users
  ansible.builtin.user:
    name: "{{ item }}"
    state: present
    groups: "wheel"
  loop:
     - testuser1
     - testuser2
  loop: "{{ somelist }}"
  loop: "{{ ['alice', 'bob'] | product(['clientdb', 'employeedb', 'providerdb']) | list }}"  #jinja2 template
  with_fileglob: '*.txt'     
```

## [conditional](https://docs.ansible.com/ansible/latest/playbook_guide/playbooks_conditionals.html)
Ansible uses Jinja2 tests and filters in conditionals. Ansible supports all the standard tests and filters, and adds some unique ones as well.
```
tasks:
  - name: Configure SELinux to start mysql on any port
    ansible.posix.seboolean:
      name: mysql_connect_any
      state: true
      persistent: true
    when: ansible_selinux.status == "enabled"

tasks:
    - name: Register a variable
      ansible.builtin.shell: cat /etc/motd
      register: motd_contents

    - name: Use the variable in conditional statement
      ansible.builtin.shell: echo "motd contains the word hi"
      when: motd_contents.stdout.find('hi') != -1
```
