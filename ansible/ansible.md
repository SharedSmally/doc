# Ansible(on Python, Shell and OpenSSH)
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
    - ansible-vault: encryption/decryption utility for Ansible data files

## [User Guide](https://docs.ansible.com/ansible/latest/user_guide/index.html)

## [Play Books](https://docs.ansible.com/ansible/latest/user_guide/playbooks.html)
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


