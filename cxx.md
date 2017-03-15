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

## cxx simulating of [multi-index](http://www.codesynthesis.com/~boris/blog/2012/09/11/emulating-boost-multi-index-with-std-containers/)
- multi-index
```
struct person
{
  person (const std::string& email_,
          const std::string& name_,
          unsigned short age_)
     : email(email_),name(name_),age(age_)
          {};

  std::string email;
  std::string name;
  unsigned short age;
};

template <typename T>
struct key
{
  mutable const T* p;

  key (const T* v = 0): p (v) {}
  bool operator< (const key& x) const {return *p < *x.p;}
};

template <typename I>
struct map_iterator_adapter: I
{
  typedef const typename I::value_type::second_type value_type;
  typedef value_type* pointer;
  typedef value_type& reference;

  map_iterator_adapter () {}
  map_iterator_adapter (I i): I (i) {}

  reference operator* () const {return I::operator* ().second;}
  pointer operator-> () const {return &I::operator-> ()->second;}
};

struct person_set
{
  typedef std::map<key<std::string>, person> email_map;
  typedef map_iterator_adapter<email_map::const_iterator> iterator;
  typedef std::map<key<std::string>, iterator> name_map;


  std::pair<iterator, bool>
  insert (const person& v)
  {
    // First check that have any collisions in the secondary indexes.
    {
      auto i (name_map_.find (&v.name));
      if (i != name_map_.end ())
        return std::make_pair (i->second, false);
    }

    auto r (email_map_.insert (email_map::value_type (&v.email, v)));
    iterator i (r.first);

    if (r.second)
    {
      r.first->first.p = &i->email;
      name_map_.insert (name_map::value_type (&i->name, i));
    }

    return std::make_pair (i, r.second);
  }

  iterator
  find_email (const std::string& email) const
  {
    return email_map_.find (&email);
  }

  iterator
  find_name (const std::string& name) const
  {
    auto i (name_map_.find (&name));
    return i != name_map_.end () ? i->second : end ();
  }

  iterator begin () const {return email_map_.begin ();}
  iterator end () const {return email_map_.end ();}

private:
  email_map email_map_;
  name_map name_map_;
};
int main()
{
        person_set s;
        s.insert (person ("john@doe.com", "John Doe", 29));
        s.insert (person ("jane@doe.com", "Jane Doe", 27));
        auto i (s.find_email ("john@doe.com"));
        cout << "Find_by_email: email=" << i->email << "; name=" << i->name << "; age=" << i->age << endl;

        auto j (s.find_name ("Jane Doe"));
        cout << "Find_by_name: email=" << j->email << "; name=" << j->name << "; age=" << j->age << endl;
}
```

- Use tuple as the composite key
```
#include <map>
#include <tuple>
#include <string>
#include <iostream>
typedef std::map<std::tuple<int, std::string>, double>  MyMap;
int main()
{
        MyMap values;
        values.insert( std::make_pair(std::make_tuple(2, "world"), 53.7 ));
        values.insert( std::make_pair(std::make_tuple(1, "www"), 100.3 ));
        values.insert( std::make_pair(std::make_tuple(1, "hello"), 13.3 ));

        cout << "tuple size=" << std::tuple_size<MyMap::key_type>::value << endl;

        for (auto it : values)
        {
                cout << "key1=" << std::get<0>(it.first) << "; key2=" << std::get<1>(it.first) << "; value=" << it.second << endl;
        }
}
```
