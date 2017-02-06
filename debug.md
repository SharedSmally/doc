## gdb cmd

## Trace:  strace; ltrace; ptrace
- strace - trace system calls and signals
   strace -fqe open cmd
 -ltrace
 - ptrace

## Tools 
- lsof : list open files and libraries used for the process:  lsof -p process
- ldd : print shared library dependencies
- nm : list symbols from object files
- pmap :  report memory map of a process

## tcpdump

## Statistics
- iostat : Report Central Processing Unit (CPU) statistics and input/output statistics for devices and partitions
- netstat : Print network connections, routing tables, interface statistics, masquerade connections, and multicast memberships
- mpstat : Report processors related statistics.
- vmstat : Report virtual memory statistics
- vnstat : 

## Performance:


## Connectivity
- netstat -an | grep port | grep ESTABLISHED | awk '{print $5}' | sort | cut -d":" -f1 | uniq -c

