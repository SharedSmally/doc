# Ansible Book

A playbook is composed of one or more ‘plays’ in an ordered list. Each play executes part of the overall goal of the playbook, running one or more tasks. Each task calls an Ansible module.

- [keywords](https://docs.ansible.com/ansible/latest/reference_appendices/playbooks_keywords.html): in Play, Role, Block abd Task


## Variables

## Task
The units of action in Ansible

## Handler

## Modules
The units of code Ansible executes. 

## Collection
The distribution format for Ansible content that can include playbooks, roles, modules, and plugins. It can be installed and used through Ansible Galaxy. 

## [Role](https://docs.ansible.com/ansible/latest/user_guide/playbooks_reuse_roles.html)
Automatically load related vars, files, tasks, handlers, and other Ansible artifacts based on a known file structure.

Create roles directory via "mkdir roles", then initialize each role by **ansible-galaxy init _<role_name>_** to create the role directory structure. 

```
# playbooks
site.yml
webservers.yml
fooservers.yml
roles/
    common/
        tasks/
        handlers/
        library/
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
