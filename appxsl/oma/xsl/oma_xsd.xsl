<xsl:stylesheet
    xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
    xmlns:xs="http://www.w3.org/2001/XMLSchema"
    xmlns:cpw="http://www.jpw.com/product/app/cxx"
    exclude-result-prefixes="cpw xs"
    version="2.0">

    <xsl:output method="xml" indent="yes"/>
    <xsl:strip-space elements="*"/>
    
    <xsl:param name='newline'><xsl:text>
</xsl:text></xsl:param>

    <xsl:template match="/">
        <xsl:apply-templates/>
    </xsl:template>

    <xsl:template match="html">
<product name="oma" category="xsd" base="http://openmobilealliance.org/">
        <xsl:apply-templates select="body/pre"/>
</product>
    </xsl:template>

    <xsl:template match="pre">
       <xsl:apply-templates/>
    </xsl:template>
    
    <xsl:template match="A">
        <xsl:if test="not(starts-with(text(),'[To Parent'))">
<xsd name="{text()}" url="{@HREF}"/>
        </xsl:if>
    </xsl:template>
    
    <xsl:template match="text()">
       <info><xsl:value-of select="normalize-space(.)"/></info>
    </xsl:template>
    
    <xsl:template match="*"/>
</xsl:stylesheet>
