## [W3 XSL]()

## [Apache FOP](https://xmlgraphics.apache.org/fop/)
- Command: 
```
fop -xml name.xml -xsl name2fo.xsl -pdf name.pdf
```
- XSLT 2.0:
Specify the processor implementation used by FOP by adding a VM parameter to the start script where org.apache.fop.cli.Main is called:
```
-Djavax.xml.transform.TransformerFactory=net.sf.saxon.TransformerFactoryImpl (example for Saxon) 
```

### FOP XSLT
```
<?xml version="1.0" encoding="utf-8"?>
<xsl:stylesheet version="1.0"
      xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
      xmlns:fo="http://www.w3.org/1999/XSL/Format">
  <xsl:output method="xml" indent="yes"/>
  
  <xsl:template match="/">
    <fo:root>
      <fo:layout-master-set>
        <fo:simple-page-master master-name="A4-portrait"
              page-height="29.7cm" page-width="21.0cm" margin="2cm">
          <fo:region-body/>
        </fo:simple-page-master>
      </fo:layout-master-set>
      
      <fo:page-sequence master-reference="A4-portrait">
        <fo:flow flow-name="xsl-region-body">
          <fo:block>
            Hello, <xsl:value-of select="name"/>!
          </fo:block>
        </fo:flow>
      </fo:page-sequence>
    </fo:root>
  </xsl:template>
</xsl:stylesheet>
```
