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
 link libapplejuice statically, but not liborangejuice:
 ```
gcc object1.o object2.o -Wl,-Bstatic -lapplejuice -Wl,-Bdynamic -lorangejuice -o binar
```

