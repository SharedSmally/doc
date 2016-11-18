[ Makefile ](https://www.gnu.org/software/make/manual/make.html)
======

## Commands:
- List Targets:   make -qp | awk -F':' '/^[a-zA-Z0-9][^$#\/\t=]*:([^=]|$)/ {split($1,A,/ /);for(i in A)print A[i]}'

## Script:
 - statements concated with * \ *,  and each one ends with * ; *
 - if-else-endif
 
   if [ ! -f $file ]; then \ 

   echo "file ", $file, " not exists"; \ 
   
   fi   
 - for-loop
for var in ${vars}; do \ 

echo "variable:" $${usher}; \ 

done
 
 - function
 
 - target
|  target … : prerequisites …
|        recipe
|        …
|        …

## Arguments:
 - 
