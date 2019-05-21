# systemd: The new init system
-  Document: [pdf](http://0pointer.de/public/systemd-ebook-psankar.pdf); [man](https://fedoraproject.org/wiki/Systemd); [docs](http://0pointer.de/blog/projects/systemd-docs.html)
- Commands: systemctl
   - List Servives
       - 
   - Manage Services:
       - systemctl start _service_
       - systemctl stop _service_
       - systemctl restart _service_


The main executable for systemd, /lib/systemd/systemd. performs all calls that originally were present in scripts. systemd creates all sockets first and then spawns all processes in parallel.

systemd introduce the new concepts of units and targets. A target is analogous to a runlevel, and is composed of several units. systemd will execute units to reach a target. The instructions for each unit reside in the */lib/systemd/system/* directory (\*.target, \*.service, \*.socket, \*.slice, \*.mount, \*.target.wants/\*.service) . These files use a declarative format. The most common type of these units is the service unit, which is used to start a service. 

Units are defined using Unit Files
- Naming convention is name.unit_type
- Maintainer files: /usr/lib/systemd/system
- Administrator files: /etc/systemd/system
- Non-persistent, runtime data: /run/systemd
- Drop-ins: /etc/systemd/system/[name.type].d/\*.conf : 

unit files under /etc will take precedence over /usr. The config file /etc/systemd/system.conf

sshd.service:
```
[Unit]
Description=OpenSSH Daemon
Wants=sshdgenkeys.service
After=sshdgenkeys.service
After=network.target

[Service]/[Mount]|[Socket]|[Path]|[Timer]
ExecStart=/usr/bin/sshd -D
ExecReload=/bin/kill -HUP $MAINPID
KillMode=process
Restart=always

[Install]
WantedBy=multi-user.target
```

There are other types of unit files: socket, device, mount, automount, swap, target, path, timer, snapshot, slice and scope.  target is a special type of unit file that glues the other types together into a cohesive whole. 

multi-user.target:
```
[Unit]
Description=Multi-User System
Documentation=man:systemd.special(7)
Requires=basic.target
Conflicts=rescue.service rescue.target
After=basic.target rescue.service rescue.target
AllowIsolate=yes
```

basic.target
```
[Unit]
Description=Basic System
Documentation=man:systemd.special(7)
Requires=sysinit.target
Wants=sockets.target timers.target paths.target slices.target
After=sysinit.target sockets.target timers.target paths.target slices.target
JobTimeoutSec=15min
JobTimeoutAction=poweroff-force
```

The Requires and Wants directives defines the dependency chain among the units. The Requires directive denotes a hard requirement, and Wants denotes an optional requirement, but they don't imply order. If the After directive isn't specified, systemd will start the units in parallel.

### Common options:
- Description=Unit description
- Documentation=Documentation links
- Requires=Additional units required
- Before/After=Unit must start Before/After
- Wants=Weaker Requires
- Conflicts=Units cannot co-exist
- WantedBy/RequiredBy=Set other units requirement

### Service Activation
- Start up services when needed
    - Save resources
    - Increased reliability
    - Transparent to client
- Activation by Socket, Device, Path, Bus, and Timer
- Recommended to convert xinetd services to units
- Boot path determined by default.target

### Target “Wants” Directories:
/usr/lib/systemd/system/<name>.target.wants/
/etc/systemd/system/<name>.target.wants/
- Files are symlinks to actual unit files
- Empty target wants directories are placeholders
- systemctl list-dependencies multi-user.target --no-pager

### runlevel vs targets
Traditional Runlevel Equivalent Target Symlink Target
Runlevel 0 poweroff.target runlevel0.target
Runlevel 1 rescue.target runlevel1.target
Runlevel 2 multi-user.target runlevel2.target
Runlevel 3 multi-user.target runlevel3.target
Runlevel 4 multi-user.target runlevel4.target
Runlevel 5 graphical.target runlevel5.target
Runlevel 6 reboot.target runlevel6.target

target can contain other targets:
- graphical.target Supports multiple users, graphical and text-based logins
- multi-user.target Supports multiple users, text-based logins only
- rescue.target Single user, local file systems mounted and basic system initialization completed, networking is not activated
- emergency.target Single user, root file system is mounted read-only, only a few essential services are started, networking is not activated

commands for default target> It is just a symbol link in /etc/systemd/system/default.target.
- list default targets: systemctl get-default
- set default targets: systemctl set-default graphical.target
- list targets:  systemctl list-units --type target

System command: link to systemctl.
- halt systemctl halt Halts the system
- poweroff systemctl poweroff Powers off the system
- reboot systemctl reboot Restarts the system
- pm-suspend systemctl suspend Suspends the system
- pm-hibernate systemctl hibernate Hibernates the system
- pm-suspend-hybrid systemctl hybrid-sleep Hibernates and suspends the system



Timer units have unit files containing a [Timer] section and define how the TimeDateD subsystem of systemd will activate a future event. There are two types of timers: one that will activate after a time period based on a variable starting point, such as the systems boot, and another that activates at fixed intervals like a cron job. timer units are an alternative to cron jobs.

Systemd unit files also provide the means to describe what to do when a service crashes using the directives Restart or RestartSec. This feature allows systemd to take the role of process supervisor.

systemd refers to the init dæmon executable itself, namely /lib/systemd/systemd, and also refers to the set of utilities and programs used to manage the system and services. Chief among these utilities is the systemctl program that's used to manage services. such as to enable, start and disable services, find the status of a given service and also list all loaded units:
```
# systemctl enable sshd
# systemctl start sshd
# systemctl stop sshd
# systemctl status sshd
# systemctl list-units
# systemctl {start,stop,restart,reload} unit1 [unit2 …]
# systemctl {enable, disable, mask, unmask} unit [unit...]
```

Another important program is the journalctl utility to view and manage the systemd logging subsystem called journald. systemd's logfile is a binary file and using journalctl to view its contents:
```
Display full log: # journalctl --all
Tail the log: # journalctl -f
Filter log by executable: # journalctl /lib/systemd/systemd
Display log since last boot: # journalctl -b
Display errors from last boot: # journalctl -b -p err
```
