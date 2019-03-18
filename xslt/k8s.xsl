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
       <xsl:when test="contains(text()[1],'Appears In:')">
          <xsl:variable name="name" select="preceding-sibling::*[local-name()='H1' or local-name()='H3'][1]/text()"/>
          <appear name="{$name}">
             <xsl:value-of select="string-join(UL/LI/a/text(),'; ')"/>
          </appear>
       </xsl:when>  <!-- Appears in -->
       <xsl:when test="count(a)>0"></xsl:when><!--  Other API versions of this object exist: -->
       <xsl:otherwise><xsl:apply-templates/></xsl:otherwise>
    </xsl:choose>
</xsl:template>
<xsl:template match="I"></xsl:template> 
<xsl:template match="H1">
    <xsl:choose>
        <xsl:when test="count(STRONG)=1">
            <h1res name="{STRONG[1]/text()}" strong="true"/>
        </xsl:when>
        <xsl:otherwise>
            <h1res name="{text()}"/>
        </xsl:otherwise>
    </xsl:choose>
</xsl:template>
<xsl:template match="H2">
    <xsl:variable name="h2next" select="following-sibling::*[1]"/>
    <!-- P: desc -->
    <xsl:choose>
        <xsl:when test="count(STRONG)=1">
            <h2res name="{STRONG[1]/text()}" strong="true">
            <xsl:call-template name="getInfo">
              <xsl:with-param name="node" select = "$h2next" />
            </xsl:call-template>
            </h2res>
        </xsl:when>
        <xsl:when test="@id">
            <h2res name="{text()}" id="{@id}">
            <xsl:call-template name="getInfo">
              <xsl:with-param name="node" select = "$h2next" />
            </xsl:call-template>
            </h2res>
        </xsl:when>
        <xsl:otherwise>
            <h2res name="{text()}">
            <xsl:call-template name="getInfo">
              <xsl:with-param name="node" select = "$h2next" />
            </xsl:call-template>
            </h2res>
        </xsl:otherwise>
    </xsl:choose>
</xsl:template>

<xsl:template match="H3">
    <xsl:variable name="h3next" select="following-sibling::*[1]"/>
    <!-- CODE:request format  --> 
    <xsl:choose>
        <xsl:when test="count(STRONG)=1">
            <h3res name="{STRONG[1]/text()}" strong="true">
            <xsl:call-template name="getInfo">
              <xsl:with-param name="node" select = "$h3next" />
            </xsl:call-template>
            </h3res>
        </xsl:when>
        <xsl:when test="@id">
            <h3res name="{text()}" id="{@id}">
            <xsl:call-template name="getInfo">
              <xsl:with-param name="node" select = "$h3next" />
            </xsl:call-template>
            </h3res>
        </xsl:when>
        <xsl:otherwise>
            <h3res name="{text()}">
            <xsl:call-template name="getInfo">
              <xsl:with-param name="node" select = "$h3next" />
            </xsl:call-template>
            </h3res>
        </xsl:otherwise>
    </xsl:choose>
</xsl:template>

<xsl:template match="TABLE">  <!--  siblining of H1/H3 for Group/Version/Kind or Field/Desc  or Parameter/Desc -->
    <xsl:variable name="name" select="preceding-sibling::*[local-name()='H1' or local-name()='H3'][1]/text()"/>
    <xsl:choose>
        <xsl:when test="count(THEAD/TR/TH)=2 and THEAD/TR/TH[1]/text()='Field'">  <!--  Field:Description -->
            <resource name="{$name}">
               <xsl:apply-templates select="TBODY/TR" mode="arg"/>
            </resource>
        </xsl:when>

        <xsl:when test="count(THEAD/TR/TH)=2 and THEAD/TR/TH[1]/text()='Parameter'" >  <!--  Http Request: Parameter/Description -->
            <request name="{$name}">
               <xsl:apply-templates select="TBODY/TR" mode="request"/>
            </request>
        </xsl:when>

        <xsl:when test="count(THEAD/TR/TH)=2 and THEAD/TR/TH[1]/text()='Code'">  <!--  Http Response: Code/Description -->
            <response name="{$name}">
               <xsl:apply-templates select="TBODY/TR" mode="response"/>
            </response>
        </xsl:when>
        
        <xsl:when test="count(THEAD/TR/TH)=3">  <!-- Type: Group/Version/Kind -->
            <resourceid name="{$name}">
               <xsl:apply-templates select="TBODY/TR" mode="resid"/>
            </resourceid>
        </xsl:when>
        
        <xsl:otherwise>
            <xsl:message>Unknown table format</xsl:message>
        </xsl:otherwise>
    </xsl:choose>
</xsl:template>

<xsl:template match="TR" mode="arg">
    <arg name="{TD[1]/CODE[1]/text()}" >
       <xsl:choose>
          <xsl:when test="count(TD[1]/I[1]/a)=1">
             <xsl:attribute name="type" select="TD[1]/I[1]/a[1]/text()"/>
             <xsl:attribute name="ref" select="TD[1]/I[1]/a[1]/@href"/>
          </xsl:when>
          <xsl:otherwise>
             <xsl:attribute name="type" select="TD[1]/I[1]/text()"/>
          </xsl:otherwise>
       </xsl:choose>
       <desc><xsl:value-of select="TD[2]/text()"/></desc>
    </arg>
</xsl:template>


<xsl:template match="TR" mode="request">
    <param name="{TD[1]/CODE[1]/text()}" >
       <xsl:choose>
          <xsl:when test="count(TD[1]/I[1]/a)=1">
             <xsl:attribute name="type" select="TD[1]/I[1]/a[1]/text()"/>
             <xsl:attribute name="ref" select="TD[1]/I[1]/a[1]/@href"/>
          </xsl:when>
          <xsl:otherwise>
             <xsl:attribute name="type" select="TD[1]/I[1]/text()"/>
          </xsl:otherwise>
       </xsl:choose>
       <desc><xsl:value-of select="TD[2]/text()"/></desc>
    </param>
</xsl:template>

<xsl:template match="TR" mode="response">
    <code value="{TD[1]/text()}" >
       <xsl:choose>
          <xsl:when test="count(TD[1]/I[1]/a)=1">
             <xsl:attribute name="type" select="TD[1]/I[1]/a[1]/text()"/>
             <xsl:attribute name="ref" select="TD[1]/I[1]/a[1]/@href"/>
          </xsl:when>
          <xsl:otherwise>
             <xsl:attribute name="type" select="TD[1]/I[1]/text()"/>
          </xsl:otherwise>
       </xsl:choose>
       <desc><xsl:value-of select="TD[2]/text()"/></desc>
    </code>
</xsl:template>

<xsl:template match="TR" mode="resid">
    <type group="{TD[1]/CODE[1]/text()}" version="{TD[2]/CODE[1]/text()}" kind="{TD[3]/CODE[1]/text()}"/>
</xsl:template>




<!-- <H2 id="create-secret-v1-core">Create</H2>: operations -->

<xsl:template match="*">
</xsl:template>

<xsl:template name="getInfo">
    <xsl:param name="node"/>
    <xsl:choose>
        <xsl:when test="local-name($node)='P'">  <!--  <P>create a CronJob</P>    -->
            <desc><xsl:value-of select="$node/text()"/></desc>
        </xsl:when>  
        <xsl:when test="local-name($node)='CODE'"> <!--  <CODE>POST /apis/batch/v1beta1/namespaces/{namespace}/cronjobs</CODE>  -->
            <format><xsl:value-of select="$node/text()"/></format>
        </xsl:when>
    </xsl:choose>
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
