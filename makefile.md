[ Makefile ](https://www.gnu.org/software/make/manual/make.html)
======

## Commands:
- List Targets: 

make -qp | awk -F':' '/^[a-zA-Z0-9][^$#\/\t=]*:([^=]|$)/ {split($1,A,/ /);for(i in A)print A[i]}'

## Script:
 - statements concated with * \ *,  and each one ends with * ; *
 - if-else-endif
 ```
   if [ ! -f $file ]; then \ 
      echo "file ", $file, " not exists"; \ 
   fi 
   
   @if [ "$(REL) " = " " ] ; then \
	echo error:: REL not specified, aborting ; exit 1 ; \
   fi
   
ifeq ($(TARGET_CPU),x86)
  TARGET_CPU_IS_X86 := 1
else ifeq ($(TARGET_CPU),x86_64)
  TARGET_CPU_IS_X86 := 1
else
  TARGET_CPU_IS_X86 := 0
endif

```   
 - for-loop
 ``` 
for var in ${vars}; do \ 
   echo "variable:" $${usher}; \ 
done

LIST = pre1 pre2 pre3 pre4 pre5 pre6 pre7 pre8 pre9 pre10
START = 0
input = somename
file_name = whatever

some_target:
    for prefix in $(LIST); do \
        if test "$(input)" = $$prefix; then \
            START=1; \
        fi; \
        if test "$(START)" = 1; then \
            if test -f  $$prefix$(file_name); then \
                <do_A>; \
            else \
                <do_B>; \
            fi; \
        fi; \
    done
  ```
  
 - foreach
 ```
dirs := a b c d
files := $(foreach dir,$(dirs),$(wildcard $(dir)/*))

$(foreach dir,$(shell ls),echo $(dir))
 ```
 - function
 
 Here is a simple Makefile with a custom function:
```
define generate_file
    sed 's/{NAME}/$(1)/' greetings.tmpl >$(2).txt
endef

all:
    $(call generate_file,John Doe,101)
    $(call generate_file,Peter Pan,102)

```
Call function:  In function the first parameter becomes $(1), the second $(2), etc.
```
$(call <name_of_function>[, <param>][,<param>][,...])
```

 - target
 ``` 
  target … : prerequisites …
        recipe
        …
        …
 ```
## Built-in Functions:
 - Run command:
```
contents := $(shell cat foo)
files := $(shell echo *.c)
```

## Tips:
- Keep the intermediate file, need to use the special target .PRECIOUS:
```
.PRECIOUS: fact_test_without_proxies.c fact_test_main.c fact_test_without_proxies.o
.PRECIOUS: %.c %.o
```
Its only effect is that these files will not be deleted if Make is killed or interrupted.

- [target-specific variable values ](https://www.gnu.org/software/make/manual/html_node/Target_002dspecific.html)

Variable values are usually global except automatic variables and target-specific variable values. The latter feature allows you to define different values for the same variable, based on the target that make is currently building:

```
target … : variable-assignment
```
       -  Target-specific variable assignments can be prefixed with any or all of the special keywords *export, override, or private*.
       -  Multiple target values create a target-specific variable value for each member of the target list individually.
       -  The variable-assignment can be any valid form of assignment; recursive (‘=’), simple (‘:=’ or ‘::=’), appending (‘+=’), or conditional (‘?=’).

## Recursive call makefile
```
DIRS = dev ui utils doc
# the sets of directories to do various things in
BUILDDIRS = $(DIRS:%=build-%)
INSTALLDIRS = $(DIRS:%=install-%)
CLEANDIRS = $(DIRS:%=clean-%)
TESTDIRS = $(DIRS:%=test-%)

all: subdirs

.PHONY: subdirs $(DIRS)
subdirs:$(DIRS)
$(DIRS): 
    $(MAKE) -C $@

.PHONY: build $(BUILDDIRS)
build:$(BUILDDIRS)
$(BUILDDIRS):
   $(MAKE) -C $(@:build-%=%) build

install: $(INSTALLDIRS) all
$(INSTALLDIRS):
	  $(MAKE) -C $(@:install-%=%) install

test: $(TESTDIRS) all
$(TESTDIRS): 
	  $(MAKE) -C $(@:test-%=%) test

clean: $(CLEANDIRS)
$(CLEANDIRS): 
	  $(MAKE) -C $(@:clean-%=%) clean

.PHONY: subdirs $(INSTALLDIRS)
.PHONY: subdirs $(TESTDIRS)
.PHONY: subdirs $(CLEANDIRS)
.PHONY: all install clean test
```
