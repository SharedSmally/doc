## [coreos](https://coreos.com/)
### commands
- Memory size
```
$ awk '/MemTotal/ {print $2}' /proc/meminfo
```
- Number of cpu size
```
$ grep -c ^processor /proc/cpuinfo
```

### Vagrantfile: https://github.com/coreos/coreos-vagrant
```
Vagrant.configure("2") do |config|
  config.vm.hostname = "coreos"

  # always use Vagrants insecure key
  config.ssh.insert_key = false
  # forward ssh agent to easily ssh into the different machines
  config.ssh.forward_agent = true

  #disable Guest Additions
  config.vbguest.auto_update = false

  # latest coreos stable
  config.vm.box = "coreos-stable"
  config.vm.box_url = "https://stable.release.core-os.net/amd64-usr/current/coreos_production_vagrant_virtualbox.json"

  # private network
  config.vm.network "private_network", ip: "192.168.33.11"

  #
  config.vm.provider :virtualbox do |vb|
        #vb.gui = vm_gui
        vb.memory = 1024
        vb.cpus = 1
        #vb.customize ["modifyvm", :id, "--cpuexecutioncap", "#{$vb_cpuexecutioncap}"]
        #config.ignition.config_obj = vb
  end
end

```

- login: 
```

$vagrant ssh
core@coreos ~ $ ifconfig -a
eth0: flags=4163<UP,BROADCAST,RUNNING,MULTICAST>  mtu 1500
        inet 10.0.2.15  netmask 255.255.255.0  broadcast 10.0.2.255
        inet6 fe80::a00:27ff:fe20:243e  prefixlen 64  scopeid 0x20<link>
        ......        
eth1: flags=4163<UP,BROADCAST,RUNNING,MULTICAST>  mtu 1500
        inet 192.168.33.11  netmask 255.255.255.0  broadcast 192.168.33.255
        inet6 fe80::a00:27ff:fe2e:66bf  prefixlen 64  scopeid 0x20<link>
        ......        
lo: flags=73<UP,LOOPBACK,RUNNING>  mtu 65536
        ......

core@coreos ~ $ ls /usr/bin (/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/opt/bin) 
core@coreos ~ $ ls /usr/lib; /lib64  
cares; crypt; curl; dbus/dbus-glib; ev/event; expat; ffi; gssapi*; json-c; ldap; pcre; pcre2; pcrecpp; ssl3; xml2;

core@coreos ~ $ ps -ef            
UID        PID  PPID  C STIME TTY          TIME CMD
root         1     0  0 22:21 ?        00:00:01 /usr/lib/systemd/systemd --switched-root --system --deserialize 14
root         2     0  0 22:21 ?        00:00:00 [kthreadd]
root         3     2  0 22:21 ?        00:00:00 [rcu_gp]
root         4     2  0 22:21 ?        00:00:00 [rcu_par_gp]
root         6     2  0 22:21 ?        00:00:00 [kworker/0:0H-kblockd]
root         7     2  0 22:21 ?        00:00:00 [kworker/u2:0-events_unbound]
root         8     2  0 22:21 ?        00:00:00 [mm_percpu_wq]
root         9     2  0 22:21 ?        00:00:00 [ksoftirqd/0]
root        10     2  0 22:21 ?        00:00:00 [rcu_sched]
root        11     2  0 22:21 ?        00:00:00 [rcu_bh]
root        12     2  0 22:21 ?        00:00:00 [migration/0]
root        14     2  0 22:21 ?        00:00:00 [cpuhp/0]
root        15     2  0 22:21 ?        00:00:00 [kdevtmpfs]
root        16     2  0 22:21 ?        00:00:00 [netns]
root        17     2  0 22:21 ?        00:00:00 [kauditd]
root        18     2  0 22:21 ?        00:00:00 [khungtaskd]
root        19     2  0 22:21 ?        00:00:00 [oom_reaper]
root        20     2  0 22:21 ?        00:00:00 [writeback]
root        21     2  0 22:21 ?        00:00:00 [kcompactd0]
root        22     2  0 22:21 ?        00:00:00 [ksmd]
root        23     2  0 22:21 ?        00:00:00 [khugepaged]
root        24     2  0 22:21 ?        00:00:00 [crypto]
root        25     2  0 22:21 ?        00:00:00 [kintegrityd]
root        26     2  0 22:21 ?        00:00:00 [kblockd]
root        27     2  0 22:21 ?        00:00:00 [watchdogd]
root        28     2  0 22:21 ?        00:00:00 [kswapd0]
root        43     2  0 22:21 ?        00:00:00 [kthrotld]
root        44     2  0 22:21 ?        00:00:00 [acpi_thermal_pm]
root        45     2  0 22:21 ?        00:00:00 [ipv6_addrconf]
root       148     2  0 22:21 ?        00:00:00 [kworker/u2:2-events_unbound]
root       153     2  0 22:21 ?        00:00:00 [kworker/0:3-events]
root       302     2  0 22:21 ?        00:00:00 [ata_sff]
root       304     2  0 22:21 ?        00:00:00 [scsi_eh_0]
root       307     2  0 22:21 ?        00:00:00 [scsi_tmf_0]
root       309     2  0 22:21 ?        00:00:00 [scsi_eh_1]
root       311     2  0 22:21 ?        00:00:00 [scsi_tmf_1]
root       347     2  0 22:21 ?        00:00:00 [kworker/0:1H-kblockd]
root       387     2  0 22:21 ?        00:00:00 [kworker/u3:0]
root       425     2  0 22:21 ?        00:00:00 [kdmflush]
root       428     2  0 22:21 ?        00:00:00 [dm_bufio_cache]
root       431     2  0 22:21 ?        00:00:00 [kverityd]
root       435     2  0 22:21 ?        00:00:00 [jbd2/sda9-8]
root       437     2  0 22:21 ?        00:00:00 [ext4-rsv-conver]
root       448     2  0 22:21 ?        00:00:00 [ext4-rsv-conver]
root       618     1  0 22:21 ?        00:00:00 /usr/lib/systemd/systemd-journald
root       652     1  0 22:21 ?        00:00:00 /usr/lib/systemd/systemd-udevd
root       697     2  0 22:21 ?        00:00:00 [jbd2/sda6-8]
root       698     2  0 22:21 ?        00:00:00 [ext4-rsv-conver]
systemd+   709     1  0 22:21 ?        00:00:00 /usr/lib/systemd/systemd-timesyncd
systemd+   710     1  0 22:21 ?        00:00:00 /usr/lib/systemd/systemd-resolved
root       744     1  0 22:21 ?        00:00:00 /usr/lib/systemd/systemd-logind
message+   749     1  0 22:21 ?        00:00:00 /usr/bin/dbus-daemon --system --address=systemd: --nofork --nopidfile --systemd-activation
root       754     1  0 22:21 ?        00:00:00 /usr/sbin/update_engine -foreground -logtostderr
root       791     1  0 22:21 ?        00:00:00 /usr/lib/locksmith/locksmithd
root       844     1  0 22:21 tty1     00:00:00 /sbin/agetty -o -p -- \u --noclear tty1 linux
systemd+  1298     1  0 22:21 ?        00:00:00 /usr/lib/systemd/systemd-networkd
root      1359     2  0 22:26 ?        00:00:00 [kworker/0:0-events]
root      1371     1  0 22:32 ?        00:00:00 sshd: core [priv]
core      1374     1  0 22:32 ?        00:00:00 /usr/lib/systemd/systemd --user
core      1375  1374  0 22:32 ?        00:00:00 (sd-pam)
core      1379  1371  0 22:32 ?        00:00:00 sshd: core@pts/0
core      1380  1379  0 22:32 pts/0    00:00:00 -bash
core      1391  1380  0 22:35 pts/0    00:00:00 ps -ef
```
