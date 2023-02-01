# [Ansible Role](https://docs.ansible.com/ansible/latest/playbook_guide/playbooks_reuse_roles.html)
Roles automatically load related vars, files, tasks, handlers, and other Ansible artifacts based on a known file structure. 
An Ansible role has a defined directory structure with eight main standard directories. At least one of these directories must be included 
in each role. 
```
roles/
    common/               # this hierarchy represents a "role"
        tasks/            #
            main.yml      #  <-- tasks file can include smaller files if warranted
        handlers/         #
            main.yml      #  <-- handlers file
        templates/        #  <-- files for use with the template resource
            ntp.conf.j2   #  <------- templates end in .j2
        files/            #
            bar.txt       #  <-- files for use with the copy resource
            foo.sh        #  <-- script files for use with the script resource
        vars/             #
            main.yml      #  <-- variables associated with this role
        defaults/         #
            main.yml      #  <-- default lower priority variables for this role
        meta/             #
            main.yml      #  <-- role dependencies
        library/          # roles can also include custom modules
        module_utils/     # roles can also include custom module_utils
        lookup_plugins/   # or other types of plugins, like lookup in this case
    webtier/              # same kind of structure as "common" was above, done for the webtier role
    monitoring/           # ""
    fooapp/               # ""
```
By default Ansible will look in each directory within a role for a main.yml file for relevant content (also main.yaml and main):
- tasks/main.yml - the main list of tasks that the role executes.
- handlers/main.yml - handlers, which may be used within or outside this role.
- library/my_module.py - modules, which may be used within this role (see Embedding modules and plugins in roles for more information).
- defaults/main.yml - default variables for the role (see Using Variables for more information). These variables have the lowest priority of any variables available, and can be easily overridden by any other variable, including inventory variables.
- vars/main.yml - other variables for the role (see Using Variables for more information).
- files/main.yml - files that the role deploys.
- templates/main.yml - templates that the role deploys.
- meta/main.yml - metadata for the role, including role dependencies and optional Galaxy metadata such as platforms supported.

## Using roles
- at the play level with the roles option: This is the classic way of using roles in a play.
- at the tasks level with include_role: You can reuse roles dynamically anywhere in the tasks section of a play using include_role.
- at the tasks level with import_role: You can reuse roles statically anywhere in the tasks section of a play using import_role.
```
- hosts: webservers
  roles:
    - common
    - webservers

- hosts: webservers
  roles:
    - common
    - role: foo_app_instance
      vars:
        dir: '/opt/a'
        app_port: 5000
      tags: typeA
    - role: foo_app_instance
      vars:
        dir: '/opt/b'
        app_port: 5001
      tags: typeB
```

## Role dependencies: automatically pull in other roles when using a role.

The roles do not have a parent/child relationship. Ansible loads all listed roles, runs the roles listed under dependencies first, then runs the role that lists them. The play object is the parent of all roles, including roles called by a dependencies list.

Role dependencies are stored in the meta/main.yml file within the role directory. This file should contain a list of roles and parameters to insert before the specified role. 
```
# roles/myapp/meta/main.yml
---
dependencies:
  - role: common
    vars:
      some_parameter: 3
  - role: apache
    vars:
      apache_port: 80
  - role: postgres
    vars:
      dbname: blarg
      other_parameter: 12
```



