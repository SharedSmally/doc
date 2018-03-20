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
include  <xsl:value-of select="@name"/>.cfg

main: init ${FILES}

init:
    @mkdir -p meta/
<xsl:for-each-group select="current-group()" group-by="@fname">
<xsl:apply-templates mode="makefile"/>
</xsl:for-each-group>    
            </xsl:result-document>

    
            <xsl:variable name="cfgfile" select="concat($dir,'/', @name,'.cfg')"/>
            <xsl:result-document method="text" href="{$cfgfile}">
FILES = \
<xsl:for-each-group select="current-group()" group-by="@fname">
<xsl:apply-templates mode="config"/>
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

    <xsl:template match="module" mode="config">
<xsl:apply-templates mode="config"/>
    </xsl:template>
    <xsl:template match="module" mode="makefile">
<xsl:apply-templates mode="makefile"/>
    </xsl:template>
    
    <xsl:template match="file" mode="config">
        <xsl:variable name="pkg" select="../@fname"/>
        <xsl:variable name="fname" select="replace($pkg,'\.', '_')"/>
<xsl:value-of select="concat($sps,'meta/', $fname, '.epi    \', $newline)"/>    
    </xsl:template>

    <xsl:template match="file" mode="makefile">
        <xsl:variable name="fname" select="concat('meta/', @name)"/>
        <xsl:variable name="xjc" select="concat(cpw:getXjc(@name, ../@fname), ' ')"/>
<xsl:value-of select="concat($fname, '.eps : ', $fname,  $newline)"/>    
<xsl:value-of select="concat($tbl, 'if [ ! -f ',  $fname, ' ]; then cp ${XOMA_HOME}/xsd/', @name,' ', $fname,'; fi', $newline)"/>
<xsl:value-of select="concat($tbl, $xjc, @name, $newline,$newline)"/>
    </xsl:template>
    
    <xsl:function name="cpw:getXjc">
        <xsl:param name="name"/>
        <xsl:param name="pkg"/>
        <xsl:variable name="fname" select="replace($pkg,'\.', '_')"/>
        <xsl:variable name="dir" select="replace($pkg, '\.', '/')"/>
        <xsl:value-of select="concat('xjc -b meta/', $fname, '.xjb -d src/main/java/', $dir, ' -p ', $pkg, ' -episode meta/', $fname, '.epi')"/> 
    </xsl:function>
    
</xsl:stylesheet>
