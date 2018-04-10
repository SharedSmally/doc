<xsl:stylesheet
    xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
    xmlns:jpw="http://www.jpw.com/product/app"
    exclude-result-prefixes="jpw"
    version="2.0">

    <xsl:output method="xml" indent="yes"/>
    <xsl:strip-space elements="*"/>

    <xsl:template match="/smpp">
<x3dia version="15.2.0">
        <xsl:apply-templates />
</x3dia>
    </xsl:template>

    <xsl:template match="table">
        <xsl:variable name="name" select="normalize-space(substring-before(@name,':'))"/>
        <xsl:variable name="desc" select="normalize-space(substring-after(@name,':'))"/>
        <xsl:variable name="type" select="jpw:getType(.)"/>
        <xsl:if test="string-length($type) &gt; 0">
<table name="{$name}" desc="{$desc}" type="{$type}">
       <xsl:choose>
           <xsl:when test="$type = 'AppID'">
               <xsl:apply-templates select="row[position()>1]" mode="appId"/>
           </xsl:when>
           <xsl:when test="$type = 'CmdCode'">
               <xsl:apply-templates select="row[position()>1]" mode="cmdCode"/>
           </xsl:when>
           <xsl:when test="$type = 'AvpCode'">
               <xsl:apply-templates select="row[position()>1]" mode="avpCode"/>
           </xsl:when>
           <xsl:when test="$type = 'ResCode'">
               <xsl:apply-templates select="row[position()>1]" mode="resCode"/>
           </xsl:when>
        </xsl:choose>
</table>
        </xsl:if>
    </xsl:template>

    <xsl:template match="row" mode="appId">
        <xsl:variable name="id" select="jpw:trim(column[1]/text())"/>
        <xsl:variable name="name" select="jpw:getAppName(column[2]/text())"/>
<application id="{$id}" name="{$name}">
         <xsl:call-template name="ts">
            <xsl:with-param name="text" select="normalize-space(column[3]/text())"/>
         </xsl:call-template>
</application>
    </xsl:template>

    <xsl:template match="row" mode="cmdCode">
        <xsl:variable name="code" select="jpw:trim(column[1]/text())"/>
        <xsl:variable name="name" select="jpw:trim(column[2]/text())"/>
        <xsl:variable name="sname" select="jpw:trim(column[3]/text())"/>
<command code="{$code}" name="{$name}" sname="{$sname}">
         <xsl:call-template name="ts">
            <xsl:with-param name="text" select="normalize-space(column[4]/text())"/>
         </xsl:call-template>
</command>
    </xsl:template>

    <xsl:template match="row" mode="avpCode">
        <xsl:variable name="code" select="jpw:trim(column[1]/text())"/>
        <xsl:variable name="name" select="jpw:trim(column[2]/text())"/>
        <xsl:variable name="type" select="jpw:trim(column[3]/text())"/>
        <xsl:variable name="ts" select="jpw:getTS(column[4]/text())"/>
        <xsl:if test="not(starts-with($code, 'Note'))">
<avp code="{$code}" name="{$name}" type="{$type}" />
        </xsl:if>
    </xsl:template>

    <xsl:template match="row" mode="resCode">
        <xsl:variable name="code" select="jpw:trim(column[1]/text())"/>
        <xsl:variable name="txt" select="jpw:trim(column[2]/text())"/>
        <xsl:variable name="ts" select="jpw:getTS(column[3]/text())"/>
        <xsl:if test="not(starts-with($code, 'Note'))">
<result code="{$code}" text="{$txt}"/>
        </xsl:if>
    </xsl:template>

    <xsl:template match="*"/>

    <xsl:template name="ts">
         <xsl:param name="text"/>
         <xsl:variable name="val" select="normalize-space(jpw:getTS($text))"/>
         <xsl:choose>
             <xsl:when test="string-length($val)>0">
                 <xsl:attribute name="ts"><xsl:value-of select="$val"/></xsl:attribute>
             </xsl:when>
         </xsl:choose>
    </xsl:template>

    <xsl:function name="jpw:getType">
       <xsl:param name="node"/>
       <xsl:variable name="txt" select="$node/row[1]/column[1]/text()"/>
       <xsl:choose>
           <!-- Application identifier  -->
           <xsl:when test="starts-with($txt, 'Application')">
               <xsl:value-of select="'AppID'"/>
           </xsl:when>
           <!-- Command code value -->
           <xsl:when test="starts-with($txt, 'Command')">
               <xsl:value-of select="'CmdCode'"/>
           </xsl:when>
           <!-- AVP Code  -->
           <xsl:when test="starts-with($txt, 'AVP')">
               <xsl:value-of select="'AvpCode'"/>
           </xsl:when>
           <!--  Experimental Result Code -->
           <xsl:when test="starts-with($txt, 'Experimental')">
               <xsl:value-of select="'ResCode'"/>
           </xsl:when>
       </xsl:choose>
    </xsl:function>

    <xsl:function name="jpw:trim">
       <xsl:param name="name"/>
       <xsl:value-of select="replace(normalize-space($name),' ','')"/>
    </xsl:function>

    <xsl:function name="jpw:getAppName">
       <xsl:param name="name"/>
       <xsl:variable name="name1" select="substring-after(normalize-space($name), '3GPP ')"/>
       <xsl:variable name="name1" select="substring-after(normalize-space($name), '3GPP ')"/>
       <xsl:variable name="name2" select="replace($name1, ' ', '')"/>
       <xsl:variable name="name3" select="replace($name2, '-', '')"/>
       <xsl:variable name="name" select="replace($name3, '/', '_')"/>
       <xsl:value-of select="$name"/>
    </xsl:function>

    <xsl:function name="jpw:getTS">
       <xsl:param name="name"/>
       <xsl:variable name="str" select="jpw:getTSStrings($name)"/>
       <xsl:value-of select="$str"/>
    </xsl:function>

    <xsl:function name="jpw:getTSStrings">
       <xsl:param name="name"/>
       <xsl:for-each select="tokenize($name, ' and ')">
            <xsl:value-of select="concat(substring-before(., '['), ' ')"/>
       </xsl:for-each>
    </xsl:function>
</xsl:stylesheet>
