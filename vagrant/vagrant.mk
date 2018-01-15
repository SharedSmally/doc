SSH_CFG=ssh.cfg
PORT=`grep "Port " ${SSH_CFG} | cut -d" " -f4 | xargs echo -n`
KEY =`grep "IdentityFile " ${SSH_CFG} | cut -d" " -f4 | xargs echo -n`
USER=`grep "User " ${SSH_CFG} | cut -d" " -f4 | xargs echo -n`
HOST=`grep "HostName " ${SSH_CFG} | cut -d" " -f4 | xargs echo -n`


main: ssh

ssh:ssh.cfg
        @ssh -i "${KEY}" ${USER}@${HOST} -p ${PORT}

ssh.cfg:
        vagrant ssh-config > $@

up:
        vagrant up

down:
        vagrant halt

status:
        vagrant status

provision:
        vagrant provision

clean:
        ${RM} -rf ${SSH_CFG}

cleanall:clean
        vagrant destroy

print:
        @echo "SSH Config: ${SSH_CFG};"
        @echo "Key File: ${KEY};"
        @echo "Host: ${HOST};"
        @echo "Port: ${PORT};"
        @echo "User: ${USER};"
