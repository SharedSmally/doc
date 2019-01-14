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
<!ENTITY events SYSTEM "events.txt">
]>
<logfile>
&events;
</logfile>
```
```
<?xml version="1.0"?>
<!DOCTYPE novel SYSTEM "/dtd/novel.dtd" [
<!ENTITY chap1 SYSTEM "mydocs/chapter1.xml">
<!ENTITY chap2 SYSTEM "mydocs/chapter2.xml">
<!ENTITY chap3 SYSTEM "mydocs/chapter3.xml">
<!ENTITY chap4 SYSTEM "mydocs/chapter4.xml">
<!ENTITY chap5 SYSTEM "mydocs/chapter5.xml">
]>
<novel>
  <header> ...  </header>
&chap1; 
&chap2; 
&chap3; 
&chap4; 
&chap5; 
</novel>
```
events.txt:
```
<event>
    <item1>item1</item1>
    <item2>item2</item2>
</event>
```

Using xinclude:
```
<?xml version="1.0"?>
<article xmlns="http://docbook.org/ns/docbook"
      xmlns:xi="http://www.w3.org/2001/XInclude">
   <info>
     <xi:include href="metadata.xml" parse="xml"  xpointer="title"/>
   </info>
   <sect1>
      ...
   </sect1>
</article>
```
