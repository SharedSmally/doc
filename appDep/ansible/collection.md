# Ansible Collections

- User Guide: https://docs.ansible.com/ansible/latest/user_guide/collections_using.html
- Collection Index:  https://docs.ansible.com/ansible/latest/collections/index.html

## builtin: ansible.builtin
- [builtin modules](https://docs.ansible.com/ansible/latest/collections/ansible/builtin/index.html#plugins-in-ansible-builtin)

### package installation
- apt
- yum
- dnf
- dpkg

## group/user
- group
- user
- sudo/su/runas

## service: 
- systemd
- sysvinit

## cron

### file
- copy
- stat
- file
- ini files
- line files
- json

### command/shell/script
- command: Run the command directly without using shell, no shell features, such as redirect, pipe, ... (local command)
- shell: using the shell woth shell features (local shell file)
- script: copy the script for remote host, then run it using shell.

