<xsl:stylesheet 
    xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
    xmlns:cpw="http://www.cpw.com/XSL/"  
    version="2.0">

    <xsl:output method="xml" indent="yes"/>
    <xsl:strip-space elements="*"/>

    <xsl:variable name='newline'><xsl:text>
</xsl:text></xsl:variable>
    <xsl:variable name='tbl'><xsl:text>&#x9;</xsl:text></xsl:variable>
    <xsl:variable name='sps' select="'     '"/>

	<xsl:key name="modName" match="module" use="concat(@name, '-', @version)"/>

    <xsl:template match="/">
       <xsl:apply-templates/>
    </xsl:template>

    <xsl:template match="xoma">
   		<xsl:for-each-group select="module" group-by="concat(@name, '+', @version)">
	      	<xsl:variable name="dir" select="concat('xoma/',@name,'/','v', @version)"/>
    	    <xsl:variable name="mkfile" select="concat($dir,'/makefile')"/>
        	<xsl:result-document method="text" href="{$mkfile}">
include  {@name}.cfg

main: ${FILES}
        	</xsl:result-document>

    	    <xsl:variable name="cfgfile" select="concat($dir,'/', @name,'.cfg')"/>
        	<xsl:result-document method="text" href="{$cfgfile}">
FILES = \
<xsl:for-each-group select="current-group()" group-by="@fname">
<xsl:apply-templates/>
</xsl:for-each-group>
     <!-- current-group: is module node -->
        	</xsl:result-document>
			
       		<xsl:variable name="pomfile" select="concat($dir,'/pom.xml')"/>
        	<xsl:result-document method="xml" href="{$pomfile}">
<project xmlns="http://maven.apache.org/POM/4.0.0" 
    xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" 
    xsi:schemaLocation="http://maven.apache.org/xsd/maven-4.0.0.xsd">
  <modelVersion>4.0.0</modelVersion>
  <groupId>com.jpw.xoma</groupId>
  <artifactId><xsl:value-of select="@name"/></artifactId>
  <version><xsl:value-of select="@version"/></version>
  <packaging>jar</packaging>
  
</project>
        	</xsl:result-document>
        </xsl:for-each-group>
    </xsl:template>

	<xsl:template match="module">
<xsl:apply-templates/>
	</xsl:template>
		
	<xsl:template match="file">
<xsl:value-of select="concat($sps, @name, '    \', $newline)"/>	
	</xsl:template>
</xsl:stylesheet>
