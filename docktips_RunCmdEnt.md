
## Docker image and layer
When Docker runs a container, it runs an image inside it. This image is usually built by executing Docker instructions, 
which add layers on top of existing image or OS distribution. OS distribution is the initial image and every added 
layer creates a new image. Final Docker image reminds an onion with OS distribution inside and a number of layers on top of it.

### Shell form
```
<instruction> <command>
```
Example:
```
RUN apt-get install python3
CMD echo "Hello world"
ENTRYPOINT echo "Hello world"
```
When instruction is executed in shell form it calls _/bin/sh -c <command>_ and normal shell processing happens, and the env variable name is substituted.
```
docker run -it <image>
```

### Exec form
This is the preferred form for CMD and ENTRYPOINT instructions.
```
<instruction> ["executable", "param1", "param2", ...]
```
Example:
```
RUN ["apt-get", "install", "python3"]
CMD ["/bin/echo", "Hello world"]
ENTRYPOINT ["/bin/echo", "Hello world"]
```
When instruction is executed in exec form it calls executable directly, and shell processing does not happen, and the env variable name is not substituted:
```
docker run -it <image>
```

If need to run bash (or any other interpreter but sh), use exec form with _/bin/bash_ as executable:
```
ENV name John Dow
ENTRYPOINT ["/bin/bash", "-c", "echo Hello, $name"]
```

### Docker RUN vs CMD vs ENTRYPOINT
All three instructions (RUN, CMD and ENTRYPOINT) can be specified in shell form or exec form:
- RUN executes command(s) in a new layer and creates a new image. E.g., it is often used for installing software packages.
- CMD sets default command and/or parameters, which can be overwritten from command line when docker container runs.
- ENTRYPOINT configures a container that will run as an executable.

### RUN
RUN instruction is used to install application and packages requited for it. 
It executes any commands on top of the current image and creates a new layer by committing the results. 
Often there are multiple RUN instructions in a Dockerfile.
```
RUN <command> (shell form)
RUN ["executable", "param1", "param2"] (exec form)
```
Example:
```
RUN apt-get update && apt-get install -y \
    bzr \
    cvs \
    git \
    mercurial \
    subversion
```
_apt-get update_ and _apt-get install_ are executed in a single RUN instruction to make sure 
that the latest packages will be installed. If they are in a separate RUN instruction, then 
it would reuse a layer added by apt-get update, that could had been created a long time ago.

### CMD
CMD instruction is used to set a default command, which will be executed only when you run 
container without specifying a command. If Docker container runs with a command, the 
default command will be ignored. If Dockerfile has more than one CMD instruction, 
all but last CMD instructions are ignored.
```
CMD ["executable","param1","param2"] (exec form, preferred)
CMD command param1 param2 (shell form)
CMD ["param1","param2"] (used together with ENTREPOINT; sets additional default parameters 
         for ENTRYPOINT in exec form if container runs without command line arguments)
```
Example:
```
CMD echo "Hello world" 
```
when container runs as docker run -it <image> will produce output
```
Hello world
```
but  when container runs with a command, e.g., docker run -it <image> /bin/bash, CMD is ignored and bash interpreter runs instead:
```
root@xxxxxx:/#
```

### ENTRYPOINT
ENTRYPOINT instruction is used to configure a container that will run as an executable. 
It is similar to CMD that can be specified with parameters, but ENTRYPOINT command and 
parameters are not ignored when Docker container runs with command line parameters.
```
ENTRYPOINT ["executable", "param1", "param2"] (exec form, preferred)
ENTRYPOINT command param1 param2 (shell form)
```

Shell form of ENTRYPOINT ignores any CMD or docker run command line arguments.

Exec form of ENTRYPOINT can set commands and parameters and then use either form 
of CMD to set additional parameters that are more likely to be changed. 
ENTRYPOINT arguments are always used, while CMD ones can be overwritten by 
command line arguments provided when Docker container runs.
```
ENTRYPOINT ["/bin/echo", "Hello"]
CMD ["world"]
```
when container runs as *docker run -it <image>* will produce output
```
Hello world
```
but when container runs as *docker run -it <image>* John will result in
```
Hello John
```

### Usage
- Use RUN instructions to build the image by adding layers on top of initial image.
- Prefer ENTRYPOINT to CMD when building executable Docker image and need a 
  command always to be executed. Additionally use CMD if need to provide 
  extra default arguments that could be overwritten from command line when docker container runs.
- Choose CMD to provide a default command and/or arguments that can be overwritten
  from command line when docker container runs.

