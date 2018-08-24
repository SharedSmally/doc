## [Entity](https://www.ibm.com/developerworks/library/x-entities/index.html)
Entities are references to data, the XML parser will either replace the entity reference with the entity's replacement text or the contents of an external document.

All entities (except parameter entities) start with an ampersand (&) and end with a semicolon (;) character. The XML standard defines five standard entities:
```
&apos; is an apostrophe: '
&amp; is an ampersand: &
&quot; is a quotation mark: "
&lt; is a less-than symbol: <
&gt; is a greater-than symbol: >
```

- Character entities
Character entities specify any Unicode character in decimal format (&#nnn;, nnn is the decimal value of the character) or hexadecimal format (&#xhhh;, hhh is the hexadecimal value of the character).
```
<!ENTITY ndash   "&#8211;"> <!-- en dash, U+2013 ISOpub -->
<!ENTITY mdash   "&#8212;"> <!-- em dash, U+2014 ISOpub -->
<!ENTITY lsquo   "&#8216;"> <!-- left single quotation mark, U+2018 ISOnum -->
<!ENTITY rsquo   "&#8217;"> <!-- right single quotation mark, U+2019 ISOnum -->
<!ENTITY sbquo   "&#8218;"> <!-- single low-9 quotation mark, U+201A NEW -->
<!ENTITY ldquo   "amp;“">   <!-- left double quotation mark, U+201C ISOnum -->
<!ENTITY rdquo   "&#8221;"> <!-- right double quotation mark, U+201D ISOnum -->
```

- Named entities (Internal entities)
Named entities are declared in either the DTD or the internal subset (part of the <!DOCTYPE> statement in document) and use them in the document as references. During the XML document parsing, the entity reference is replaced by its representation.
```
<!ENTITY c "Chris">
<!ENTITY ch "&c; Herborth">
```
Using &c; in a document will expand to Chris, and &ch; will expand to the full Chris Herborth.

- External entities
External entities represent the content of an external file:
```
<!ENTITY chap1 SYSTEM "chapter-1.xml">
<!ENTITY chap2 SYSTEM "chapter-2.xml">
<!ENTITY chap3 SYSTEM "chapter-3.xml">
```
Pull in the chapter content(the contents of these files are inserted into the XML document):
```
<?xml version="1.0" encoding="utf-8"?>
&chap1;
&chap2;
&chap3;
```

- Parameter entities
Parameter entities are only available inside the DTD and the internal subset of the document. They use the percent (%) symbol instead of the ampersand, and can be either named entities or external entities.
```
<!ENTITY % attrs "%coreattrs; %i18n; %events;">
<!ENTITY % coreattrs
 "id          ID             #IMPLIED
  class       CDATA          #IMPLIED
  style       %StyleSheet;   #IMPLIED
  title       %Text;         #IMPLIED"
  >
<!ENTITY % i18n
 "lang        %LanguageCode; #IMPLIED
  xml:lang    %LanguageCode; #IMPLIED
  dir         (ltr|rtl)      #IMPLIED"
  >
```

## Define Engities
 Entities are defined using the ENTITY declaration, either as part of an external DTD (st.ent):
```
 <!-- Named entity for site name: -->
<!ENTITY dw "developerWorks">
 
<!-- External entity for re-use: -->
<!ENTITY bio SYSTEM "dw-author-bio.xml">
 
<!-- Parameter entity for use in DTD -->
<!ENTITY % English "en-US|en-CA|en-UK">
```
 
 or as part of the document's internal subset:
 
```
<?xml version="1.0" encoding="UTF-8"?>
<!DOCTYPE html 
    PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN" 
    "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd"
[
    <!ENTITY test-entity "This <em>is</em> an entity.">
]>
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
    <meta http-equiv="Content-Type" content="application/xhtml+xml;charset=utf-8"/>
    <title>Entities in XML</title>
</head>
<body>
    <h1>Entities in XML</h1>
    <p>&test-entity;</p>
    <p>You can use it anywhere you'd use a standard XHTML entity:</p>
    <pre>&test-entity;</pre>
</body>
</html>
```
 
 ## Example1:
 - Define Entities: style.ent
```
 <!-- Tab -->
<!ENTITY tab  "<xsl:text xmlns:xsl='http://www.w3.org/1999/XSL/Transform'>    </xsl:text>">
<!-- Two Tabs -->
<!ENTITY tab2 "<xsl:text xmlns:xsl='http://www.w3.org/1999/XSL/Transform'>        </xsl:text>">
<!-- Three Tabs -->
<!ENTITY tab3 "<xsl:text xmlns:xsl='http://www.w3.org/1999/XSL/Transform'>            </xsl:text>">
<!-- Four Tabs -->
<!ENTITY tab4 "<xsl:text xmlns:xsl='http://www.w3.org/1999/XSL/Transform'>                </xsl:text>">
<!-- New Line -->
<!ENTITY n "<xsl:text xmlns:xsl='http://www.w3.org/1999/XSL/Transform'>
</xsl:text>">
<!-- Two new Lines -->
<!ENTITY n2 "<xsl:text xmlns:xsl='http://www.w3.org/1999/XSL/Transform'>

</xsl:text>">
<!-- Three new Lines -->
<!ENTITY n3 "<xsl:text xmlns:xsl='http://www.w3.org/1999/XSL/Transform'>

</xsl:text>">
<!-- Space -->
<!ENTITY space "<xsl:text xmlns:xsl='http://www.w3.org/1999/XSL/Transform'> </xsl:text>">
```
 
 - Include ent file
```
<!DOCTYPE xsl:stylesheet [
     <!ENTITY % stylesheet_extensions SYSTEM './stylesheet.ent' >
     %stylesheet_extensions;
]>

<xsl:stylesheet version="1.0"
    xmlns:xsl="http://www.w3.org/1999/XSL/Transform" >

<xsl:template match="TEST1">
    &tab;<TEST1>
    ...
 </xsl>
 ```
 
 ## Example2: with XInclude to reference XML nodes
 ```
<!DOCTYPE Profile SYSTEM "Profile.dtd" [
        <!ENTITY env   "env.xml">
        <!ENTITY db    "db.xml">
        <!ENTITY groups   "groups.xml">
        <!ENTITY configs  "configs.xml">

        <!ATTLIST DBConfigs
            id  NMTOKEN #REQUIRED
        >
        <!ATTLIST GroupConfigs
            id  NMTOKEN #REQUIRED
        >
        <!ATTLIST AppData
            id  NMTOKEN #REQUIRED
        >
]>

<Profile xmlns:xi="http://www.w3.org/2001/XInclude"
    name="appProfile"
    multicast="&amp;mcastaddr;"
    default-profile="&amp;TAG;/data/default.xml"
>
   <desc>desc</desc>

   <!-- get envs -->
   <xi:include href="&env;" xpointer="xpointer(/env/host)"/>

    <!-- get groups info  -->
    <xi:include href="&groups;" xpointer="xpointer(/groups/config)"/>
    
    <!-- get specific info -->
    <xi:include href="&configs;" xpointer="xpointer(id('test')/*)"/>
 ```
