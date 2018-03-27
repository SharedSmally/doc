#[Valgrind](http://valgrind.org/

## Quick Start
- Prepare program:
   - Compile your program with -g to include debugging information
   - Using -O0 is also a good idea, if you can tolerate the slowdown
   - With -O1 line numbers in error messages can be inaccurate, 
   - Use of -O2 and above is not recommended 
- Run program
   If you normally run your program like this:
```
  myprog arg1 arg2
```
   Use this command line:
```
  valgrind --leak-check=yes myprog arg1 arg2
```
 Memcheck is the default tool. The --leak-check option turns on the detailed memory leak detector.
 
 
