Bash
======

## [Programming](http://tldp.org/HOWTO/Bash-Prog-Intro-HOWTO.html)
## [Reference](https://www.gnu.org/software/bash/manual/bash.html)

- Condition: if-elif-else-fi
 - if
 
if test-commands; then
  consequent-commands;
[elif more-test-commands; then
  more-consequents;]
[else alternate-consequents;]
fi

 -case 
 
case word in [ [(] pattern [| pattern]…) command-list ;;]… esac

- Loop: for; while; 
 - until
 until test-commands; do consequent-commands; done
 - while
 while test-commands; do consequent-commands; done
 - for
 for name [ [in [words …] ] ; ] do commands; done
 
 for (( expr1 ; expr2 ; expr3 )) ; do commands ; done
 
## Tips
- [Detect OS type](http://stackoverflow.com/questions/3466166/how-to-check-if-running-in-cygwin-mac-or-linux)

** uname -s **

