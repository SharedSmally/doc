#
#How to Increase Number of Open Files Limit in Linux
#https://www.tecmint.com/increase-set-open-file-limits-in-linux/
#
#Check Hard Limit in Linux
# ulimit -Hn
#4096
#Check Soft Limits in Linux
# ulimit -Sn
#1024
# su marin
$ ulimit -Sn
#1024
$ ulimit -Hn
#4096
#
#How to Check System wide File Descriptors Limits in Linux
#Sysctl is used to configure kernel parameters at runtime.
#For example, to increase open file limit to 500000, you can use the following command as root:
# sysctl -w fs.file-max=500000
#You can check the current value for opened files with the following command:
#$ cat /proc/sys/fs/file-max
#With the above command the changes you have made will only remain active until the next reboot. If you wish to apply them permanently, you will have to edit the following file:
# vi /etc/sysctl.conf
#Add the following line:
#fs.file-max=500000
#To verify the changes again use:
# cat /proc/sys/fs/file-max

#Set User Level Open File limits in Linux
#The above examples, showed how to set global limits, 
#but you may want to apply limits per user basis. For that purpose, as user root, you will need to edit the following file:
# vi /etc/security/limits.conf
#The lines that you should add take the following parameters:
#<domain>        <type>  <item>  <value>
#Here is an example of setting a soft and hard limits for user marin:
## Example hard limit for max opened files
#marin        hard nofile 4096
## Example soft limit for max opened files
#marin        soft nofile 1024
