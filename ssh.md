# ssh 

## (ssh manual](https://linux.die.net/man/1/ssh) 

## ssh command:   
- ssh user@remote 'bash -s' < script.sh

script should not use any tty. If the command is in background, using  > logfile 2>&1 &  or  > /dev/null 2>&1 &

- -i identity_file  (private key for RSA or DSA)
- -l login_name:  Specifies the user to log in as on the remote machine
- -p port:        Port to connect to on the remote host.
- -R [bind_address:]port:host:hostport:  remote address

## ssh agent
ssh-agent is a program to hold private keys used for public key authentication (RSA, DSA). The idea is that ssh-agent is started in the beginning of an X-session or a login session, and all other windows or programs are started as clients to the ssh-agent program.

The agent initially does not have any private keys. Keys are added using ssh-add(1). When executed without arguments, ssh-add(1) adds the files ~/.ssh/id_rsa, ~/.ssh/id_dsa and ~/.ssh/identity.

- exec ssh-agent bash
- ssh-add dlxs14_id_rsa

### [ssh-agent](https://linux.die.net/man/1/ssh-agent) command:
- ssh-agent [-c | -s] [-d] [-a bind_address] [-t life] [command [arg ...]]

### [ssh-add](https://linux.die.net/man/1/ssh-add) command: 
Adds RSA or DSA identities to the authentication agent, ssh-agent(1)
- ssh-add [-cDdLlXx] [-t life] [file ...]
- ssh-add -s reader
- ssh-add -e reader
- ssh-add -n [-T token]
