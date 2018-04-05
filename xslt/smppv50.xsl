<xsl:stylesheet 
    xmlns:xsl="http://www.w3.org/1999/XSL/Transform" 
    xmlns:xs="http://www.w3.org/2001/XMLSchema"
    xmlns:jpw="http://www.jpw.com/product/app"
    exclude-result-prefixes="jpw"
    version="2.0">

    <xsl:output method="xml" indent="yes"/>
    <xsl:strip-space elements="*"/>
    
    <xsl:template match="/">
<smpp version="5.0.0">
        <xsl:apply-templates select="smpp/table[position() &gt; 19]"/>
</smpp>
    </xsl:template>

    <xsl:template match="table">
       <xsl:choose>
           <xsl:when test="contains(@name, 'PDU')">
              <xsl:variable name="name" select="jpw:getName(@name)"></xsl:variable>
              <xsl:variable name="tbl" select="jpw:getTable(@name)"></xsl:variable>
              <xsl:if test="string-length($name) &gt; 1">
<pdu name="{$name}"  table="{$tbl}">
   <desc><xsl:value-of select="@desc"/></desc>
    <xsl:apply-templates mode="pdu"/>
</pdu>
              </xsl:if>
           </xsl:when>

           <xsl:when test="contains(@name, 'TLVs')">
              <xsl:variable name="name" select="jpw:getTlvName(@name)"></xsl:variable>
              <xsl:variable name="tbl" select="jpw:getTlvTable(@name)"></xsl:variable>
              <xsl:if test="string-length($name) &gt; 1">
<tlvs name="{$name}"  table="{$tbl}">
   <desc><xsl:value-of select="@desc"/></desc>
    <xsl:apply-templates mode="tlvs"/>
</tlvs>
              </xsl:if>
           </xsl:when>
           
           <xsl:when test="contains(@name, 'TLV')">
              <xsl:variable name="name" select="jpw:getTlvName(@name)"></xsl:variable>
              <xsl:variable name="tbl" select="jpw:getTlvTable(@name)"></xsl:variable>
              <xsl:if test="string-length($name) &gt; 1">
<tlv name="{$name}"  table="{$tbl}">
   <desc><xsl:value-of select="@desc"/></desc>
    <xsl:apply-templates mode="tlv"/>
</tlv>
              </xsl:if>
           </xsl:when>
           
           <xsl:when test="contains(@name, 'Values')">
              <xsl:variable name="name" select="jpw:getValuesName(@name)"></xsl:variable>
              <xsl:variable name="tbl" select="jpw:getValuesTable(@name)"></xsl:variable>
              <xsl:if test="string-length($name) &gt; 1">
<values name="{$name}"  table="{$tbl}">
   <desc><xsl:value-of select="@desc"/></desc>
    <xsl:apply-templates mode="values"/>
</values>
              </xsl:if>
           </xsl:when>

           <xsl:when test="contains(@name, 'Format')">
              <xsl:variable name="name" select="jpw:getValuesName(@name)"></xsl:variable>
              <xsl:variable name="tbl" select="jpw:getValuesTable(@name)"></xsl:variable>
              <xsl:if test="string-length($name) &gt; 1">
<format name="{$name}"  table="{$tbl}">
   <desc><xsl:value-of select="@desc"/></desc>
    <xsl:apply-templates mode="format"/>
</format>
              </xsl:if>
           </xsl:when>
           
       </xsl:choose>
    </xsl:template>
    
    <xsl:template match="row" mode="pdu">
        <xsl:if test="not(starts-with(column[1]/text(), 'Field Name'))">
            <xsl:variable name="name" select="normalize-space(column[1]/text())"/>
            <xsl:variable name="size" select="normalize-space(column[2]/text())"/>
            <xsl:variable name="type" select="normalize-space(column[3]/text())"/>
            <xsl:variable name="val" select="normalize-space(column[4]/text())"/>
            <xsl:variable name="ref"  select="normalize-space(column[5]/text())"/>
            <xsl:choose>
                <xsl:when test="starts-with($val, '0x')">
                    <field name="{$name}" size="{$size}" type="{$type}" value="{$val}" ref="{$ref}"/>
                </xsl:when>
                <xsl:otherwise>
                    <field name="{$name}" size="{$size}" type="{$type}" ref="{$ref}"><xsl:value-of select="$val"/></field>
                </xsl:otherwise>
            </xsl:choose>
        </xsl:if>
    </xsl:template>

    <xsl:template match="row" mode="tlvs">
       <xsl:choose>
         <xsl:when test="not(starts-with(column[1]/text(), 'TLV Name'))">
            <xsl:variable name="name" select="normalize-space(column[1]/text())"/>
            <xsl:variable name="desc" select="normalize-space(column[2]/text())"/>
            <xsl:variable name="ref" select="normalize-space(column[3]/text())"/>
            <field name="{$name}" ref="{$ref}"><xsl:value-of select="$desc"/></field>
         </xsl:when>
        </xsl:choose>
    </xsl:template>
    
    <xsl:template match="row" mode="tlv">
       <xsl:choose>
         <xsl:when test="not(starts-with(column[1]/text(), 'Field Size'))">
            <xsl:variable name="name" select="normalize-space(column[1]/text())"/>
            <xsl:variable name="size" select="normalize-space(column[2]/text())"/>
            <xsl:variable name="type" select="normalize-space(column[3]/text())"/>
            <xsl:variable name="val" select="normalize-space(column[4]/text())"/>
            <xsl:choose>
                <xsl:when test="starts-with($val, '0x')">
                    <field name="{$name}" size="{$size}" type="{$type}" value="{$val}"/>
                </xsl:when>
                <xsl:otherwise>
                    <field name="{$name}" size="{$size}" type="{$type}"><xsl:value-of select="$val"/></field>
                </xsl:otherwise>
            </xsl:choose>
         </xsl:when>
        </xsl:choose>
    </xsl:template>

    <xsl:template match="row" mode="values">
       <xsl:choose>
         <xsl:when test="not(starts-with(column[1]/text(), 'Message'))">
            <xsl:variable name="name" select="normalize-space(column[1]/text())"/>
            <xsl:variable name="value" select="normalize-space(column[2]/text())"/>
            <xsl:variable name="desc" select="normalize-space(column[3]/text())"/>
            <field name="{$name}" value="{$value}"><xsl:value-of select="$desc"/></field>
         </xsl:when>
        </xsl:choose>
    </xsl:template>

    <xsl:template match="row" mode="format">
       <xsl:choose>
         <xsl:when test="not(starts-with(column[1]/text(), 'Digits'))">
            <xsl:variable name="name" select="normalize-space(column[1]/text())"/>
            <xsl:variable name="desc" select="normalize-space(column[2]/text())"/>
            <field name="{$name}"><xsl:value-of select="$desc"/></field>
         </xsl:when>
        </xsl:choose>
    </xsl:template>
        
    <xsl:template match="*"/>
    
    <xsl:function name="jpw:getName">
       <xsl:param name="name"/>
       <xsl:variable name="names" select="tokenize(normalize-space($name), '\s+')"/>
         <xsl:choose>
           <xsl:when test="count($names) = 6">
               <xsl:value-of select="$names[3]"/>
           </xsl:when>
           <xsl:when test="count($names) = 5">
               <xsl:value-of select="$names[3]"/>
           </xsl:when>
           <xsl:when test="count($names) = 4">
               <xsl:value-of select="$names[3]"/>
           </xsl:when>
           <xsl:when test="count($names) = 3">
               <xsl:value-of select="$names[2]"/>
           </xsl:when>
       </xsl:choose>
    </xsl:function>

    <xsl:function name="jpw:getTable">
       <xsl:param name="name"/>
       <xsl:variable name="names" select="tokenize(normalize-space($name), '\s+')"/>
         <xsl:choose>
           <xsl:when test="count($names) = 6">
               <xsl:value-of select="$names[2]"/>
           </xsl:when>
           <xsl:when test="count($names) = 5">
               <xsl:value-of select="$names[2]"/>
           </xsl:when>
           <xsl:when test="count($names) = 4">
               <xsl:value-of select="$names[2]"/>
           </xsl:when>
           <xsl:when test="count($names) = 3">
               <xsl:value-of select="$names[1]"/>
           </xsl:when>
       </xsl:choose>
    </xsl:function>

    <xsl:function name="jpw:getTlvName">
       <xsl:param name="name"/>
       <xsl:variable name="names" select="tokenize(normalize-space($name), '\s+')"/>
       <xsl:value-of select="$names[3]"/>
    </xsl:function>

    <xsl:function name="jpw:getTlvTable">
       <xsl:param name="name"/>
       <xsl:variable name="names" select="tokenize(normalize-space($name), '\s+')"/>
       <xsl:value-of select="$names[2]"/>
    </xsl:function>

    <xsl:function name="jpw:getValuesName">
       <xsl:param name="name"/>
       <xsl:variable name="names" select="tokenize(normalize-space($name), '\s+')"/>
       <xsl:value-of select="$names[3]"/>
    </xsl:function>

    <xsl:function name="jpw:getValuesTable">
       <xsl:param name="name"/>
       <xsl:variable name="names" select="tokenize(normalize-space($name), '\s+')"/>
       <xsl:value-of select="$names[2]"/>
    </xsl:function>
</xsl:stylesheet>
