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
        <xsl:apply-templates/>
    </xsl:template>

    <xsl:template match="k8sapi">
<k8sapi version="{@version}" date="{@date}" type="resource">
           <xsl:apply-templates/>
</k8sapi>
    </xsl:template>
 
    <xsl:template match="resource">
        <xsl:variable name="node1" select="preceding-sibling::*[1]"/>
        <xsl:variable name="node2" select="preceding-sibling::*[2]"/>
<resource>
        <xsl:if test="name($node2)='group'">
            <xsl:variable name="names" select="tokenize($node2/@name)"/>
            <xsl:attribute name="name"><xsl:value-of select="$names[1]"/></xsl:attribute>
            <xsl:attribute name="version"><xsl:value-of select="$names[2]"/></xsl:attribute>
            <xsl:attribute name="group"><xsl:value-of select="$names[3]"/></xsl:attribute>
        </xsl:if>

        <xsl:if test="name($node1)='h3'">
            <xsl:variable name="names" select="tokenize($node1/@name)"/>
            <xsl:attribute name="name"><xsl:value-of select="$names[1]"/></xsl:attribute>
            <xsl:attribute name="version"><xsl:value-of select="$names[2]"/></xsl:attribute>
            <xsl:attribute name="group"><xsl:value-of select="$names[3]"/></xsl:attribute>
        </xsl:if>

        <xsl:if test="name($node1)='category'">
            <xsl:copy-of select="$node1"/>
        </xsl:if>

        <xsl:apply-templates/>
</resource>
    </xsl:template>

    <xsl:template match="field">
        <xsl:copy-of select="."/>
    </xsl:template>

    <xsl:template match="*">
    </xsl:template>    
</xsl:stylesheet>
