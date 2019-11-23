<xsl:stylesheet
    xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
    xmlns:xs="http://www.w3.org/2001/XMLSchema"
    exclude-result-prefixes="xs"
    version="2.0">

    <xsl:output method="xml" indent="yes"/>
    <xsl:strip-space elements="*"/>
    <xsl:param name="text-encoding" select="'iso-8859-1'"/>

    <xsl:template match="/">
<ansible category="modules">
        <xsl:apply-templates select="html/body/section/div/div/div/div/div" />   
</ansible>
    </xsl:template>
    
    <xsl:template match="div">
        <xsl:attribute name="group"><xsl:value-of select="h1"/></xsl:attribute>
        <xsl:apply-templates select="blockquote" mode="group"/>
        <xsl:apply-templates select="div" mode="group"/>
    </xsl:template>

    <xsl:template match="blockquote" mode="group" >
<group name="{@id}">
    <xsl:apply-templates select="child::div/ul"/>
</group>    
    </xsl:template>
           
    <xsl:template match="div" mode="group">
<group name="{@id}">
    <xsl:apply-templates select="blockquote/div/ul"/>
</group>    
    </xsl:template>

    <xsl:template match="ul">
        <xsl:apply-templates />
    </xsl:template>
        
    <xsl:template match="li" >
    <xsl:variable name="href" select="tokenize(a[1]/@href, '#')"/>
<module name="{$href[2]}" href="{$href[1]}">
    <xsl:value-of select="a[1]"/>
</module>
    </xsl:template>
    
    <xsl:template match="*"/>
</xsl:stylesheet>
