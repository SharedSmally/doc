## Login root
- Add the following to Vagrantfile:
```
config.ssh.username = 'root'
config.ssh.password = 'vagrant'
config.ssh.insert_key = 'true'
```
- set a root password in vagrant first
```
sudo passwd root

su -

```
