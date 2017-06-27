### Issue: echo on the same line in cgwin
- Add the the following lines to .bashrc:
```
PS1='\[\e[32m\]\u@\h:\W> \[\e[0m\]'
TERM=cygwin
export PS1
export TERM
```
