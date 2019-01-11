## Merge multiple xml files into one using Xinclude:
```
<book xmlns:xi="http://www.w3.org/2001/XInclude">
  <title>Merge multiple xml files</title>
  <xi:include href="file1.xml"/>
  <xi:include href="file2.xml"/>
  <xi:include href="file3.xml"/>
</book>
```

## Merge multiple xml files into one using entity:
logfile.xml:
```
<?xml version="1.0"?>
<!DOCTYPE logfile [
<!ENTITY events    
 SYSTEM "events.txt">
]>
<logfile>
&events;
</logfile>
```
events.txt:
```
<event>
    <item1>item1</item1>
    <item2>item2</item2>
</event>
```
