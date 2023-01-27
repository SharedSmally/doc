# makefile
- [reference](https://www.gnu.org/software/make/manual/)

## define function
```
all:
    $(call generate_file,John Doe,101)
    
define generate_file
    sed 's/{NAME}/$(1)/' greetings.tmpl >$(2).txt
endef    
```

## for loop
```
target:
    for number in 1 2 3 4 ; do \
        echo $$number ; \
    done
    
xxx:
    for i in `seq 1 4`; do ./a.out $$i; done;    
```
## while loop
```
target:
    number=1 ; while [[ $$number -le 10 ]] ; do \
        echo $$number ; \
        ((number = number + 1)) ; \
    done
```

## special targets
```
.PHONY: all
.SECONDARY:  #keep intermediate files
```

## [Common Functions](https://www.gnu.org/software/make/manual/html_node/Functions.html)
```
$(function arguments)
```
- [text functions](https://www.gnu.org/software/make/manual/html_node/Text-Functions.html)
```
$(subst from,to,text)   # $(subst ee,EE,feet on the street) =>'fEEt on the strEEt'
$(patsubst pattern,replacement,text)
$(strip string)
$(findstring find,in)
$(filter pattern…,text)
$(filter-out pattern…,text)
$(sort list)
$(word n,text)
$(wordlist s,e,text)
$(words text)
$(firstword names…)
$(lastword names…)
```
- [Filename functions](https://www.gnu.org/software/make/manual/html_node/File-Name-Functions.html)
```
$(dir names…)
$(notdir names…)
$(suffix names…)
$(basename names…)
$(addsuffix suffix,names…)
$(addprefix prefix,names…)
$(join list1,list2)
$(wildcard pattern)
$(realpath names…)
$(abspath names…)
```
- [Condition functions](https://www.gnu.org/software/make/manual/html_node/Conditional-Functions.html)
```
$(if condition,then-part[,else-part])
$(or condition1[,condition2[,condition3…]])
$(and condition1[,condition2[,condition3…]])
$(intcmp lhs,rhs[,lt-part[,eq-part[,gt-part]]])
$(let var [var ...],[list],text)
$(foreach var,list,text)   #dirs:=a b c d;  files:=$(foreach dir,$(dirs),$(wildcard $(dir)/*))
$(file op filename[,text])  #read: >,>> or write (<) to a file
$(call variable,param,param,…)  # reverse = $(2) $(1); foo = $(call reverse,a,b)
$(value variable)   #
```
- [Logging functions](https://www.gnu.org/software/make/manual/html_node/Make-Control-Functions.html)
```
$(error text…)
$(warning text…)
$(info text…)
files := $(shell echo *.c)
```

## [Automatic Variables](https://www.gnu.org/software/make/manual/html_node/Automatic-Variables.html)
- $@: The file name of the target of the rule.
- $%: The target member name, when the target is an archive member. 
- $<: The name of the first prerequisite. 
- $?: The names of all the prerequisites that are newer than the target, with spaces between them. 
- $^: The names of all the prerequisites, with spaces between them. 
- $+: Similar to $^, with duplicated in the order
- $|: The names of all the order-only prerequisites, with spaces between them.
- $\*: The stem for an implicit rule matches

- ‘$(@D)’: The directory part of the file name of the target, with the trailing slash removed. 
- ‘$(@F)’: The file-within-directory part of the file name of the target. 
- ‘$(\*D)’/‘$(\*F)’:  The directory part and the file-within-directory part of the stem; dir and foo in this example.
- ‘$(%D)’/‘$(%F)’:  The directory part and the file-within-directory part of the target archive member name. 
- ‘$(<D)’/‘$(<F)’: The directory part and the file-within-directory part of the first prerequisite.
- ‘$(^D)’/‘$(^F)’:  Lists of the directory parts and the file-within-directory parts of all prerequisites.
- ‘$(+D)’/‘$(+F)’:  Lists of the directory parts and the file-within-directory parts of all prerequisites, with duplicatted ones
- ‘$(?D)’/‘$(?F)’:  Lists of the directory parts and the file-within-directory parts of all prerequisites that are newer than the target. 
    
    
