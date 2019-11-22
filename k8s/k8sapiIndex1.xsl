
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

    <xsl:template match="k8s">
<k8s>
     <xsl:for-each select="@*"><xsl:copy-of select="."/></xsl:for-each>
     <xsl:apply-templates/>
</k8s>
    </xsl:template>

    <xsl:template match="category">
       <xsl:copy-of select="."/>
    </xsl:template>

    <xsl:template match="group">
<group  category="{preceding-sibling::category[1]/@name}">
        <!-- <xsl:for-each select="@*[name()!='category']"><xsl:copy-of select="."/></xsl:for-each> -->
        <xsl:copy-of select="@*"/>
        <xsl:for-each select="*"><xsl:copy-of select="."/></xsl:for-each>
</group>
    </xsl:template>

    <xsl:template match="operations">
<operations category="{preceding-sibling::category[1]/@name}" group="{preceding-sibling::group[1]/@name}">
        <xsl:for-each select="@*[name()!='category' and name()!='group']"><xsl:copy-of select="."/></xsl:for-each>
        <xsl:for-each select="*"><xsl:copy-of select="."/></xsl:for-each>
</operations>
    </xsl:template>

    <xsl:template match="*">
    </xsl:template>

</xsl:stylesheet>
