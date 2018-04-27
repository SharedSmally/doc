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

