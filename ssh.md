# ssh 

## ssh command
- ssh user@remote 'bash -s' < script.sh
script should not use any tty. If the command is in background, using  > logfile 2>&1 &  or  > /dev/null 2>&1 &
