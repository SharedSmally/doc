<xsl:stylesheet 
    xmlns:xsl="http://www.w3.org/1999/XSL/Transform" 
    xmlns:xs="http://www.w3.org/2001/XMLSchema"
    xmlns:jpw="http://www.jpw.com/product/app"
    version="2.0">

    <xsl:output method="xml" indent="yes"/>
    <xsl:strip-space elements="*"/>

    <xsl:variable name="newline"><xsl:text>
</xsl:text></xsl:variable>

    <xsl:template match="/">
        <xsl:apply-templates/>
    </xsl:template>

    <xsl:template match="x3gpp">
        <x3gpp name="{@name}" coding="{@coding}" version="{@version}" 
               category="{@category}" site="{@site}" ftp="{@ftp}">
            <xsl:apply-templates/>
        </x3gpp>
    </xsl:template>
    
    <xsl:template match="release">
        <release year="{@year}">
            <xsl:for-each-group select="spec" group-by="@major">
                <xsl:sort select="@ver" order="descending"/>
                <xsl:variable name="version" select="concat(@major,'.',@minor,'.', @patch)"/>
                <spec name="{@name}" major="{@major}"
                      version="{$version}" url="{@url}"/>
            </xsl:for-each-group>
        </release>
    </xsl:template>
    
</xsl:stylesheet>
