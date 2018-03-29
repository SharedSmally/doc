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
    <xsl:variable name="category" select="/x3gpp/@category"/>
    <xsl:variable name="coding" select="/x3gpp/@coding"/>
    <xsl:variable name="pkgname" select="concat('com.jpw.x3gpp.',$name)"/>
    <xsl:variable name="pkgdir" select="replace($pkgname,'.','/')"/>
    
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
        <xsl:variable name="mkfile" 
              select="concat($ppdir,'/v',@version,'/makefile')"/>
        <xsl:variable name="docfile" select="replace(@name, '.zip', '.doc')"/> 
        <xsl:variable name="docdir" select="concat('${X3G_DOC_DIR}/', $name, '/v', @version,'/')"/>
        <xsl:variable name="zipfile" select="concat('${X3G_ZIP_DIR}/', $name, '/', @name)"/>
        
        <xsl:result-document method="text" href="{$mkfile}">
include ../../../x3gpp.cfg

main: init gen
	
init:
	@mkdir -p meta

<xsl:choose>
<xsl:when test="$category = 'asn1'">
gen:meta/<xsl:value-of select="$name"/>.asn1
	${ASN1_COMPILER_OPTIONS} java -p <xsl:value-of select="$pkgname"/> ${ASN1_JAVA_OPTIONS}
	${ASN1_COMPILER_OPTIONS} c++ -p <xsl:value-of select="$pkgname"/> ${ASN1_CXX_OPTIONS}
	${ASN1_XSDCOMPILER_OPTIONS} xsd -p <xsl:value-of select="$pkgname"/> ${ASN1_XSD_OPTIONS}
	
<xsl:value-of select="concat('meta/',$name,'.asn1 : ', $docdir, $docfile)"/>
	@mkdir -p meta/
	cp $&lt; $@
	#../../../bin/asn1.pl $&lt; $@
	
</xsl:when>

<xsl:when test="$category = 'xsd'">
gen:meta/<xsl:value-of select="$name"/>.xsd
	
<xsl:value-of select="concat('meta/',$name,'.xsd : ', $docdir, $docfile)"/>
	@mkdir -p meta/
	cp $&lt; $@
</xsl:when>

<xsl:when test="$category = 'wsdl'">
gen:meta/<xsl:value-of select="$name"/>.wsdl
		
<xsl:value-of select="concat('meta/',$name,'.wsdl : ', $docdir, $docfile)"/>
	@mkdir -p meta/
	cp $&lt; $@
	#../../../bin/asn1.pl $&lt; $@
</xsl:when>

<xsl:when test="$category = 'diameter'">
gen:meta/<xsl:value-of select="$name"/>.asn1
	
<xsl:value-of select="concat('meta/',$name,'.asn1 : ', $docdir, $docfile)"/>
	@mkdir -p meta/
	cp $&lt; $@
	#../../../bin/asn1.pl $&lt; $@
</xsl:when>

</xsl:choose>

<xsl:value-of select="concat( $docdir, $docfile, ' : ', $zipfile)"/>
	@mkdir -p <xsl:value-of select="$docdir"/> 
	unzip $&lt; -d <xsl:value-of select="concat($docdir,$newline,$newline)"/>
	
<xsl:value-of select="$zipfile"/>:
	wget <xsl:value-of select="concat($site,@url)"/> -q -O $@

package:
	mvn package
	
deploy:package
	mvn deploy
	
clean:
	mvn clean
	
cleanall:clean
	${RM} -rf meta/

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
