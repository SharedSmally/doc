<xsl:stylesheet
    xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
    xmlns:xs="http://www.w3.org/2001/XMLSchema"
    xmlns:cpw="http://www.jpw.com/product/app/cxx"
    exclude-result-prefixes="cpw xs"
    version="2.0">

    <xsl:output method="xml" indent="yes"/>
    <xsl:strip-space elements="*"/>
    <xsl:param name="text-encoding" select="'iso-8859-1'"/>

    <xsl:template match="/">
<ansible category="modules">
        <xsl:apply-templates select="html/body/blockquote/div/ul[@class='simple']/li"/>
</ansible>
    </xsl:template>

    <xsl:template match="html/body/blockquote/div/ul/li">
<module href="{a/@href}"><xsl:value-of select="text()"/></module>
    </xsl:template>
    
</xsl:stylesheet>
