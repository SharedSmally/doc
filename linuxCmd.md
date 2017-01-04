Linux
======

## [/proc](http://man7.org/linux/man-pages/man5/proc.5.html): process related information
- OS platform: *uname _[-o|--operating-system] [-s|--kernel-name] [-r|--kernel-release] [-v|--kernel-version] [-n|--nodename] [-m|--machine] [-p --processor] [-i|--hardware-platform] _*: from /proc/version
- Get number of Processors:  *cat  /proc/cpuinfo | grep processor | wc -l*
- Get memory info: *more /proc/meminfo*
- /proc/loadavg: _f1 f2 f3 n1/n2_: load average over 1,5,15 mins (uptime).
- /proc/stat
- /proc/devices
- /proc/partitions
- /proc/filesystems: list of supported FS
- /proc/mounts
- /proc/swaps
- /proc/uptime
- /proc/net/: netstat  (netstat -e|-o)

## Device
- /device/
