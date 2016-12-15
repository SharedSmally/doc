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
        - fn:node-name(node)	
        - fn:nilled(node)		
        - fn:data(item.item,...)	
        - fn:base-uri()
        - fn:base-uri(node)	
        - fn:document-uri(node)	
 - Error and Trace Functions
        - fn:error()
        - fn:error(error)
        - fn:error(error,description)
        - fn:error(error,description,error-object)	
        - fn:trace(value,label)	
 - Functions on Numeric Values
        - fn:number(arg)	
        - fn:abs(num)	
        - fn:ceiling(num)	
        - fn:floor(num)	
        - fn:round(num)	
        - fn:round-half-to-even()	
 - Functions on Strings
        - fn:string(arg)	
        - fn:codepoints-to-string((int,int,...))
        - fn:string-to-codepoints(string)
        - fn:codepoint-equal(comp1,comp2)
        - fn:compare(comp1,comp2)
        - fn:compare(comp1,comp2,collation)
        - fn:concat(string,string,...)	
        - fn:string-join((string,string,...),sep)	
        - fn:substring(string,start,len)
        - fn:substring(string,start)	
        - fn:string-length(string)
        - fn:string-length()	
        - fn:normalize-space(string)
        - fn:normalize-space()	
        - fn:normalize-unicode()	 
        - fn:upper-case(string)	
        - fn:lower-case(string)	
        - fn:translate(string1,string2,string3)	
        - fn:escape-uri(stringURI,esc-res)	
        - fn:contains(string1,string2)	
        - fn:starts-with(string1,string2)	
        - fn:ends-with(string1,string2)	
        - fn:substring-before(string1,string2)	
        - fn:substring-after(string1,string2)	
        - fn:matches(string,pattern)	
        - fn:replace(string,pattern,replace)	
        - fn:tokenize(string,pattern)
        - fn:resolve-uri(relative,base)	 
 - Functions on Boolean Values
        - fn:boolean(arg)	
        - fn:not(arg)	
        - fn:true()	
        - fn:false()	
 - Functions on Durations, Dates and Times
        - fn:dateTime(date,time)	
        - fn:years-from-duration(datetimedur)	
        - fn:months-from-duration(datetimedur)	
        - fn:days-from-duration(datetimedur)	
        - fn:hours-from-duration(datetimedur)	
        - fn:minutes-from-duration(datetimedur)	
        - fn:seconds-from-duration(datetimedur)	
        - fn:year-from-dateTime(datetime)	
        - fn:month-from-dateTime(datetime)
        - fn:day-from-dateTime(datetime)	
        - fn:hours-from-dateTime(datetime)
        - fn:minutes-from-dateTime(datetime)
        - fn:seconds-from-dateTime(datetime)
        - fn:timezone-from-dateTime(datetime)
        - fn:year-from-date(date)	
        - fn:month-from-date(date)
        - fn:day-from-date(date)	
        - fn:timezone-from-date(date)
        - fn:hours-from-time(time)
        - fn:minutes-from-time(time)
        - fn:seconds-from-time(time)
        - fn:timezone-from-time(time)
        - fn:adjust-dateTime-to-timezone(datetime,timezone)
        - fn:adjust-date-to-timezone(date,timezone)	
        - fn:adjust-time-to-timezone(time,timezone)	
 - Functions Related to QNames
        - fn:QName()	 
        - fn:local-name-from-QName()	 
        - fn:namespace-uri-from-QName()	 
        - fn:namespace-uri-for-prefix()	 
        - fn:in-scope-prefixes()	 
        - fn:resolve-QName()	 
 - Functions on Nodes
        - fn:name()
        - fn:name(nodeset)	
        - fn:local-name()
        - fn:local-name(nodeset)
        - fn:namespace-uri()
        - fn:namespace-uri(nodeset)	
        - fn:lang(lang)	
        - fn:root()
        - fn:root(node)	
 - Functions on Sequences
        - fn:index-of((item,item,...),searchitem)	
        - fn:remove((item,item,...),position)	
        - fn:empty(item,item,...)	
        - fn:exists(item,item,...)	
        - fn:distinct-values((item,item,...),collation)	
        - fn:insert-before((item,item,...),pos,inserts)	
        - fn:reverse((item,item,...))	
        - fn:subsequence((item,item,...),start,len)	
        - fn:unordered((item,item,...))	
 - Functions That Test the Cardinality of Sequences
        - fn:zero-or-one(item,item,...)
        - fn:one-or-more(item,item,...)
        - fn:exactly-one(item,item,...)
 - Equals, Union, Intersection and Except
        - fn:deep-equal(param1,param2,collation)	
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
        - fn:doc-available(URI)	
        - fn:collection()
        - fn:collection(string)	 
 - Context Functions
        - fn:position()	
        - fn:last()	
        - fn:current-dateTime()
        - fn:current-date()	
        - fn:current-time()	
        - fn:implicit-timezone()	
        - fn:default-collation()	
        - fn:static-base-uri()	
 - XSLT Functions
        - current()	
        - document()	
        - element-available()	
        - format-number()	
        - function-available()	
        - generate-id()
        - key()	
        - system-property()	
        - unparsed-entity-uri()	
