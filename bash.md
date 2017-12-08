Bash
======

## [Manual](https://linux.die.net/man/1/bash) and [Reference](https://www.gnu.org/software/bash/manual/bash.html)

## BASH Startup and Shutdown (Reads and executes commands)
-  As an interactive login shell, or as a non-interactive shell with --login
     - File **/etc/profile**, then first readable one from **~/.bash_profile**, **~/.bash_login**, and **~/.profile** (--noprofile inhibit it)
     - Files **~/.bash_logout** and **/etc/bash.bash_logout** when exit.

 - As an interactive non-login shell:
     - File **~/.bashrc** (inhibited by --norc)
     - File specified by **--rcfile** *file* option instead of ~/.bashrc
    
  - As a non-interactive shell:
     - File from the variable **BASH_ENV** in the environment. Simlar to ```if [ -n "$BASH_ENV" ]; then . "$BASH_ENV"; fi```
     
  - Invoked with the name *sh* (POSIX standard)
     - As an interactive login shell, or a non-interactive shell with --login:
          - Files **/etc/profile** and **~/.profile** (--noprofile inhibit it) 

## Tips
- Command-line arguments
```
fullname=$0   # full name of the command: first arg
echo " full name = " $numargs

numargs=$#
echo " args number = " $numargs

for arg
do
    echo "$arg"
done
```

- Parse Command Line Arguments: ** COMMAND ** *[options] <params> *
```
#!/bin/sh

while :
do
    case "$1" in
      -f | --file)
	  file="$2"   # check validity of $2
	  shift 2
	  ;;
      -h | --help)
	  display_help  # Call your function
	  # no shifting needed here, we're done.
	  exit 0
	  ;;
      -u | --user)
	  username="$2" # check validity of $2
	  shift 2
	  ;;
      -v | --verbose)
          #  It's better to assign a string rather than a number, and use
	  #    if [ "verbose" ] ...
	  verbose="verbose"
	  shift
	  ;;
      --) # End of all options
	  shift
	  break;
      -*)
	  echo "Error: Unknown option: $1" >&2
	  exit 1
	  ;;
      *)  # No more options
	  break
	  ;;
    esac
done
```

## Customized .bashrc
 See [LDP](http://www.tldp.org/LDP/abs/html/sample-bashrc.html) for the customized .bashrc and .bash_profile
 
#### Pipeline
 a sequence of one or more commands separated by one of the control operators **|** or **|&**:
```bash
[time [-p]] [!] command1 [ | or |& command2 ] …
```
#### List of Commands
sequence of one or more pipelines separated by one of the operators **;**, **&**, **&&**, or **||**, and optionally terminated by one of **;**, **&**, or a **newline**

#### Condition: if-elif-else; case
  - if
```
if test-commands; then
  consequent-commands;
[elif more-test-commands; then
  more-consequents;]
[else alternate-consequents;]
fi
```
  - case 
```
case word in [ [(] pattern [| pattern]…) command-list ;;]
… 
esac
```
#### Loop: until; while; for;select
  - until
```
 until test-commands; \
    do consequent-commands; \
 done
```
  - while
```
 while test-commands; 
    do consequent-commands; 
 done
```
  - for
```
 for name [ [in [words …] ] ; ] 
    do commands; 
 done
 
 for (( expr1 ; expr2 ; expr3 )) ; 
     do commands ; 
 done
```
  - select
```bash
select name [in words …]; 
    do commands; 
done
```

#### Expression
  - ((…)): The arithmetic expression is evaluated according to the rules. If the value of the expression is non-zero, the return status is 0; otherwise the return status is 1
```
(( expression ))
```
  - [[…]]: Return a status of 0 or 1 depending on the evaluation of the conditional expression expression.
```  
 [[ expression ]]
```
  - combined expressions:
```  
( expression )
! expression
expression1 && expression2
expression1 || expression2
```
#### Special Parameters
- *:  ($*) Expands to the positional parameters, starting from one.
- **@**: (**$@**) Expands to the positional parameters, starting from one.
- **#**: (**$#**) Expands to the number of positional parameters in decimal.
- **?**: (**$?**) Expands to the exit status of the most recently executed foreground pipeline.
- **-**: (**$-**, a hyphen.) Expands to the current option flags as specified upon invocation, by the set builtin command, or those set by the shell itself (such as the -i option).
- **$**: (**$$**) Expands to the process ID of the shell. In a () subshell, it expands to the process ID of the invoking shell, not the subshell.
- **!**:  (**$!**) Expands to the process ID of the job most recently placed into the background, whether executed as an asynchronous command or using the bg builtin.
- **0**: (**$0**) Expands to the name of the shell or shell script. 



#### [Builtins](https://www.gnu.org/software/bash/manual/bash.html#Bash-Builtins)
- : (a colon): Do nothing beyond expanding arguments and performing redirections. 
```bash 
 : [arguments]
```

- . (a period): Read and execute commands from the filename argument in the current shell context. 
```bash 
 . filename [arguments]
```

- break: Exit from a for, while, until, or select loop. 
```bash 
  break [n]
```

- continue: Resume the next iteration of an enclosing for, while, until, or select loop. 
```bash 
  continue [n]
```

-  cd: Change the current working directory to directory. I
```bash 
  cd [-L|[-P [-e]] [-@] [directory]
```

-  eval
```bash 
  eval [arguments]
```

-  exec
```bash 
  exec [-cl] [-a name] [command [arguments]]
```

-  exit
```bash 
  exit [n]
```

-  export
```bash 
  export [-fn] [-p] [name[=value]]
```

-  getopts
```bash 
  getopts optstring name [args]
 
```

-  hash
```bash 
  hash [-r] [-p filename] [-dt] [name]
```

-  pwd
```bash 
  pwd [-LP]
 ```

-  readonly
```bash 
  readonly [-aAf] [-p] [name[=value]] …
 ```

-  return
```bash 
  return [n]
 ```

-  shift
```bash 
  shift [n]
 ```

-  test
```bash 
  test [ expr ];  test [ ! expr ]; test expr1 -a expr2;  expr1 -o expr2
```

-  times
```bash 
  times
 ```

-  trap
```bash 
 
 trap [-lp] [arg] [sigspec …]
```

-  umask
```bash 
  umask [-p] [-S] [mode]
```

-  unset
```bash 
  unset [-fnv] [name]
 ```

-  set
```bash 
  set [--abefhkmnptuvxBCEHPT] [-o option-name] [argument …]
set [+abefhkmnptuvxBCEHPT] [+o option-name] [argument …]
```

- shopt
```bash 
 shopt [-pqsu] [-o] [optname …]
```

#### [Builtin Commands](https://www.gnu.org/software/bash/manual/bash.html#Shell-Builtin-Commands)
- alias
```bash 
alias [-p] [name[=value] …]
```

-  bind
```bash 
bind [-m keymap] [-lpsvPSVX]
bind [-m keymap] [-q function] [-u function] [-r keyseq]
bind [-m keymap] -f filename
bind [-m keymap] -x keyseq:shell-command
bind [-m keymap] keyseq:function-name
bind [-m keymap] keyseq:readline-command
```

- builtin
```bash  
 builtin [shell-builtin [args]]
 

```

- caller
```bash 
  caller [expr]

```

- command
```bash 
  command [-pVv] command [arguments …]

```

- declare
```bash 
  declare [-aAfFgilnrtux] [-p] [name[=value] …]

 ```

- echo
```bash 
  echo [-neE] [arg …]
 
 ```

- enable
```bash 
  enable [-a] [-dnps] [-f filename] [name …]
 
 ```

- help
```bash 
  help [-dms] [pattern]
 
 ```

- let
```bash 
  let expression [expression …]
 
 
```

-  local
```bash 
  local [option] name[=value] …
 
```

-  logout
```bash 
  logout [n]
 
```

-  mapfile
```bash 
  mapfile [-d delim] [-n count] [-O origin] [-s count] [-t] [-u fd]
    [-C callback] [-c quantum] [array]
	
```

- printf
```bash 
  printf [-v var] format [arguments]
 
 ```

- read
```bash 
  read [-ers] [-a aname] [-d delim] [-i text] [-n nchars]
    [-N nchars] [-p prompt] [-t timeout] [-u fd] [name …]	
```

- readarray
```bash 
  readarray [-d delim] [-n count] [-O origin] [-s count] [-t] [-u fd]
    [-C callback] [-c quantum] [array]

```

- source
```bash 
  source filename

```

-  type
```bash 
  type [-afptP] [name …]
 
```

-  typeset
```bash 
  typeset [-afFgrxilnrtux] [-p] [name[=value] …]
 
```

-  ulimit
```bash 
  ulimit [-HSabcdefiklmnpqrstuvxPT] [limit]
```

- unalias
```bash 
  unalias [-a] [name … ]
```

#### [Variables](https://www.gnu.org/software/bash/manual/bash.html#Bash-Variables)
- (command line arguments](http://wiki.bash-hackers.org/scripting/posparams)
#### [Conditional Expressions](https://www.gnu.org/software/bash/manual/bash.html#Bash-Conditional-Expressions)
#### [Shell Arithmetic](https://www.gnu.org/software/bash/manual/bash.html#Shell-Arithmetic)
#### [Directory Stack](https://www.gnu.org/software/bash/manual/bash.html#The-Directory-Stack)
#### [Job Control](https://www.gnu.org/software/bash/manual/bash.html#Job-Control-Builtins)
#### [Functions](http://tldp.org/HOWTO/Bash-Prog-Intro-HOWTO-8.html)
```bash
 #!/bin/bash 
                function quit {
                   exit
                }  
                function e {   # with parameter: $1, ...$9; $@
                    echo $1 
                }  
                e Hello
                e World
                quit
                echo foo 
```

## Tips
- [Detect OS type](http://stackoverflow.com/questions/3466166/how-to-check-if-running-in-cygwin-mac-or-linux)
```bash
uname -s
```
- Find exclude paths
```bash
find . ! -path './src/*' ! -path './include/*' ! -path './libsrc/*'  -name *.cpp  -s | xargs grep test_ > cpp.txt
cut -d':' -f1 cpp.txt | sort -u > cpp1.txt
```


