##TIPS
### [Group](https://www.xml.com/pub/a/2003/11/05/tr.html): for-each-group
```
 <xsl:for-each-group select="file" group-by="@project">
      <xsl:text><xsl:value-of select="current-grouping-key()"/></xsl:text>
 </xsl:for-each-group>
 
 <xsl:for-each-group select="file" group-by="@project">
    <xsl:for-each select="current-group()">
      <xsl:text><xsl:value-of select="@name"/>, <xsl:value-of select="@size"/></xsl:text>
    </xsl:for-each>

    <xsl:text>average size for </xsl:text>
    <xsl:value-of select="current-grouping-key()"/>
    <xsl:text> group: </xsl:text>
    <xsl:value-of select="avg(current-group()/@size)"/>
    <xsl:text>
    </xsl:text>
 </xsl:for-each-group>

    <xsl:for-each-group select="*" group-ending-with="*[position() mod 3 = 0]">
        <xsl:for-each select="current-group()">
          <xsl:copy> <xsl:apply-templates  select="@*|node()"/></xsl:copy>
        </xsl:for-each>
    </xsl:for-each-group>
```
The group-by, group-adjacent, group-starting-with, and group-ending-with attributes can all name an element as the criterion to determine grouping boundaries; but, as this last example shows, you can be more creative than that, using functions and XPath predicates to identify the source tree nodes that should be treated as group boundaries. The Examples section of the XSLT 2.0 Working Draft's section on grouping has additional good demonstrations of what you can do with these attributes to customize the xsl:for-each-group element's treatment of your documents.


### [pattern match](https://www.xml.com/pub/a/2003/06/04/tr.html): xsl:matches; xsl:analyze-string
```
<xsl:template match="p">
  <xsl:copy>
    <xsl:attribute name="matchesPattern">
      <xsl:value-of select='matches(.,".*\$\d+\.\d{2}.*")'/>
    </xsl:attribute>
    <xsl:value-of select='replace(., "\$\d+\.\d{2}","\$xx.xx")'/>
  </xsl:copy>
</xsl:template>
```
```
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
```
