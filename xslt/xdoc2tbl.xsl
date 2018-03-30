<xsl:stylesheet 
    xmlns:xsl="http://www.w3.org/1999/XSL/Transform" 
    xmlns:xs="http://www.w3.org/2001/XMLSchema"
    xmlns:pkg="http://schemas.microsoft.com/office/2006/xmlPackage"
    xmlns:w="http://schemas.openxmlformats.org/wordprocessingml/2006/main"
    xmlns:jpw="http://www.jpw.com/product/app"
    exclude-result-prefixes="pkg w jpw"
    version="2.0">

    <xsl:output method="xml" indent="yes"/>
    <xsl:strip-space elements="*"/>
    
    <xsl:template match="pkg:package">
<smpp version="5.0.0">
        <xsl:apply-templates select=".//w:tbl"/>
</smpp>
    </xsl:template>

    <xsl:template match="w:tbl">
       <xsl:variable name="preTitle" select="jpw:getText(preceding-sibling::*[1])"/>
        <xsl:variable name="postTitle" select="jpw:getText(following-sibling::*[1])"/>
       <table name="{$preTitle}" desc="{$postTitle}">
           <xsl:apply-templates select=".//w:tr"/>
       </table>
    </xsl:template>

    <xsl:template match="w:tr">
       <row>
           <xsl:apply-templates select=".//w:tc"/>
       </row>
    </xsl:template>

    <xsl:template match="w:tc">
       <column>
         <xsl:for-each select=".//w:t">
              <xsl:variable name="txt" select="normalize-space(text())"/>
              <xsl:if test="string-length($txt) > 0">
                  <xsl:value-of select="concat($txt, ' ')"/>
              </xsl:if>
         </xsl:for-each>
       </column>
    </xsl:template>
    
    <xsl:template match="*"/>
    
    <xsl:function name="jpw:getText">
       <xsl:param name="node"/>
       <xsl:value-of select="'text'"/>
    </xsl:function>
</xsl:stylesheet>
