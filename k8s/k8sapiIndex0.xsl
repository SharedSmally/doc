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
<k8s type="index">
        <xsl:apply-templates select="BODY/DIV[@id='sidebar-wrapper']" />
</k8s>
    </xsl:template>
    
    <xsl:template match="BODY/DIV">
       <xsl:apply-templates/>
    </xsl:template>
    
    <xsl:template match="BODY/DIV/UL">
       <xsl:apply-templates/>
    </xsl:template>

    <xsl:template match="BODY/DIV/UL/LI">
       <xsl:choose>
           <xsl:when test="count(A/STRONG)>0">
<category name="{A/STRONG/text()}"/>
           </xsl:when>
           
           <xsl:otherwise>
<group name="{A/text()}"/>
           </xsl:otherwise>
       </xsl:choose>
    </xsl:template>
    
    <xsl:template match="BODY/DIV/UL/UL">
       <xsl:choose>
           <xsl:when test="count(UL)=0">
<group name="{LI/A/text()}"/>
           </xsl:when>

           <xsl:otherwise>
              <xsl:apply-templates select="UL"/>
           </xsl:otherwise>
       </xsl:choose>
    </xsl:template>

    <xsl:template match="BODY/DIV/UL/UL/UL">
<operations name="{LI}">
    <xsl:apply-templates select="UL/LI"/>
</operations>
    </xsl:template>

 
    <xsl:template match="BODY/DIV/UL/UL/UL/UL/LI">
<operation name="{A/text()}"/>
    </xsl:template>
    
    <xsl:template match="*">
    </xsl:template>

</xsl:stylesheet>
