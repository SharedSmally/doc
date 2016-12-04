cxx
======

## Eclipse CXX (CDT)
 - Env setup:



 
 - CMake
    - CMake plugins: CMakeEclipse; CMakeEd; CMakeBuilder
    
    - Create a project with CMakeLists.txt; then run the command:
```
 % mkdir ctest 
 % cd ctest
 % vi  CMakeLists.txt 
cmake_minimum_required (VERSION 2.8.11)
project (HELLO)

add_subdirectory (libsrc)
add_subdirectory (src)

 %cmake -G"Eclipse CDT4 - Unix Makefiles" -DCMAKE_BUILD_TYPE=Debug ./ 

There are two Eclipse files in the tree:
 ~/.project
 ~/.cproject
The project can be imported to eclipse:  Menu File->Import>General->Existing projects into workspace: 
```
    
 
 - Maven + Nar
 
 - Gradle + cxx
 
 
 ## [AutoMake](https://www.gnu.org/software/automake/manual/automake.html), [AutoConfig](https://www.gnu.org/software/autoconf/manual/autoconf.html) and libtool:  
 - Commands: aclocal; autoreconf/autoconf; configure; autoscan; ifname;  Using CDT=>C++=>gnu autotools
 
 - Use _Autoconf_ to develop software package:
```
     source files --> [autoscan*] --> [configure.scan] --> configure.ac
     
     configure.ac --.
                    |   .------> autoconf* -----> configure
     [aclocal.m4] --+---+
                    |   `-----> [autoheader*] --> [config.h.in]
     [acsite.m4] ---'
     
     Makefile.in
```
 - Use _Automake_ to develop software package::
```
     [acinclude.m4] --.
                      |
     [local macros] --+--> aclocal* --> aclocal.m4
                      |
     configure.ac ----'
     
     configure.ac --.
                    +--> automake* --> Makefile.in
     Makefile.am ---'
```     
 - Configure and build a software package:
```
                            .-------------> [config.cache]
     configure* ------------+-------------> config.log
                            |
     [config.h.in] -.       v            .-> [config.h] -.
                    +--> config.status* -+               +--> make*
     Makefile.in ---'                    `-> Makefile ---'
     
  Can use _autoreconf_ to update configure Scripts.
```

 - Example to create a package using AutoConfig/AutoMake:
 
   - src/main.c : the source file 
```cpp    
% cat src/main.c

#include <config.h>
#include <stdio.h>
int main (void)
{
  puts ("Hello World!");
  puts ("This is " PACKAGE_STRING ".");
  return 0;
}
```
   - README: documentation for the package.
```    
% cat README
This is a demonstration package for GNU Automake.
Type 'info Automake' to read the Automake manual.
```
   - Makefile.am and src/Makefile.am: contain Automake instructions for these two directories.
```
% cat src/Makefile.am
bin_PROGRAMS = hello
hello_SOURCES = main.c

% cat Makefile.am
SUBDIRS = src
dist_doc_DATA = README
```
   - configure.ac: Autoconf instructions to create the configure script.
```
% cat configure.ac
AC_INIT([pkgtest], [1.0], [bug-automake@gnu.org])
AM_INIT_AUTOMAKE([-Wall -Werror foreign])
AC_PROG_CC
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([
 Makefile
 src/Makefile
])
AC_OUTPUT
```

   - Run the Autotools to create the package:
```
% autoreconf --install
configure.ac: installing './install-sh'
configure.ac: installing './missing'
configure.ac: installing './compile'
src/Makefile.am: installing './depcomp' 
 ```

   - Config and build project
```
 % ./configure
 % make
…
 % src/hello

 % make distcheck
…
=============================================
package is ready for distribution: xxxxxx-1.0.tar.gz
=============================================
```

   - Standard configure.ac Layout
  
```  
     Autoconf requirements
     AC_INIT(package, version, bug-report-address)
     information on the package
     checks for programs
     checks for libraries
     checks for header files
     checks for types
     checks for structures
     checks for compiler characteristics
     checks for library functions
     checks for system services
     AC_CONFIG_FILES([file...])
     AC_OUTPUT
```
