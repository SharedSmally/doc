<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet version="2.0"
    xmlns:cpw="http://www.cpw.com/app/xsl/app"
    xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

<xsl:output method="text" indent="yes" />
<xsl:strip-space elements="*" />

<xsl:template match="/">
main: download

download: \
<xsl:apply-templates select="/html/body/pre/A" mode="main"/>
<xsl:text>
</xsl:text>

   <xsl:apply-templates select="/html/body/pre/A"/>
</xsl:template>

<xsl:template match="A" mode="main">
   <xsl:if test="ends-with(@HREF,'.yaml')">
       <xsl:value-of select="concat('    ',text())"/> \
</xsl:if>
</xsl:template>

<xsl:template match="A">
   <xsl:if test="ends-with(@HREF,'.yaml')">
       <xsl:value-of select="text()"/>:
	wget https:/<xsl:value-of select="@HREF"/> -O $@

</xsl:if>
</xsl:template>

</xsl:stylesheet>
