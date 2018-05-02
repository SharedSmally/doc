## [XSLT 2.0](https://www.w3.org/TR/xslt2)
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
