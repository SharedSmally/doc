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

    <xsl:template match="HTML">
        <xsl:apply-templates select="BODY/DIV[@id='sidebar-wrapper']" mode="side"/>
        <xsl:apply-templates select="BODY/DIV/DIV[@id='page-content-wrapper']"/>
    </xsl:template>

    <xsl:template match="BODY/DIV/DIV">  <!--  API Overview -->
       <xsl:variable name="date" select="tokenize(tokenize(DIV[1]/DIV[2]/DIV[1],': ')[2], '\s+')[1]"/>
       <xsl:variable name="version" select="tokenize(DIV[1]/DIV[2]/DIV[2],': ')[2]"/>
<k8sapi version="{$version}" date="{$date}">
           <xsl:apply-templates/>
</k8sapi>
    </xsl:template>
    
    <!-- example -->
    <xsl:template match="BODY/DIV/DIV/DIV">   
        <xsl:variable name="kube" select="DIV/DIV/PRE[@class='kubectl']"/>
        <xsl:variable name="curl" select="DIV/DIV/PRE[@class='curl']"/>
        <xsl:if test="string-length($kube)>0">
<kubectl name="{@id}"><xsl:value-of select="$kube"/></kubectl>
        </xsl:if>
            
        <xsl:if test="string-length($curl)>0">
<curl  name="{@id}"><xsl:value-of select="$curl"/></curl>
        </xsl:if>
    </xsl:template>
 
    <xsl:template match="BODY/DIV/DIV/H1">
    </xsl:template>

    <!-- H2 could also be group -->
    <xsl:template match="BODY/DIV/DIV/H2">
    </xsl:template>

    <xsl:template match="BODY/DIV/DIV/H3">
    </xsl:template>

    <xsl:template match="*">
    </xsl:template>

    <xsl:template match="BODY/DIV" mode="side">
    </xsl:template>
    
