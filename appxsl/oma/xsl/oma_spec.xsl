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
<product name="oma" base="http://openmobilealliance.org/">
        <xsl:apply-templates select="body//div[@class='container']/div/table[@id='releases-table']"/>
</product>
    </xsl:template>

    <xsl:template match="table">
        <xsl:apply-templates/>
    </xsl:template>
    
    <xsl:template match="tbody">
        <xsl:apply-templates/>
    </xsl:template>
    
    <xsl:template match="tr">
        <xsl:choose>
            <xsl:when test="count(td)=4 and count(td[1]/div)=2">
<spec name="{td[1]/div[1]/a[1]/text()}" url="{td[1]/div[1]/a[1]/@href}">
               <xsl:apply-templates select="td[1]/div[2]/ul/li" mode="lwm2m" />
               <xsl:apply-templates select="td[3]" mode="candidate"/>
               <xsl:apply-templates select="td[4]" />
</spec>
            </xsl:when>
            
            <xsl:when test="count(td)=4">
<spec name="{td[1]/a[1]/text()}" url="{td[1]/a[1]/@href}">
               <xsl:apply-templates select="td[3]" mode="candidate"/>
               <xsl:apply-templates select="td[4]" />
</spec>
            </xsl:when>
            <xsl:otherwise>
                <xsl:message>unknown format:<xsl:value-of select="."/></xsl:message>
            </xsl:otherwise>
        </xsl:choose>
    </xsl:template>

    <xsl:template match="td">
         <xsl:apply-templates select="ul/li"/>
    </xsl:template>

    <xsl:template match="td" mode="candidate">
        <xsl:apply-templates select="ul/li" mode="candidate"/>
    </xsl:template>

    <xsl:template match="li">
        <xsl:variable name="ver" select="normalize-space(text())"/>
        <xsl:variable name="date" select="normalize-space(span/text())"/>
         <xsl:if test="$ver!='-'">
    <version ver="{$ver}">
             <xsl:if test="$date">
       <xsl:attribute name="date"><xsl:value-of select="$date"/></xsl:attribute>
             </xsl:if>
    </version>
         </xsl:if>
    </xsl:template>

    <xsl:template match="li" mode="candidate">
        <xsl:variable name="ver" select="normalize-space(text())"/>
        <xsl:variable name="date" select="normalize-space(span/text())"/>
         <xsl:if test="$ver!='-'">
    <version ver="{$ver}" candidator="true">
             <xsl:if test="$date">
       <xsl:attribute name="date"><xsl:value-of select="$date"/></xsl:attribute>
             </xsl:if>
    </version>
         </xsl:if>
    </xsl:template>
    
    <xsl:template match="li" mode="lwm2m">
       <xsl:choose>
           <xsl:when test="count(a)=1"> 
 <module name="{a/text()}" url="{a/@href}"/>
           </xsl:when>
           <xsl:when test="count(a)=0"/> 
           <xsl:otherwise>
              <xsl:message>Unknown format: <xsl:value-of select="."/></xsl:message>
           </xsl:otherwise>
       </xsl:choose>
    </xsl:template>
    
    <xsl:template match="*"/>
</xsl:stylesheet>
