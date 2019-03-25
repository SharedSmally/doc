## Simple Tips

- Find files with pattern
```
files=`find . \( -name "*.h" -o -name "*.cc" \) -exec grep -q "Tensor/System/EndianCopy.h" {} \; -print`
for file in $files; do
   echo $file
   /usr/local/bin/p4 edit $file
   perl -i -pe "s|Tensor/System/EndianCopy.h|Tensor/XMF/EndianCopy.h|" $file
done
```

- Generate executable including all libraries: use -static or -Wl,-Bstatic:
     - lc: standard c libary, link to libc.so.6 (glibc: install glibc-devel or libc6-dev package)     
     - lm:  math library
     - lstdc++: standard c++ libary
     - -static-libgcc -static-libstdc++: static version of c and stdc++ libraries

- link libapplejuice statically, but not liborangejuice:
 ```
gcc object1.o object2.o -Wl,-Bstatic -lapplejuice -Wl,-Bdynamic -lorangejuice -o binar
```

### [ glibc ](https://www.gnu.org/software/libc/manual/html_mono/libc.html) headers
```
errno.h
ctype.h
string.h
stdlib.h
stdio.h
unistd.h
dirent.h
regex.h
wchar.h
printf.h
fcntl.h
utime.h
time.h
setjmp.h
signal.h.
argp.h
grp.h
pwd.h
execinfo.h
threads.h
assert.h
stdarg.h
stddef.h
limits.h
float.h
crypt.h
math.h
search.h
utmp.h
utmpx.h
wordexp.h
termios.h
obstack.h
libintl.h
ucontext.h 
sys/file.h
sys/types.h
sys/param.h
sys/stat.h
sys/time.h
sys/times.h
sys/utsname.h
sys/random.h
sys/socket.h
net/if.h
sys/un.h
sys/wait.h
netinet/in.h
arpa/inet.h
```

