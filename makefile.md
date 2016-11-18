Makefile
======

Commands:
- List Targets:   make -qp | awk -F':' '/^[a-zA-Z0-9][^$#\/\t=]*:([^=]|$)/ {split($1,A,/ /);for(i in A)print A[i]}'

Script:
 - if-else-endif
   
 - for-loop
 	
  for var in ${vars}; do \
		 echo "variable:" $${usher}; \
	done
 
 - function
 
Arguments:
 - 
