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

systemd introduce the new concepts of units and targets. A target is analogous to a runlevel, and is composed of several units. systemd will execute units to reach a target. The instructions for each unit reside in the */lib/systemd/system/* directory (*.target, *.service, *.socket,*.slice, *.mount, *.target.wants/*.service) . These files use a declarative format. The most common type of these units is the service unit, which is used to start a service.

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

Timer units have unit files containing a [Timer] section and define how the TimeDateD subsystem of systemd will activate a future event. There are two types of timers: one that will activate after a time period based on a variable starting point, such as the systems boot, and another that activates at fixed intervals like a cron job. timer units are an alternative to cron jobs.

Systemd unit files also provide the means to describe what to do when a service crashes using the directives Restart or RestartSec. This feature allows systemd to take the role of process supervisor.

systemd refers to the init dæmon executable itself, namely /lib/systemd/systemd, and also refers to the set of utilities and programs used to manage the system and services. Chief among these utilities is the systemctl program that's used to manage services. such as to enable, start and disable services, find the status of a given service and also list all loaded units:
```
# systemctl enable sshd
# systemctl start sshd
# systemctl stop sshd
# systemctl status sshd
# systemctl list-units
```

Another important program is the journalctl utility to view and manage the systemd logging subsystem called journald. systemd's logfile is a binary file and using journalctl to view its contents:
```
Display full log: # journalctl --all
Tail the log: # journalctl -f
Filter log by executable: # journalctl /lib/systemd/systemd
Display log since last boot: # journalctl -b
Display errors from last boot: # journalctl -b -p err
```
