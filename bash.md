Bash
======

  
## [Reference](https://www.gnu.org/software/bash/manual/bash.html)
#### Pipeline
 a sequence of one or more commands separated by one of the control operators **|** or **|&**:
```bash
[time [-p]] [!] command1 [ | or |& command2 ] …
```
#### List of Commands
sequence of one or more pipelines separated by one of the operators **;**, **&**, **&&**, or **||**, and optionally terminated by one of **;**, **&**, or a **newline**

#### Condition: if-elif-else; case
  - if
```bash
if test-commands; then
  consequent-commands;
[elif more-test-commands; then
  more-consequents;]
[else alternate-consequents;]
fi
```
  - case 
```bash
case word in [ [(] pattern [| pattern]…) command-list ;;]… esac
```
#### Loop: until; while; for;select
  - until
```bash
 until test-commands; do consequent-commands; done
```
  - while
```bash
 while test-commands; do consequent-commands; done
```
  - for
```bash
 for name [ [in [words …] ] ; ] do commands; done
 
 for (( expr1 ; expr2 ; expr3 )) ; do commands ; done
```
  - select
```bash
select name [in words …]; do commands; done
```

#### Expression
  - ((…)): The arithmetic expression is evaluated according to the rules. If the value of the expression is non-zero, the return status is 0; otherwise the return status is 1
```bash  
(( expression ))
```
  - [[…]]: Return a status of 0 or 1 depending on the evaluation of the conditional expression expression.
```bash  
 [[ expression ]]
```
  - combined expressions:
```bash  
( expression )
! expression
expression1 && expression2
expression1 || expression2
```
#### Special Parameters
- *****:  (**$***) Expands to the positional parameters, starting from one.
- **@**: (**$@**) Expands to the positional parameters, starting from one.
- **#**: (**$#**) Expands to the number of positional parameters in decimal.
- **?**: (**$?**) Expands to the exit status of the most recently executed foreground pipeline.
- **-**: (**$-**, a hyphen.) Expands to the current option flags as specified upon invocation, by the set builtin command, or those set by the shell itself (such as the -i option).
- **$**: (**$$**) Expands to the process ID of the shell. In a () subshell, it expands to the process ID of the invoking shell, not the subshell.
- **!**:  (**$!**) Expands to the process ID of the job most recently placed into the background, whether executed as an asynchronous command or using the bg builtin.
- **0**: (**$0**) Expands to the name of the shell or shell script. 



## Tips
- [Detect OS type](http://stackoverflow.com/questions/3466166/how-to-check-if-running-in-cygwin-mac-or-linux)
```
** uname -s **
```
