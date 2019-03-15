<?xml version="1.0"?>
<!--  
   convert xml to x.proto for protobuf: - for double-.
   @See https://developers.google.com/protocol-buffers/docs/proto3
   1. not support nested messages
   2. not support oneof

   protoc -proto_path=IMPORT_PATH # path to look for .proto files
          -cpp_out=DST_DIR 
          -java_out=DST_DIR 
          -python_out=DST_DIR 
          -go_out=DST_DIR 
          -ruby_out=DST_DIR 
          -objc_out=DST_DIR 
          -csharp_out=DST_DIR path/to/file.proto
 -->
<xsl:stylesheet version="2.0"
   xmlns:cpw="http://www.cpw.com/app"
   xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
   exclude-result-prefixes="cpw">

   <xsl:output method="xml" indent="yes"/>
	<xsl:strip-space  elements="*"/>

<xsl:template match="/">
    <xsl:apply-templates/>
</xsl:template>

<xsl:template match="HTML">
   <k8s version="1.13">
    <xsl:apply-templates/>
    </k8s>
</xsl:template>

<xsl:template match="BODY">
    <xsl:apply-templates/>
</xsl:template>

<xsl:template match="DIV[@id='sidebar-wrapper']">
<!-- 
   <overview>
       <xsl:apply-templates mode="overview"/>
   </overview>
-->
</xsl:template>

<xsl:template match="DIV/UL" mode="overview">
    <resource>
        <xsl:apply-templates mode="overview"/>
    </resource>
</xsl:template>

<xsl:template match="DIV/UL/LI" mode="overview">
    <xsl:if test="count(A)=1">
        <xsl:choose>
           <xsl:when test="count(A[1]/STRONG)=1">
               <group><xsl:value-of select="A[1]/STRONG[1]/text()"/></group>
           </xsl:when>
           <xsl:otherwise>
               <name><xsl:value-of select="A[1]/text()"/></name>
               <!-- href -->
               
           </xsl:otherwise>
        </xsl:choose>
    </xsl:if>
</xsl:template>

<xsl:template match="DIV/UL/UL" mode="overview">
    <xsl:apply-templates mode="overview"/>
</xsl:template>

<xsl:template match="DIV/UL/UL/LI" mode="overview">
    <xsl:if test="count(A)=1">
       <definition><xsl:value-of select="A[1]/text()"/></definition>
    </xsl:if>
</xsl:template>

<xsl:template match="DIV/UL/UL/UL" mode="overview">
    <xsl:if test="count(LI/A/STRONG)=1">
       <operations name="{LI/A/STRONG[1]/text()}">
          <xsl:apply-templates select="UL/LI" mode="overview"/>
       </operations>
    </xsl:if>
</xsl:template>

<xsl:template match="DIV/UL/UL/UL/UL/LI" mode="overview">
    <operation name="{A[1]/text()}"  href="{A[1]/@href}"/>
</xsl:template>


<!--  xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx -->
<xsl:template match="DIV[@id='wrapper']">
    <content>
       <xsl:apply-templates select="DIV"/>
    </content>
</xsl:template>

<xsl:template match="DIV/DIV">
    <xsl:choose>
       <xsl:when test="@class='panel-body'"></xsl:when>
       <xsl:when test="@class='panel-heading'"></xsl:when>
       <xsl:otherwise><xsl:apply-templates/></xsl:otherwise>
    </xsl:choose>
</xsl:template>
<xsl:template match="I"></xsl:template> 
<xsl:template match="H1">
    <xsl:choose>
        <xsl:when test="count(STRONG)=1">
            <h1res name="{STRING[1]/text()}"/>
        </xsl:when>
        <xsl:otherwise>
            <h1res name="{text()}"/>
        </xsl:otherwise>
    </xsl:choose>
</xsl:template>
<xsl:template match="H2">
    <xsl:choose>
        <xsl:when test="count(STRONG)=1">
            <h2res name="{STRING[1]/text()}"/>
        </xsl:when>
        <xsl:otherwise>
            <h2res name="{text()}"/>
        </xsl:otherwise>
    </xsl:choose>
</xsl:template>
<xsl:template match="H3">
    <xsl:choose>
        <xsl:when test="count(STRONG)=1">
            <h3res name="{STRING[1]/text()}"/>
        </xsl:when>
        <xsl:otherwise>
            <h3res name="{text()}"/>
        </xsl:otherwise>
    </xsl:choose>
</xsl:template>

<xsl:template match="TABLE">  <!--  siblining H1/H3 -->
    <xsl:variable name="name" select="preceding-sibling::H1[1]/text()"/>
    <xsl:choose>
        <xsl:when test="count(THEAD/TR/TH)=2">  <!--  Field:Description: parameters -->
            <resourceid name="{$name}">
               <xsl:apply-templates select="TBODY/TR" mode="arg"/>
            </resourceid>
        </xsl:when>
        <xsl:when test="count(THEAD/TR/TH)=3">  <!--  Group:Version:Kind -->
            <resource name="{$name}">
               <xsl:apply-templates select="TBODY/TR" mode="res"/>
            </resource>
        </xsl:when>
    </xsl:choose>
</xsl:template>

<xsl:template match="TR" mode="arg">
    <arg name="{TD[1]/CODE[1]/text()}" type="{TD[1]/I[1]/text()}">
       <desc><xsl:value-of select="TD[2]/text()"/></desc>
    </arg>
</xsl:template>

<xsl:template match="TR" mode="res">
    <type group="{TD[1]/CODE[1]/text()}" version="{TD[2]/CODE[1]/text()}" kind="{TD[3]/CODE[1]/text()}"/>
</xsl:template>

<!-- <H2 id="create-secret-v1-core">Create</H2>: operations -->

<xsl:template match="*">
</xsl:template>

<xsl:function name="cpw:getName">
    <xsl:param name="node"/>
    <xsl:if test="$node/@public"> public </xsl:if>
</xsl:function>

<xsl:function name="cpw:ucfirst">
    <xsl:param name="name"/>
    <xsl:value-of select="concat(upper-case(substring($name,1,1)), substring($name, 2))"/>
 </xsl:function>
</xsl:stylesheet>
