Bash
======

* Item 1
* Item 2
  * Item 2a
  * Item 2b
  
## [Reference](https://www.gnu.org/software/bash/manual/bash.html)
#### Pipeline: a sequence of one or more commands separated by one of the control operators **|** or **|&**:
```bash
[time [-p]] [!] command1 [ | or |& command2 ] …
```
#### List of Commands: sequence of one or more pipelines separated by one of the operators **;**, **&**, **&&**, or **||**, and optionally terminated by one of **;**, **&**, or a **newline**

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
  - ((…))
```bash  
(( expression ))
```

  - [[…]]
```bash  
 [[ expression ]]
```

## Tips
- [Detect OS type](http://stackoverflow.com/questions/3466166/how-to-check-if-running-in-cygwin-mac-or-linux)
```
** uname -s **
```
