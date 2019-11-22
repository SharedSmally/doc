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
     <xsl:apply-templates select="category"/>
</k8s>
    </xsl:template>
    
    <xsl:template match="category">
       <xsl:variable name="cname" select="@name"/>
<category>
       <xsl:copy-of select="@*"/>
       <xsl:apply-templates select="following-sibling::group[@category=$cname]"/>
</category>
    </xsl:template>

    <xsl:template match="group">
       <xsl:variable name="cname" select="@category"/>
       <xsl:variable name="gname" select="@name"/>
<group>
       <xsl:copy-of select="@*[name()!='category']"/>
       <xsl:apply-templates select="following-sibling::operations[@category=$cname and @group=$gname]"/>
</group>
    </xsl:template>

    <xsl:template match="operations">
<operations>
       <xsl:copy-of select="@*[name()!='category' and name() != 'group']"/>
       <xsl:copy-of select="*"/>
</operations>
    </xsl:template>

    <xsl:template match="*">
    </xsl:template>

</xsl:stylesheet>
