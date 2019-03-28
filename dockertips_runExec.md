## Docker
Both Docker *run* and *exec* execute commands in a Docker container.

## run
Use this to run a command in a new container. It is used when there is no container running, 
and need to create one, start it and then run a process on it.
```
docker run [OPTIONS] IMAGE [COMMAND] [ARG...]
docker run --name ubuntu_bash --rm -i -t ubuntu bash
```
Some options:
- _ --name_ assigns a name to the container, in this case ubuntu_bash
- _ --rm _ like the bash command rm it removes the container, but when it exits
- _ -i _ short for -interactive, this ensures STDIN is kept open even if not attached to the running container
- _ -t _, which can also be referenced with -tty , starts an interactive bash shell in the container
- The image for the container follows the options, here it is the image ubuntu
- The last part that follows the image, is the command you want to run: bash

## exec
This is used to run a command in an existing container. There already has a container running 
and want to change it or obtain something from it:
```
docker exec [OPTIONS] CONTAINER COMMAND [ARG...]
docker exec -d -w /temp ubuntu_bash touch my_file.sh
```
- -w followed by the directory or file path allows you to state which working directory you want to run the command in.
- -d or -detached means that the container will run in detached mode, so you can still continue to use your terminal session with the container running in the background. Don’t use this if you want to see what the container sends to STDOUT.
- The command is touch used to create the file with the name my_file.sh inside the /temp directory of the running container ubuntu_bash

