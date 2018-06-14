- Eliminate empty namespace :  xmlns=""
   1. In the stylesheet, define exclude-result-prefixes:
   ```
   <xsl:stylesheet 
    xmlns:xsl="http://www.w3.org/1999/XSL/Transform" 
    xmlns:xs="http://www.w3.org/2001/XMLSchema"
    xmlns:jpw="http://www.jpw.com/xsl/app"
    exclude-result-prefixes="xsl xs jpw"
    version="2.0">
   ```
   2. In the output root node, set xmlns. Will not output xmlns if it is not in exclude-result-prefixes list.
   ```
   <catalog xmlns="urn:oasis:names:tc:entity:xmlns:xml:catalog">
   ```
   3. In the child node, set the same xmlns as the root. Otherwise will output xmlns="":
   ```
    <public publicId ="{@namespace}" uri="{$uri}" xmlns="urn:oasis:names:tc:entity:xmlns:xml:catalog"/> 
    ```
- collection: base-uri(); document()
```
<xsl:variable name="files" select="collection('../foo/?select=blor*.xml')"/>
<xsl:variable name="fileNames" select="'../foo/?select=blor*.xml'"/>

<xsl:for-each select="collection($fileNames)/xs:schema">
   ...........
<xsl:for-each>
```
- [XSLT group](https://www.xml.com/pub/a/2003/11/05/tr.html)
```
  <xsl:for-each-group select="" group-by="">
     <xsl:variable name="key" select="current-grouping-key()"/>
     <xsl:for-each select="current-group()">

     </xsl:for-each>

  </xsl:for-each-group>
```
```
    <xsl:for-each-group select="file" group-by="@project">
      <xsl:value-of select="current-grouping-key()"/>
      <xsl:text>xxx</xsl:text>
    </xsl:for-each-group>
```
```
  <xsl:for-each-group select="file" group-by="@project">
    <xsl:for-each select="current-group()">
      <xsl:value-of select="@name"/>, <xsl:value-of select="@size"/>
      <xsl:text>xxx</xsl:text>
    </xsl:for-each>

    <xsl:text>average size for </xsl:text> <xsl:value-of select="current-grouping-key()"/>
    <xsl:text> group: </xsl:text> <xsl:value-of select="avg(current-group()/@size)"/>
  </xsl:for-each-group>
```

- [XSLT regrex](https://www.xml.com/pub/a/2003/06/04/tr.html)
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
