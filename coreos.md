## coreos

### coreos vagrant
- Conflicting dependecies[fog-core]: Update vagarnt to latest version
```
wget -c https://releases.hashicorp.com/vagrant/2.2.3/vagrant_2.2.3_x86_64.deb
sudo dpkg -i vagrant_2.2.3_x86_64.deb
```
- clone
```
 git clone https://github.com/coreos/coreos-vagrant
 cd coreos-vagrant/
 cp config.rb.sample config.rb
 vi config.rb to change instatnce number to 3
 cp config.ign.sample config.ign
 curl https://discovery.etcd.io/new?size=3
 vi config.ign to update token form curl.
 vagrant up
 vagrant status
 vagrant ssh core-01
 core-01 $ etcdctl member list
```
