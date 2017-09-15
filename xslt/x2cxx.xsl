<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet version="2.0" 
    xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
    xmlns:app="http://www.cpw.com/xml/app"
    >
    <xsl:output method="xml" version="1.0" encoding="UTF-8" indent="yes"/>
    <xsl:param name="lang" select="'cxx'" />
    
    <!--  command-line parameters -->
    <!-- base directory by base=src:  header in include/xxx; c++ in libsrc/xxx -->
    <xsl:param name="base" select="'src'" />
    <!-- type reference by refs=xxx. default is types.xml -->
    <xsl:param name="refs" select="'types.xml'" />
    
    <xsl:variable name="types" select="document(document($refs)/typedef/ref/@file)//typedef/types[@lang=$lang]/type" />
    
<xsl:template match="/">
    <xsl:message select="concat('generate code for ',$lang)"/>
    <xsl:message select="concat('base directory:',$base)"/>
    <xsl:message select="concat('types ref:',$refs)"/>
    <xsl:apply-templates/>
</xsl:template>

<xsl:template match="define">
  <xsl:variable name="ns" select="@namespace" />
  <xsl:variable name="hxxdir" select="app:nspath(concat($base, '/include/'),$ns)" />
  <xsl:variable name="cxxdir" select="app:nspath(concat($base, '/libsrc/'),$ns)" />
    
  <xsl:for-each select="message">
    <xsl:variable name="hxxfile" select="concat($hxxdir, '/', ./@name, '.h')" />
    <xsl:message select="concat('generate hxx file: ',$hxxfile)"/>
    <xsl:result-document method="text" href="{$hxxfile}">
      <xsl:apply-templates mode="header"/>
    </xsl:result-document>
 
    <xsl:variable name="cxxfile" select="concat($nsdir, '/', ./@name, '.cc')" />
    <xsl:message select="concat('generate cxx file: ',$cxxfile)"/>
    <xsl:result-document method="text" href="{$cxxfile}">
      <xsl:apply-templates mode="cxx"/>
    </xsl:result-document>
  </xsl:for-each>
</xsl:template>

<!--  generate *.h -->
<xsl:template match="message" mode="header">
     <xsl:apply-templates mode="import-types"/>
</xsl:template>


<xsl:template match="message" mode="import-types">
   <xsl:message select="concat('&#xa;','message=',@name)"/>
   <xsl:for-each-group select="./elem" group-by="./@type">
     <xsl:message select="concat('element: name=',@name,'; type=',@type)"/>
     <xsl:variable name="typeStr" select="@type"/>
     <xsl:apply-templates select="$types[@name=$typeStr]" mode="import"/>
   </xsl:for-each-group>
</xsl:template>

<!--  generate *.cc -->
<xsl:template match="message" mode="cxx">
   <xsl:message select="concat('&#xa;','message=',@name)"/>
   <xsl:for-each-group select="./elem" group-by="./@type">
     <xsl:message select="concat('element: name=',@name,'; type=',@type)"/>
     <xsl:variable name="typeStr" select="@type"/>
     <xsl:apply-templates select="$types[@name=$typeStr]" mode="import"/>
     
     <!-- trick: change context node to external document  
     <xsl:for-each select="$types">
          <xsl:variable name="name" select="key('type-lookup',$type)"/>
          <xsl:if test="position()=1">
              <xsl:apply-templates select="$name" mode="import"/>
          </xsl:if>
     </xsl:for-each>
     -->
   </xsl:for-each-group>
</xsl:template>

<xsl:template match="type" mode="import">
     <xsl:message select="concat('import name=',@name,'; type=',@type, ', include=', @include)"/>
</xsl:template>

<!--  switch namespace x.x.x to x/x/x -->
<xsl:function name = "app:nspath">
    <xsl:param name="basedir" />
    <xsl:param name="ns" />
    <xsl:variable name="nsdir" select="replace($ns,'\.','/')" />
    <xsl:choose>
        <xsl:when test="$basedir and ends-with($basedir,'/')">
             <xsl:value-of select="concat($basedir,$nsdir)"/>
        </xsl:when>
        <xsl:when test="$basedir and not(ends-with($basedir,'/'))">
             <xsl:value-of select="concat($basedir,'/',$nsdir)"/>
        </xsl:when>
        <xsl:otherwise>
             <xsl:value-of select="$nsdir"/>
        </xsl:otherwise>
    </xsl:choose>
</xsl:function>
 
</xsl:stylesheet>
