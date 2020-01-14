<xsl:stylesheet
    xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
    xmlns:xs="http://www.w3.org/2001/XMLSchema"
    xmlns:cpw="http://www.jpw.com/product/app/cxx"
    exclude-result-prefixes="cpw xs"
    version="2.0">

    <xsl:output method="xml" indent="yes"/>
    <xsl:strip-space elements="*"/>
    
    <xsl:param name="name" select="'xoma'"/>
    <xsl:param name="base" select="'http://openmobilealliance.org/'"/>
    <xsl:param name="dirLabel" select="'&lt;dir&gt;'"/>

    <xsl:template match="/">
        <xsl:apply-templates/>
    </xsl:template>

    <xsl:template match="html">
<product name="{$name}" base="{$base}">
        <xsl:apply-templates select="body/pre"/>
</product>
    </xsl:template>

    <xsl:template match="pre">
       <xsl:apply-templates/>
    </xsl:template>
    
    <xsl:template match="A">
        <xsl:if test="not(starts-with(text(),'[To Parent'))">
            <xsl:variable name="s0" select="normalize-space(preceding-sibling::text()[1])"/>
            <xsl:variable name="info" select="tokenize($s0)"/>

            <xsl:choose>
                <!-- 1/13/2020 12:25 PM 1909090 -->
                <xsl:when test="count($info)=4 and $info=$dirLabel">
<dir name="{text()}" url="{@HREF}" date="{$info[1]}"/>
                </xsl:when>
                <xsl:when test="count($info)=4">
<file name="{text()}" url="{@HREF}" date="{$info[1]}" size="{$info[4]}"/>
                </xsl:when>
                <xsl:otherwise>
                   <xsl:message>UNKNOW format:<xsl:value-of select="$s0"/></xsl:message>
                </xsl:otherwise>
            </xsl:choose>

        </xsl:if>
    </xsl:template>
    
    <xsl:template match="text()"/>
    <xsl:template match="*"/>
</xsl:stylesheet>
