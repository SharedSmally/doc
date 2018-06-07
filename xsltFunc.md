## [XSLT 2.0](https://www.w3.org/TR/xslt2)
### [XSLT 2.0 function](http://www.xsltfunctions.com/xsl/alpha.html)
## Check if file exists:
- Check text exist
```
<xsl:if test="unparsed-text-available('hello_world.txt')">
  <!-- ... -->
</xsl:if>
```
- Check xml exists
```
<xsl:if test="doc-available('hello_world.xml')">
  <!-- ... -->
</xsl:if>
```
- General check file exist
- Generate file
```
<!-- Category: instruction -->
<xsl:result-document
  format? = { qname }
  href? = { uri-reference }
  validation? = "strict" | "lax" | "preserve" | "strip"
  type? = qname
  method? = { "xml" | "html" | "xhtml" | "text" | qname-but-not-ncname }
  byte-order-mark? = { "yes" | "no" }
  cdata-section-elements? = { qnames }
  doctype-public? = { string }
  doctype-system? = { string }
  encoding? = { string }
  escape-uri-attributes? = { "yes" | "no" }
  include-content-type? = { "yes" | "no" }
  indent? = { "yes" | "no" }
  media-type? = { string }
  normalization-form? = { "NFC" | "NFD" | "NFKC" | "NFKD" | "fully-normalized" | "none" | nmtoken }
  omit-xml-declaration? = { "yes" | "no" }
  standalone? = { "yes" | "no" | "omit" }
  undeclare-prefixes? = { "yes" | "no" }
  use-character-maps? = qnames
  output-version? = { nmtoken }>
  <!-- Content: sequence-constructor -->
</xsl:result-document>
```

- Group
```
    <xsl:for-each-group select="file" group-by="@project">
        <xsl:value-of select="current-grouping-key()"/>
        <xsl:value-of select="avg(current-group()/@size)"/>
        
        <xsl:for-each select="current-group()">
        <xsl:for-each>
        
        <xsl:for-each select="current-group()">
            <xsl:copy>
               <xsl:apply-templates select="."/>
            </xsl:copy>
        </xsl:for-each>
    </xsl:for-each-group>
    
    <xsl:for-each-group select="*" group-ending-with="*[position() mod 3 = 0]">
    </xsl:for-each-group>
```
- Read xml: <xsl variable name="xsd" select="document('xmlfile')/$nodes"/>
- Output file: <xsl:result-document href="ref" method="text|xml|html"></xsl:result-document>
- Read multiple XML files from a directory:
```
    <xsl:variable name="files" select="collection('../foo/?select=blor*.xml')"/>
    
    <xsl:variable name="xsds" select="concat('../',$path2collection,'?select=*.xsd;recurse=yes;on-error=warning')"/>
    <xsl:variable name="files" select="collection($xsds)/xs:schema"/>    
```
- regex: match
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
      <addrLine2>
        <xsl:value-of select="$elValue"/>
      </addrLine2>
    </xsl:non-matching-substring>
  </xsl:analyze-string>
</xsl:template>
```
- Output xml node information: serialize
```
<xsl:message>Query namespace <xsl:value-of select="$ns"/>; node:<xsl:value-of select="serialize($dep)"/></xsl:message> 
<xsl:message>Query namespace <xsl:value-of select="$ns"/>; node:<xsl:value-of select="string($dep)"/></xsl:message> 
```
