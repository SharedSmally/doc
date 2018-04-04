
## Java Redirect: Systen.out
```
ByteArrayOutputStream pipeOut = new ByteArrayOutputStream();

// Store the current System.out
PrintStream old_out = System.out;

// Replace redirect output or error to our stream
System.setOut(new PrintStream(pipeOut));  //Any PrintStream

// Do stuff
// System.out.println(xxx);
// Done stuff

// Revert back to the old System.out
System.setOut(old_out);
```
## Log rotation of stdout

- Redirect STDOUT and STDERR to a rotating logfile:
```
  command-program.sh >> /tmp/output.txt 2>&1 &
  
  command &>log.txt &                 #stdout and stderr to log.txt
  command 1>/dev/null &               #stdout to /dev/null, stderr still attached to shell
  command 1>output.log 2>error.log &  #stdout to output.log, stderr to error.log
```

- Create a logrotate config file under /etc/logrotate.d called whatever, output_roll here. Sample config:
```
/tmp/output.txt {
    notifempty
    missingok
    size 1G
    copytruncate
    start 0
    rotate 15
    compress
}
```

- Setup your cron job inside the /etc/crontab file
```
*  *  *  *  * root /usr/sbin/logrotate /etc/logrotate.d/output_roll
```
This will check the file every minute. You can adjust to suit your needs.

- Start it up:
```
$> service crond restart
```
