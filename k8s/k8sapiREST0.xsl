<xsl:stylesheet
    xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
    xmlns:xs="http://www.w3.org/2001/XMLSchema"
    xmlns:cpw="http://www.jpw.com/product/app/cxx"
    exclude-result-prefixes="cpw xs"
    version="2.0">

    <xsl:output method="xml" indent="yes"/>
    <xsl:strip-space elements="*"/>
    <xsl:param name="text-encoding" select="'iso-8859-1'"/>

    <xsl:template match="/">
        <xsl:apply-templates/>
    </xsl:template>

    <xsl:template match="k8sapi">
<k8sapi version="{@version}" date="{@date}" type="rest">
           <xsl:apply-templates/>
</k8sapi>
    </xsl:template>
 
    <xsl:template match="group"> 
       <xsl:copy-of select="."/>
    </xsl:template>
    
    <xsl:template match="operations"> 
        <xsl:variable name="node" select="preceding-sibling::group[1]"/>
<operations>
     <xsl:attribute name="group"><xsl:value-of select="$node/@name"/></xsl:attribute>
     <xsl:for-each select="@*"> <!--  all attributes -->
        <xsl:copy-of select="."/>
     </xsl:for-each>
</operations>
    </xsl:template>

    <xsl:template match="operation">  <!--  Following: request; path/query/body parameters; response -->
       <xsl:variable name="grpname" select="preceding-sibling::group[1]/@name"/>
       <xsl:variable name="opsname" select="preceding-sibling::operations[1]/@name"/>
       <xsl:variable name="requestName" select="following-sibling::*[1]/@name"/>
       
       <xsl:choose>
          <xsl:when test="$requestName='HTTP Request'">
<operation group="{$grpname}" operations="{$opsname}">
     <xsl:for-each select="@*">
        <xsl:copy-of select="."/>
     </xsl:for-each>
     <xsl:call-template name="handleOperation">
         <xsl:with-param name="desc" select="following-sibling::*[1]"/>
         <xsl:with-param name="node" select="following-sibling::*[2]"/>
     </xsl:call-template>
     <xsl:call-template name="handleOperation">
        <xsl:with-param name="desc" select="following-sibling::*[3]"/>
        <xsl:with-param name="node" select="following-sibling::*[4]"/>
     </xsl:call-template>
     <xsl:call-template name="handleOperation">
        <xsl:with-param name="desc" select="following-sibling::*[5]"/>
        <xsl:with-param name="node" select="following-sibling::*[6]"/>
     </xsl:call-template>
     <xsl:call-template name="handleOperation">
        <xsl:with-param name="desc" select="following-sibling::*[7]"/>
        <xsl:with-param name="node" select="following-sibling::*[8]"/>
     </xsl:call-template>
     <xsl:call-template name="handleOperation">
        <xsl:with-param name="desc" select="following-sibling::*[9]"/>
        <xsl:with-param name="node" select="following-sibling::*[10]"/>
     </xsl:call-template>
</operation>
          </xsl:when>
          
          <xsl:otherwise>
             <xsl:message>Improper operation:<xsl:value-of select="@id"/></xsl:message>
          </xsl:otherwise>
       </xsl:choose>
    </xsl:template>
 
    <xsl:template match="*">
    </xsl:template>

   <xsl:template name="handleOperation">
       <xsl:param name="desc"/>
       <xsl:param name="node"/>

       <xsl:choose>
          <xsl:when test="name($desc)='h3' and name($node)='request' and $desc/@name='HTTP Request'">
              <xsl:copy-of select="$node"/>
          </xsl:when>
          
          <xsl:when test="name($desc)='h3' and name($node)='response' and $desc/@name='Response'">
              <xsl:copy-of select="$node"/>
          </xsl:when>
          
          <xsl:when test="name($desc)='h3' and name($node)='parameter' and $desc/@name='Path Parameters'" >
    <path>
        <xsl:for-each select="$node/*"><xsl:copy-of select="."/></xsl:for-each>
    </path>
          </xsl:when>
          
          <xsl:when test="name($desc)='h3' and name($node)='parameter' and $desc/@name='Query Parameters'" >
    <query>
        <xsl:for-each select="$node/*"><xsl:copy-of select="."/></xsl:for-each>
    </query>
          </xsl:when>
          
          <xsl:when test="name($desc)='h3' and name($node)='parameter' and $desc/@name='Body Parameters'" >
    <body>
        <xsl:for-each select="$node/*"><xsl:copy-of select="."/></xsl:for-each>
    </body>
          </xsl:when>
          
          <xsl:otherwise>
              <xsl:message>not handled: <xsl:value-of select="concat(name($desc), ':', $desc/@name, '; ', name($node) )"/></xsl:message>
          </xsl:otherwise>
       </xsl:choose>
   </xsl:template>

</xsl:stylesheet>
