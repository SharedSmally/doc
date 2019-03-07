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
   xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

   <xsl:output method="text"/>
	<xsl:strip-space  elements="*"/>
	
<xsl:variable name='newline'><xsl:text>
</xsl:text></xsl:variable>
<xsl:variable name='newline2'><xsl:text>

</xsl:text></xsl:variable>
<xsl:variable name='spaces'><xsl:text>    </xsl:text></xsl:variable>


<xsl:template match="/">
    <xsl:apply-templates/>
</xsl:template>

<xsl:template match="protocol">
    <xsl:choose>
        <xsl:when test="@version='2'">syntax = "proto2";</xsl:when>
        <xsl:when test="@version='3'">syntax = "proto3";</xsl:when>
        <xsl:otherwise>syntax = "proto3";</xsl:otherwise>
    </xsl:choose>
    <xsl:if test="@package"><xsl:value-of select="concat($newline2,'package ',@package,';',$newline)"/></xsl:if>
    <xsl:apply-templates/>
</xsl:template>

<xsl:template match="import">
    <xsl:variable name="public" select="cpw:getPublic(.)"/>
    <xsl:variable name="prefix" select="@prefix"/>
    <xsl:variable name="suffix" select="cpw:getSuffix(.)"/>
    <xsl:variable name="names" select="normalize-space(text())"/>
    
    <xsl:if test="@name"><xsl:value-of select="concat($spaces, 'import &quot;', $prefix, normalize-space(@name), $suffix, '&quot;;', $newline)"/></xsl:if>
    <xsl:for-each select="tokenize($names)">
<xsl:value-of select="concat($spaces,'import &quot;', $prefix, normalize-space(.), $suffix, '&quot;;', $newline)"/>
    </xsl:for-each>
</xsl:template>

<!-- 
options target="java"
  option name="" value=""
 -->
<xsl:template match="options">
    <xsl:variable name="target" select="@target"/>
<xsl:value-of select="$newline"/>
    <xsl:for-each select="option">
<xsl:value-of select="concat($target,'_',@name,' = ', @value,$newline)"/>
    </xsl:for-each>
</xsl:template>

<xsl:template match="message">
message <xsl:value-of select="cpw:ucfirst(@name)"/> {
<xsl:apply-templates select="field"/>}
</xsl:template>

<xsl:template match="enum">
enum <xsl:value-of select="cpw:ucfirst(@name)"/> {
<xsl:if test="@alias"><xsl:value-of select="concat($spaces,'option allow_alias = true; ',$newline)"/></xsl:if>
<xsl:apply-templates select="value"/>
<xsl:apply-templates select="reserved"/>}
</xsl:template>

<xsl:template match="service">
service <xsl:value-of select="@name"/> {
   <xsl:apply-templates select="method"/>
}
</xsl:template>

<xsl:template match="field">
    <xsl:variable name="tag" select="cpw:getTag(.)"/>
    <xsl:variable name="prefix" select="cpw:getTypePrefix(.)"/>
    <xsl:variable name="type" select="cpw:getType(.)"/>
    <xsl:variable name="suffix" select="cpw:getDeprecated(.)"/>
    <xsl:variable name="names" select="normalize-space(text())"/>

    <xsl:message>tag=<xsl:value-of select="$tag"/></xsl:message>
    
    <xsl:choose>
        <xsl:when test="@name"><xsl:value-of select="concat($spaces, $prefix,$type, ' ', normalize-space(@name), ' = ', $tag, $suffix, ';', $newline)"/></xsl:when>
        <xsl:otherwise>
           <xsl:for-each select="tokenize($names)">
<xsl:value-of select="concat($spaces, $prefix, $type, ' ', normalize-space(.), ' = ', $tag+position()-1, $suffix, ';', $newline)"/>
           </xsl:for-each>
        </xsl:otherwise>    
    </xsl:choose>
</xsl:template>

<xsl:template match="value">
    <xsl:variable name="tag" select="cpw:getValueTag(.)"/>
    <xsl:variable name="names" select="normalize-space(text())"/>

    <xsl:message>enum tag=<xsl:value-of select="$tag"/></xsl:message>
    
    <xsl:choose>
        <xsl:when test="@name"><xsl:value-of select="concat($spaces, upper-case(normalize-space(@name)), ' = ', $tag, ';', $newline)"/></xsl:when>
        <xsl:otherwise>
           <xsl:for-each select="tokenize($names, ',')">
<xsl:value-of select="concat($spaces, upper-case(normalize-space(.)), ' = ', $tag+position()-1, ';', $newline)"/>
           </xsl:for-each>
        </xsl:otherwise>    
    </xsl:choose>
</xsl:template>

<xsl:template match="method">
    <xsl:value-of select="concat($spaces,'rpc', ' ', @name, '(', @arg,') returns (', @return, ');')"/>
</xsl:template>

<xsl:template match="*"></xsl:template>

<xsl:function name="cpw:getType">
    <xsl:param name="node"/>
    <xsl:choose>
        <xsl:when test="$node/@type"><xsl:value-of select="$node/@type"/></xsl:when>
        <xsl:when test="$node/@map"><xsl:value-of select="concat('map &lt;',$node/@map,'&gt;')"/></xsl:when>
        <xsl:otherwise><xsl:value-of select="'google.protobuf.Any'"/></xsl:otherwise>
    </xsl:choose>
</xsl:function>

<xsl:function name="cpw:getTypePrefix">
    <xsl:param name="node"/>
    <xsl:choose>
        <xsl:when test="$node/@size='1'"><xsl:value-of select="'required '"/></xsl:when>
        <xsl:when test="$node/@size='n'"><xsl:value-of select="'repeated '"/></xsl:when>
        <xsl:when test="$node/@size='m'"><xsl:value-of select="'repeated '"/></xsl:when>
    </xsl:choose>
</xsl:function>

<xsl:function name="cpw:getTag">
    <xsl:param name="node"/>

    <xsl:choose>
       <xsl:when test="$node/@tag">
          <xsl:value-of select="$node/@tag"/>
       </xsl:when>
       <xsl:when test="count($node/preceding-sibling::field)=0">
          <xsl:value-of select="'1'"/>
       </xsl:when>
       <xsl:otherwise>
          <xsl:variable name="pnode" select="$node/preceding-sibling::field[1]"/>
          <xsl:variable name="cnt" select="count(tokenize(normalize-space($pnode/text())))"/>
          <xsl:choose>
              <xsl:when test="$pnode/@name"><xsl:value-of select="cpw:getTag($pnode)+1"/></xsl:when>
              <xsl:otherwise>
                  <xsl:value-of select="cpw:getTag($pnode)+$cnt"/>
              </xsl:otherwise>
          </xsl:choose>
       </xsl:otherwise>
    </xsl:choose>
</xsl:function>

<!-- [deprecated=true] -->
<xsl:function name="cpw:getDeprecated">
    <xsl:param name="node"/>
    <xsl:if test="$node/@deprecated"> [deprecated=true] </xsl:if>
</xsl:function>
       

<xsl:function name="cpw:getValueTag">
    <xsl:param name="node"/>
    
    <xsl:choose>
       <xsl:when test="$node/@tag">
          <xsl:value-of select="$node/@tag"/>
       </xsl:when>
       <xsl:when test="count($node/preceding-sibling::value)=0">
          <xsl:value-of select="'0'"/>
       </xsl:when>
       <xsl:otherwise>
          <xsl:variable name="pnode" select="$node/preceding-sibling::value[1]"/>
          <xsl:variable name="cnt" select="count(tokenize(normalize-space($pnode/text())))"/>
          <xsl:choose>
              <xsl:when test="$pnode/@name"><xsl:value-of select="cpw:getValueTag($pnode)+1"/></xsl:when>
              <xsl:otherwise>
                  <xsl:value-of select="cpw:getValueTag($pnode)+$cnt"/>
              </xsl:otherwise>
          </xsl:choose>
       </xsl:otherwise>
    </xsl:choose>
</xsl:function>

<xsl:function name="cpw:getPublic">
    <xsl:param name="node"/>
    <xsl:if test="$node/@public"> public </xsl:if>
</xsl:function>

<xsl:function name="cpw:getSuffix">
    <xsl:param name="node"/>
    <xsl:choose>
        <xsl:when test="$node/@suffix"><xsl:value-of select="$node/@suffix"/></xsl:when>
        <xsl:otherwise>.proto</xsl:otherwise>
    </xsl:choose>
</xsl:function>

<xsl:function name="cpw:ucfirst">
    <xsl:param name="name"/>
    <xsl:value-of select="concat(upper-case(substring($name,1,1)), substring($name, 2))"/>
 </xsl:function>
</xsl:stylesheet>
