 xslt
======
 
## Transfers
 - [xalan](https://xml.apache.org/xalan-j/) - xslt 1.0; based in [xerces] (http://xerces.apache.org/xerces2-j/index.html)
   
   export XALAN_HOME=/home/xxx/xalan

   java -cp ${XALAN_HOME}/xalan.jar:${XALAN_HOME}/serializer.jar:${XALAN_HOME}/xercesImpl.jar:${XALAN_HOME}/xml-apis.jar \
     org.apache.xalan.xslt.Process -xsl $1 -in $2 -out $3

 - [Saxon] (http://saxon.sourceforge.net/) - xslt 2.0; Home Edition

   export SAXON_HOME=/home/xxx/saxon

   java -cp ${SAXON_HOME}/saxon9-xqj.jar:${SAXON_HOME}/saxon9he.jar \
     net.sf.saxon.Transform -xsl:$1 -s:$2 -o:$3

## Components:  [Reference](http://www.w3schools.com/xml/xsl_elementref.asp)
- XSLT root
```xml
<xsl:stylesheet
  id? = id
  version = decimal
  default-mode? = eqname | "#unnamed"
  default-validation? = "preserve" | "strip"
  input-type-annotations? = "preserve" | "strip" | "unspecified"
  default-collation? = uris
  extension-element-prefixes? = prefixes
  exclude-result-prefixes? = prefixes
  expand-text? = boolean
  use-when? = expression
  xpath-default-namespace? = uri >
  <!-- Content: (declarations) -->
</xsl:stylesheet>
```
- Import
```
<xsl:import  href = uri />
<xsl:include  href = uri />
```
    - xsl:include: include the referenced xsl document (b.xsl) within the referencing document (a.xsl).  Cannot have two templates with the same matching signature: name, or (match and/or mode).

    - xsl:importans: if b.xsl "imports" a.xsl then b.xsl is--in effect--sub-classing a.xsl. If a.xsl has a template named "X" and b.xsl has a template named "X", then xslt processor will use the call the "X" template from the b.xsl document.  

    - importing a style sheet is the same as including it except that definitions and template rules in the importing style sheet take precedence over those in the imported style sheet.

- template
```xml
<xsl:template
  match? = pattern
  name? = eqname
  priority? = decimal
  mode? = tokens
  as? = sequence-type
  visibility? = "public" | "private" | "final" | "abstract" >
  <!-- Content: (xsl:context-item?, xsl:param*, sequence-constructor) -->
</xsl:template>
```
- call-template
```xml
<xsl:call-template
  name = eqname >
  <!-- Content: xsl:with-param* -->
</xsl:call-template>
```
- apply-templates
```xml
<xsl:apply-templates
  select? = expression
  mode? = token >
  <!-- Content: (xsl:sort | xsl:with-param)* -->
</xsl:apply-templates>
```
- Control
       - if
```xml
<xsl:if
  test = expression >
  <!-- Content: sequence-constructor -->
</xsl:if>
```
       - conditional Processing
```xml
<xsl:choose>
  <!-- Content: (xsl:when+, xsl:otherwise?) -->
</xsl:choose>

<xsl:when
  test = expression >
  <!-- Content: sequence-constructor -->
</xsl:when>

<xsl:otherwise>
  <!-- Content: sequence-constructor -->
</xsl:otherwise>
```
       - Repeat
```xml
<xsl:for-each
  select = expression >
  <!-- Content: (xsl:sort*, sequence-constructor) -->
</xsl:for-each>
```

- Variable and Parameter
```
<xsl:variable
  name = eqname
  select? = expression
  as? = sequence-type
  static? = boolean
  visibility? = "public" | "private" | "final" | "abstract" >
  <!-- Content: sequence-constructor -->
</xsl:variable>

<xsl:param
  name = eqname
  select? = expression
  as? = sequence-type
  required? = boolean
  tunnel? = boolean
  static? = boolean >
  <!-- Content: sequence-constructor -->
</xsl:param>

<xsl:with-param
  name = eqname
  select? = expression
  as? = sequence-type
  tunnel? = boolean >
  <!-- Content: sequence-constructor -->
</xsl:with-param>
```
- Function
```
<xsl:function
  name = eqname
  as? = sequence-type
  visibility? = "public" | "private" | "final" | "abstract"
  streamability? = "unclassified" | "absorbing" | "inspection" | "filter" | "shallow-descent" | "deep-descent" | "ascent" | eqname
  override-extension-function? = boolean
  [override]? = boolean
  new-each-time? = "yes" | "true" | "1" | "no" | "false" | "0" | "maybe"
  cache? = boolean >
  <!-- Content: (xsl:param*, sequence-constructor) -->
</xsl:function>
```

- XML node
```xml
Document Node
<xsl:document
  validation? = "strict" | "lax" | "preserve" | "strip"
  type? = eqname >
  <!-- Content: sequence-constructor -->
</xsl:document>
Text Node
<xsl:text
  [disable-output-escaping]? = boolean >
  <!-- Content: #PCDATA -->
</xsl:text>
Processing Instructions
<xsl:processing-instruction
  name = { ncname }
  select? = expression >
  <!-- Content: sequence-constructor -->
</xsl:processing-instruction>
Namespace Node
<xsl:namespace
  name = { ncname }
  select? = expression >
  <!-- Content: sequence-constructor -->
</xsl:namespace>
Deep Copy of Nodes
<xsl:copy-of  
  select = expression
  copy-accumulators? = boolean
  copy-namespaces? = boolean
  type? = eqname
  validation? = "strict" | "lax" | "preserve" | "strip" />
Shadow Copy of Nodes
<xsl:copy
  select? = expression
  copy-namespaces? = boolean
  inherit-namespaces? = boolean
  use-attribute-sets? = eqnames
  type? = eqname
  validation? = "strict" | "lax" | "preserve" | "strip" >
  <!-- Content: sequence-constructor -->
</xsl:copy>

Sequence
<xsl:sequence
  select? = expression >
  <!-- Content: sequence-constructor -->
</xsl:sequence>

```

- Output
```
<xsl:value-of
  select? = expression
  separator? = { string }
  [disable-output-escaping]? = boolean >
  <!-- Content: sequence-constructor -->
</xsl:value-of>
```
- Multiple Document
```xml
<xsl:result-document
  format? = { eqname }
  href? = { uri }
  validation? = "strict" | "lax" | "preserve" | "strip"
  type? = eqname
  method? = "xml" | "html" | "xhtml" | "text" | "json" | "adaptive" | eqname
  allow-duplicate-names? = { boolean }
  build-tree? = { boolean }
  byte-order-mark? = { boolean }
  cdata-section-elements? = { eqnames }
  doctype-public? = { string }
  doctype-system? = { string }
  encoding? = { string }
  escape-uri-attributes? = { boolean }
  html-version? = { decimal }
  include-content-type? = { boolean }
  indent? = { boolean }
  item-separator? = { string }
  json-node-output-method? = "xml" | "html" | "xhtml" | "text" | eqname
  media-type? = { string }
  normalization-form? = { "NFC" | "NFD" | "NFKC" | "NFKD" | "fully-normalized" | "none" | nmtoken }
  omit-xml-declaration? = { boolean }
  parameter-document? = { uri }
  standalone? = { boolean | "omit" }
  suppress-indentation? = { eqnames }
  undeclare-prefixes? = { boolean }
  use-character-maps? = eqnames
  output-version? = { nmtoken } >
  <!-- Content: sequence-constructor -->
</xsl:result-document>
```
- Sort
```xml
<xsl:sort
  select? = expression
  lang? = { language }
  order? = { "ascending" | "descending" }
  collation? = { uri }
  stable? = { boolean }
  case-order? = { "upper-first" | "lower-first" }
  data-type? = { "text" | "number" | eqname } >
  <!-- Content: sequence-constructor -->
</xsl:sort>

<xsl:perform-sort
  select? = expression >
  <!-- Content: (xsl:sort+, sequence-constructor) -->
</xsl:perform-sort>
```
## xslt
 - [xslt 1.0](https://www.w3.org/TR/xslt)
 - [xslt 2.0](https://www.w3.org/TR/xslt20/)
 - New features in xslt 2.0
  - Conversion of result tree fragments to node-sets
  - Multiple output documents
  - Built-in support for grouping
  - User-defined functions in XSLT
  - Define a default namespace 
  - Sorting specifications
  - Read external files as unparsed text

## Tips
- methods:
   - method="xml"
   - method="html"
- [xslt functions] (http://www.w3schools.com/xml/xsl_functions.asp)
- Counter
```
<xsl:for-each select="for $i in 1 to $length return $i">...</xsl:for-each>
  <xsl:for-each select="1 to $cnt">
    ... do something ...
  </xsl:for-each>
```
- Multiple Outputs
```
<xsl:template match="/">
  <xsl:for-each select="elem/file">
    <xsl:result-document method="xml" href="file_{@id}-output.xml">
      <xsl:copy-of select="."/>
    </xsl:result-document>
  </xsl:for-each>
</xsl:template> 
```

### [XSLT functions](http://www.w3schools.com/xml/xsl_functions.asp)

- Accessor Functions

        - fn:node\-name(node)	        
        - fn:nilled(node)		      
        - fn:data(item.item,...)	        
        - fn:base\-uri()        
        - fn:base\-uri(node)	        
        - fn:document\-uri(node)	

- Error and Trace Functions
        
        - fn:error()        
        - fn:error(error)        
        - fn:error(error,description)        
        - fn:error(error,description,error\-object)	        
        - fn:trace(value,label)	

- Functions on Numeric Values

        - fn:number(arg)	        
        - fn:abs(num)	        
        - fn:ceiling(num)	        
        - fn:floor(num)	        
        - fn:round(num)	        
        - fn:round-half\-to\-even()	

- Functions on Strings

        - fn:string(arg)	        
        - fn:codepoints\-to\-string((int,int,...))        
        - fn:string\-to\-codepoints(string)        
        - fn:codepoint\-equal(comp1,comp2)        
        - fn:compare(comp1,comp2)        
        - fn:compare(comp1,comp2,collation)        
        - fn:concat(string,string,...)	        
        - fn:string-join((string,string,...),sep)	        
        - fn:substring(string,start,len)                
        - fn:substring(string,start)	        
        - fn:string-length(string)        
        - fn:string-length()	      
        - fn:normalize\-space(string)        
        - fn:normalize\-space()	        
        - fn:normalize\-unicode()	         
        - fn:upper\-case(string)	        
        - fn:lower\-case(string)	        
        - fn:translate(string1,string2,string3)	        
        - fn:escape\-uri(stringURI,esc-res)	        
        - fn:contains(string1,string2)	        
        - fn:starts\-with(string1,string2)	        
        - fn:ends\-with(string1,string2)	        
        - fn:substring\-before(string1,string2)	        
        - fn:substring\-after(string1,string2)	        
        - fn:matches(string,pattern)	        
        - fn:replace(string,pattern,replace)	        
        - fn:tokenize(string,pattern)        
        - fn:resolve\-uri(relative,base)	 

- Functions on Boolean Values

        - fn:boolean(arg)	        
        - fn:not(arg)	        
        - fn:true()	        
        - fn:false()	

- Functions on Durations, Dates and Times

        - fn:dateTime(date,time)	        
        - fn:years\-from\-duration(datetimedur)	        
        - fn:months\-from-duration(datetimedur)	        
        - fn:days\-from-duration(datetimedur)	        
        - fn:hours\-from-duration(datetimedur)        
        - fn:minutes\-from-duration(datetimedur)	        
        - fn:seconds\-from-duration(datetimedur)	        
        - fn:year\-from-dateTime(datetime)	        
        - fn:month\-from-dateTime(datetime)        
        - fn:day\-from-dateTime(datetime)	        
        - fn:hours\-from-dateTime(datetime)        
        - fn:minutes\-from-dateTime(datetime)        
        - fn:seconds\-from-dateTime(datetime)        
        - fn:timezone\-from-dateTime(datetime)        
        - fn:year\-from\-date(date)	        
        - fn:month\-from\-date(date)        
        - fn:day\-from\-date(date)	        
        - fn:timezone\-from\-date(date)        
        - fn:hours\-from\-time(time)        
        - fn:minutes\-from\-time(time)        
        - fn:seconds\-from\-time(time)        
        - fn:timezone\-from\-time(time)        
        - fn:adjust\-dateTime\-to\-timezone(datetime,timezone)        
        - fn:adjust\-date\-to\-timezone(date,timezone)	        
        - fn:adjust\-time\-to\-timezone(time,timezone)	
        
- Functions Related to QNames

        - fn:QName()	         
        - fn:local\-name\-from-QName()	         
        - fn:namespace\-uri\-from-QName()	         
        - fn:namespace\-uri\-for\-prefix()	        
        - fn:in\-scope\-prefixes()	         
        - fn:resolve\-QName()	 

- Functions on Nodes

        - fn:name()        
        - fn:name(nodeset)	        
        - fn:local\-name()        
        - fn:local\-name(nodeset)        
        - fn:namespace\-uri()        
        - fn:namespace\-uri(nodeset)	        
        - fn:lang(lang)	        
        - fn:root()        
        - fn:root(node)	
        
- Functions on Sequences

        - fn:index\-of((item,item,...),searchitem)	        
        - fn:remove((item,item,...),position)	        
        - fn:empty(item,item,...)	        
        - fn:exists(item,item,...)        
        - fn:distinct\-values((item,item,...),collation)	        
        - fn:insert\-before((item,item,...),pos,inserts)	        
        - fn:reverse((item,item,...))	                
        - fn:subsequence((item,item,...),start,len)	        
        - fn:unordered((item,item,...))	

- Functions That Test the Cardinality of Sequences

        - fn:zero\-or\-one(item,item,...)        
        - fn:one\-or\-more(item,item,...)        
        - fn:exactly\-one(item,item,...)

- Equals, Union, Intersection and Except

        - fn:deep\-equal(param1,param2,collation)	

- Aggregate Functions

        - fn:count((item,item,...))	        
        - fn:avg((arg,arg,...))	        
        - fn:max((arg,arg,...))	        
        - fn:min((arg,arg,...))	        
        - fn:sum(arg,arg,...)	

- Functions that Generate Sequences

        - fn:id((string,string,...),node)	        
        - fn:idref((string,string,...),node)        
        - fn:doc(URI)	         
        - fn:doc\-available(URI)	        
        - fn:collection()        
        - fn:collection(string)	 

- Context Functions

        - fn:position()	        
        - fn:last()	        
        - fn:current\-dateTime()        
        - fn:current\-date()	        
        - fn:current\-time()	        
        - fn:implicit\-timezone()	        
        - fn:default\-collation()	        
        - fn:static\-base\-uri()	

- XSLT Functions

  - current()	       
  - document()	
  - element\-available()	
  - format\-number()	
  - function\-available()	
  - generate\-id()
  - key()	
  - system\-property()	
  - unparsed\-entity\-uri()	


## Pass parameters from command line:
At the top level of a (2.0) stylesheet
   <xsl:param name="x" as="xs:integer" required="yes"/>

and then invoke Saxon as
   java -jar saxon8.jar source.xml style.xsl x=17

and then access the variable $x in any XPath expression.

## Sample
```
<?xml version="1.0"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

<xsl:template match="/">
  <html>
  <body>
    <h2>My CD Collection</h2>
    <table border="1">
      <tr bgcolor="#9acd32">
        <th>Title</th>
        <th>Artist</th>
      </tr>
      <xsl:for-each select="catalog/cd">
        <tr>
          <td><xsl:value-of select="title"/></td>
          <td><xsl:value-of select="artist"/></td>
        </tr>
      </xsl:for-each>
    </table>
  </body>
  </html>
</xsl:template>

</xsl:stylesheet>
```
