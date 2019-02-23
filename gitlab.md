## Install [ gitlab ] ()
- create vagrant VM. See https://github.com/rgl/gitlab-vagrant. The default user/password: root/password.
- Resolve gitlab.example.com: 
```
echo '10.10.9.99 gitlab.example.com' | sudo tee -a /etc/hosts
```
- Create ssh key and import public keys in settings
```
ssh-keygen -o -f ~/.ssh/id_rsa
```
- Disable ssh verification:
```
export GIT_SSL_NO_VERIFY=true
```
- clone project:
```
git clone https://gitlab.example.com/${user}/${project}.git
```
