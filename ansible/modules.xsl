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
        <xsl:apply-templates select="html/body/div/nav/div/div/ul[@class='current']/li/ul" mode="index"/>
        <xsl:apply-templates select="html/body/section/div/div/div/div/div/blockquote/div/ul" mode="all"/>   
</ansible>
    </xsl:template>

    <xsl:template match="ul" mode="index">
<modules category="index">
        <xsl:apply-templates mode="index"/>
</modules>
    </xsl:template>

    <xsl:template match="li" mode="index">
       <xsl:variable name="href" select="a[1]/@href"/>
       <xsl:if test="starts-with($href, 'list_of_')">
       <xsl:variable name="name" select="replace(a[1],' modules','')"/>    
<module name="{$name}" href="{$href}"/>
       </xsl:if>
    </xsl:template>

    <xsl:template match="ul"  mode="all">
<modules category="all">
        <xsl:apply-templates mode="all"/>
</modules>
    </xsl:template>
        
    <xsl:template match="li" mode="all">
    <xsl:variable name="href" select="tokenize(a[1]/@href, '#')"/>
<module name="{$href[2]}" href="{$href[1]}">
    <xsl:value-of select="a[1]"/>
</module>
    </xsl:template>
    
    <xsl:template match="*"/>
</xsl:stylesheet>
