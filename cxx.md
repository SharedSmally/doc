cxx
======

## Eclipse CXX (CDT)
 - Env setup:



 
 - CMake
    - CMake plugins: CMakeEclipse; CMakeEd; CMakeBuilder
 
 - Maven + Nar
 
 - Gradle + cxx
 
 
 ## [AutoMake/AutoConfig](https://www.gnu.org/software/automake/manual/automake.html):
 
 - Create an AutoConfig/AutoMake package in an empty directory.
 
   - src/main.c : the source file 
```cpp    
~/amhello % cat src/main.c
#include <config.h>
#include <stdio.h>

int
main (void)
{
  puts ("Hello World!");
  puts ("This is " PACKAGE_STRING ".");
  return 0;
}
```
   - README: documentation for the package.
```    
~/amhello % cat README
This is a demonstration package for GNU Automake.
Type 'info Automake' to read the Automake manual.
```
   - Makefile.am and src/Makefile.am: contain Automake instructions for these two directories.
```
~/amhello % cat src/Makefile.am
bin_PROGRAMS = hello
hello_SOURCES = main.c
~/amhello % cat Makefile.am
SUBDIRS = src
dist_doc_DATA = README
```
   - configure.ac: Autoconf instructions to create the configure script.
```
~/amhello % cat configure.ac
AC_INIT([amhello], [1.0], [bug-automake@gnu.org])
AM_INIT_AUTOMAKE([-Wall -Werror foreign])
AC_PROG_CC
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([
 Makefile
 src/Makefile
])
AC_OUTPUT
```

   - Run the Autotools to instantiate the build system:
```
~/amhello % autoreconf --install
configure.ac: installing './install-sh'
configure.ac: installing './missing'
configure.ac: installing './compile'
src/Makefile.am: installing './depcomp' 
 ```

   - Config and build project
 ```
 ~/amhello % ./configure
 ~/amhello % make
…
~/amhello % src/hello
Hello World!
This is amhello 1.0.
~/amhello % make distcheck
…
=============================================
amhello-1.0 archives ready for distribution:
amhello-1.0.tar.gz
=============================================
```
 
