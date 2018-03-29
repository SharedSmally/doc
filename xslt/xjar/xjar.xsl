<xsl:stylesheet 
    xmlns:xsl="http://www.w3.org/1999/XSL/Transform" 
    version="2.0">

    <xsl:variable name="newline"><xsl:text>
</xsl:text></xsl:variable>

    <xsl:output method="text"/>
    <xsl:template match="/">
        <xsl:apply-templates/>
    </xsl:template>

    <xsl:template match="/asn1">
<xsl:apply-templates/>

<xsl:for-each select="jar">
<xsl:value-of select="concat($newline, @name, ':')"/>
	mvn install:install-file -Dfile=<xsl:value-of select="concat(/asn1/@src,@file)"/> -DpomFile=<xsl:value-of select="concat(@name,'.pom.xml')"/>
</xsl:for-each>

DEPLOY_TARGETS = <xsl:for-each select="jar">
   <xsl:value-of select="concat(@name, ' ')"/>
</xsl:for-each>
    </xsl:template>    

    <xsl:template match="jar">
         <xsl:variable name="fname" select="concat(@name, '.pom.xml')"/>
         <xsl:result-document method="xml" href="{$fname}">
<project xmlns="http://maven.apache.org/POM/4.0.0" 
    xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" 
    xsi:schemaLocation="http://maven.apache.org/xsd/maven-4.0.0.xsd">
     <modelVersion>4.0.0</modelVersion>
  
     <groupId><xsl:value-of select="../@base"/></groupId>
     <artifactId><xsl:value-of select="@name"/></artifactId>
     <version><xsl:value-of select="../@version"/></version>
     <packaging>jar</packaging>
</project>
         </xsl:result-document>
    </xsl:template>
    
    <xsl:template match="*"/>
</xsl:stylesheet>
