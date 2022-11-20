# [W3 XSLT](https://www.w3.org/TR/xslt/)
## References
- [xslt 2.0](https://www.w3.org/TR/2021/REC-xslt20-20210330/)
- [xslt 3.0](https://www.w3.org/TR/2017/REC-xslt-30-20170608/)
- [XSLT functions](https://www.w3.org/2005/04/xpath-functions/)
- [Grouping With XSLT 2.0](https://www.xml.com/pub/a/2003/11/05/tr.html)
- [Regular Express Match](https://www.xml.com/pub/a/2003/06/04/tr.html)
- [Collections](https://www.oreilly.com/library/view/xslt-2nd-edition/9780596527211/ch08s07.html)
- Document:
     - import xml file: document  
     - export xml file:  xsl:result-document

## Useful Functions
- xsl file: static-base-uri()/base-uri(document(''))
- target xml: base-uri()
- source xml: document-uri(root())
- collections: 

## Sample
```
<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet version="2.0"	xmlns:cpw="http://www.jpw.com/app"
	xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
	exclude-result-prefixes="cpw"	>
    <xsl:strip-space elements="*"/>
    <xsl:output method="xml" omit-xml-declaration="yes" indent="yes"/>
	<xsl:template match="/">
		<xsl:apply-templates/>	
	</xsl:template>

	<xsl:template match="/node" mode="mode1">
		<xsl:apply-templates/>	
    <xsl:variable name="txt"><xsl:apply-templates mode="serialize" select="."/></xsl:variable> 
	</xsl:template>
  
<xsl:template match="*" mode="serialize">
  <xsl:text>&lt;</xsl:text>
  <xsl:value-of select="name()"/>
  <xsl:text>&gt;</xsl:text>
  <xsl:apply-templates mode="serialize"/>
  <xsl:text>&lt;/</xsl:text>
  <xsl:value-of select="name()"/>
  <xsl:text>&gt;</xsl:text>
</xsl:template>
<xsl:template match="text()" mode="serialize">
  <xsl:value-of select="."/>
</xsl:template>
</  
```

### Group
```
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="2.0">
  <xsl:output method="text"/>
  <xsl:template match="files">
    <xsl:for-each-group select="file" group-by="@project">
      <xsl:value-of select="current-grouping-key()"/>
      <xsl:text>
</xsl:text>
    </xsl:for-each-group>
  </xsl:template>
</xsl:stylesheet>
```
### Regular Express
```
<xsl:template match="addrLine2">
  <xsl:variable name="elValue" select="."/>
  <xsl:analyze-string select="$elValue" regex="\s*(.*)\s*,\s*([A-Z]{{2}})\s+(\d{{5}}(\-\d{{4}})?)\s*">
    <xsl:matching-substring>
      <city><xsl:value-of select="regex-group(1)"/></city>
      <state><xsl:value-of select="regex-group(2)"/></state>
      <zip><xsl:value-of select="regex-group(3)"/></zip>
    </xsl:matching-substring>

    <xsl:non-matching-substring>
      <addrLine2><xsl:value-of select="$elValue"/></addrLine2>
    </xsl:non-matching-substring>
  </xsl:analyze-string>
</xsl:template>
```

### Collection: import mltiple xml files
```
<collection>
  <doc href="po38292.xml"/>
  <doc href="po38293.xml"/>
  <doc href="po38294.xml"/>
  <doc href="po38295.xml"/>
</collection>

 <xsl:template match="/">
   <xsl:apply-templates mode="inFile" select="collection('file:///C:/temp?select=*.xml;recurse=yes')"/>
 </xsl:template>
```
### Regular Express replace
```
<xsl:function name="cpw:trim">
   <xsl:param name="t0"/>
   <xsl:variable name="s0" select="normalize-space($t0)"/>
   <xsl:variable name="s1" select='replace($s0, "\.\s+(\d+)",".$1")'/>
   <xsl:value-of select='replace($s1, "(\d+)\s+\.","$1.")'/>
</xsl:function>
```

### Import/Export documents
import xml file
```
<xsl:for-each select="document('somefile.xml')/groups/group/member[@name='somename']">
    something
</xsl:for-each>
```
Export file(s)
```
     <xsl:for-each select="products/product">
      <xsl:result-document method="xml" href="product_{@id}-output.xml">
        <xsl:copy-of select="."/>
      </xsl:result-document>
    </xsl:for-each> 
```
### Select specific nodes
```
@*: All attributes
<xsl:apply-templates select="*[name(  ) != 'element-to-ignore']"/>
```

### Command Parameters
```
    <xsl:param name="startX" as="xs:integer" required="yes"/>
    
  java org.apache.xalan.xslt.Process -in xyz.xml -xsl params.xsl -param startX 50 -param baseColor magenta
  java org.apache.xalan.xslt.Process -in xyz.xml -xsl params.xsl startX=50 baseColor=magenta
```

### call-template
```
<xsl:call-template name="draw-box">
  <xsl:with-param name="startX" select="50"/>
  <xsl:with-param name="startY" select="50"/>
</xsl:call-template>

<xsl:template name="draw-box">
  <xsl:parameter name="startX" />
  <xsl:parameter name="startY" />
</xsl:template>
```
