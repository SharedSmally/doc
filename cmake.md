## CMake:
- cmake
- ctest: testing
- cdash: collect test results
- cpack: packing

## [CMake document](https://cmake.org/cmake/help/latest/)
- [cmake] (https://cmake.org/cmake/help/latest/manual/cmake.1.html)
- [ctest] (https://cmake.org/cmake/help/latest/manual/ctest.1.html)
- [cpack] (https://cmake.org/cmake/help/latest/manual/cpack.1.html)
- [build commands] (https://cmake.org/cmake/help/latest/manual/cmake-buildsystem.7.html)
    - add_executable / add_library / add_custom_target:  create a new target
    - target_link_libraries
    - set_target_properties/get_target_property
    - set_property/get_property
    - set_source_files_properties/get_source_fileproperty
- [commands] (https://cmake.org/cmake/help/latest/manual/cmake-commands.7.html)

### steps
- Read CMakeCache.txt
- Read CMakeLists.txt 
- Write CMakeCache.txt
- Generate Makefile or project

#### Command-line-argument: -DXXXX=yyy
- in CMakeLists.txt: refereed as ${XXXX}

### Build process
The CMake build process is controlled by one or more CMakeLists.txt file in each directories that contain a series of command:
```
command (args ...) 
```
args is a white space seperated list of arguments. Argument with embedded white space should be double quoted.

CMake supports simple variable that can be either string of list of strings. Variables are referenced using a '''${VAR}''' syntax. Multiple argument can be grouped together into a list using the set command. To access system enviroment variable, the syntax $ENV{VAR} is used.

The simple CMakeLists.txt:
```
cmake_minimum_required(2.6)
project(Hello)

set (HELLO_SRCS Hello.c Filesn.c)

if (WIN32)
  set (HELLO_SRCS ${HELLO_SRCS} WinSupport.c)
else ()
  set (HELLO_SRCS ${HELLO_SRCS} UnixSupport.c)
endif()

add_executable(Hello ${HELLO_SRCS})
#add_executable(Hello Hello.c Filen.c)

# find tcl library
find_library( TCL_LIBRARY
   NAMES tcl tcl84 tcl83 tcl82 tcl80
   PATHS /usr/lib /usr/local/lib
)

if (RCL_LIBRARY)
   target_link_library(Hello ${TCL_LIBRARY})
endif()
```
To config, run
```
cmake -DVAR:TYPE=value --build <dir> options srcpath
make
```


