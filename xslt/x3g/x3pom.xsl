<xsl:stylesheet 
    xmlns:xsl="http://www.w3.org/1999/XSL/Transform" 
    xmlns:xs="http://www.w3.org/2001/XMLSchema"
    xmlns:jpw="http://www.jpw.com/product/app"
    exclude-result-prefixes="jpw xsl xs"
    version="2.0">

    <xsl:output method="text" indent="yes"/>
    <xsl:strip-space elements="*"/>

    <!--  project base dir -->
    <xsl:param name="ppdir" select="'.'"/>
    <xsl:variable name="newline"><xsl:text>
</xsl:text></xsl:variable>
    <xsl:variable name='tbl'><xsl:text>&#x9;</xsl:text></xsl:variable>
    <xsl:variable name='sps' select="'     '"/>
    <xsl:variable name='targets' select="'main gen package deploy clean cleanall'"/>
    <xsl:variable name="name" select="/x3gpp/@name"/>
    <xsl:variable name="asn1ver" select="'7.0.5'"/>
    
    <xsl:variable name="minVer" select="'4'"/>
    <xsl:variable name="site" select="'http://www.3gpp.org/'"/>
    
    <xsl:template match="/">
        <xsl:apply-templates/>
    </xsl:template>

    <xsl:template match="/x3gpp">
        <xsl:apply-templates/>
        <xsl:apply-templates mode="year"/>
    </xsl:template>
    
    <xsl:template match="/x3gpp/release">
        <xsl:apply-templates mode="makefile"/>
        <xsl:apply-templates mode="pomXml"/>
    </xsl:template>

    <xsl:template match="spec" mode="makefile">
       <xsl:if test="number(@major) &gt; number($minVer)">
        <xsl:variable name="mkfile" select="concat($ppdir,'/v',@version,'/makefile')"/>
        <xsl:result-document method="text" href="{$mkfile}">
ZIPDIR=${X3G_HOME}/xzip
DOCDIR=${X3G_HOME}/xdoc

main: init gen
	
init:
	@mkdir -p meta
	
gen:meta/<xsl_value-of select="$name"/>.asn1

<xsl_value-of select="concat($name,'.asn1 : ${DOC/DIR}/', $name, '/v', @version,'/',@file,'.doc',$newline"/>

<xsl_value-of select="concat('${DOC/DIR}/', $name, '/v', @version,'/',@file,'.doc : ${ZIPDIR}/',$name,'/', $newline"/>

        </xsl:result-document>
        </xsl:if>
    </xsl:template>

    <xsl:template match="spec" mode="pomXml">
      <xsl:if test="number(@major) &gt; number($minVer)">
        <xsl:variable name="pomXmlfile" select="concat($ppdir,'/v',@version,'/pom.xml')"/>

        <xsl:result-document method="xml" href="{$pomXmlfile}">
<project xmlns="http://maven.apache.org/POM/4.0.0" 
    xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" 
    xsi:schemaLocation="http://maven.apache.org/xsd/maven-4.0.0.xsd">
  <modelVersion>4.0.0</modelVersion>
  
  <groupId>com.jpw.x3g</groupId>
  <artifactId><xsl:value-of select="$name"/></artifactId>
  <version><xsl:value-of select="@version"/></version>
  <packaging>jar</packaging>

  <properties>
    <maven.compiler.source>1.8</maven.compiler.source>
    <maven.compiler.target>1.8</maven.compiler.target>
  </properties>

  <dependencies>
  <dependency  xmlns='http://maven.apache.org/POM/4.0.0'>
     <groupId>com.objsys</groupId>
     <artifactId>asn1rt</artifactId>
     <version><xsl:value-of select="$asn1ver"/></version>
  </dependency>
  
  <dependency  xmlns='http://maven.apache.org/POM/4.0.0'>
     <groupId>com.objsys</groupId>
     <artifactId>ber</artifactId>
     <version><xsl:value-of select="$asn1ver"/></version>
  </dependency>

  <dependency  xmlns='http://maven.apache.org/POM/4.0.0'>
     <groupId>com.objsys</groupId>
     <artifactId>per</artifactId>
     <version><xsl:value-of select="$asn1ver"/></version>
  </dependency>
  </dependencies>
</project>
        </xsl:result-document>
      </xsl:if>
    </xsl:template>

    <xsl:template match="/x3gpp/release" mode="year">
        <xsl:variable name="pomfile" select="concat($ppdir,'/y',@year,'/pom.xml')"/>
        <xsl:result-document method="xml" omit-xml-declaration="yes" href="{$pomfile}">
<project xmlns="http://maven.apache.org/POM/4.0.0" 
    xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" 
    xsi:schemaLocation="http://maven.apache.org/xsd/maven-4.0.0.xsd">
  <modelVersion>4.0.0</modelVersion>
  
  <groupId>com.jpw.x3g</groupId>
  <artifactId><xsl:value-of select="$name"/></artifactId>
  <version><xsl:value-of select="concat(number(substring(@year,3,2)),'.0.0')"/></version>
  <packaging>pom</packaging>
          
  <dependencies>
      <xsl:apply-templates mode="year"/>
  </dependencies>
</project>
        </xsl:result-document>
    </xsl:template>
    
    <xsl:template match="spec"  mode="year">
       <xsl:if test="number(@major) &gt; number($minVer)">
<dependency  xmlns='http://maven.apache.org/POM/4.0.0'>
  <groupId>com.jpw.x3g</groupId>
  <artifactId><xsl:value-of select="$name"/></artifactId>
  <version><xsl:value-of select="@version"/></version>
</dependency>
       </xsl:if>
    </xsl:template>

</xsl:stylesheet>
