<xsl:stylesheet 
    xmlns:xsl="http://www.w3.org/1999/XSL/Transform" 
    xmlns:xs="http://www.w3.org/2001/XMLSchema"
    xmlns:jpw="http://www.jpw.com/product/app"
    exclude-result-prefixes="jpw"
    version="2.0">

    <xsl:output method="xml" indent="yes"/>
    <xsl:strip-space elements="*"/>
    
    <xsl:template match="/">
<smpp version="3.4.0">
        <xsl:apply-templates select="smpp/table[position() &gt; 12]"/>
</smpp>
    </xsl:template>

    <xsl:template match="table">
       <xsl:variable name="desc" select="normalize-space(@desc)"/>

       <xsl:choose>
           <xsl:when test="matches($desc, '^5\.\d\.\d\.\d+ ')">
              <xsl:variable name="names" select="tokenize(@name,' ')"></xsl:variable>
              <xsl:variable name="tbl" select="tokenize(@desc,' ')[1]"></xsl:variable>
              <xsl:variable name="tbls" select="tokenize($tbl,'\.')"></xsl:variable>
              <xsl:variable name="lastTbl" select="number($tbls[4])-1"></xsl:variable>
              <xsl:variable name="newTbl" select="concat($tbls[1],'.',$tbls[2], '.',$tbls[3], '.', $lastTbl)"></xsl:variable>
              <xsl:variable name="name" select="normalize-space($names[2])"></xsl:variable>
<tlvref label="Table {$newTbl}" name="{$name}">
    <xsl:apply-templates mode="tlvref"/>
</tlvref>
           </xsl:when>
           
           <xsl:when test="contains(@name, 'PDU')">
              <xsl:variable name="name" select="jpw:getName(@name)"></xsl:variable>
              <xsl:variable name="tbl" select="jpw:getTable(@name)"></xsl:variable>
              <xsl:if test="string-length($name) &gt; 1">
<pdu label="Table {$tbl}" name="{$name}" >
   <desc><xsl:value-of select="@desc"/></desc>
    <xsl:apply-templates mode="pdu"/>
</pdu>
              </xsl:if>
           </xsl:when>

           <xsl:when test="contains(@name, 'Command ID Values')">
              <xsl:variable name="name" select="jpw:getValuesName(@name)"></xsl:variable>
              <xsl:variable name="tbl" select="jpw:getValuesTable(@name)"></xsl:variable>
              <xsl:if test="string-length($name) &gt; 1">
<enum label="Table {$tbl}" name="CommandIDs">
   <desc><xsl:value-of select="@desc"/></desc>
    <xsl:apply-templates mode="commandID"/>
</enum>
              </xsl:if>
           </xsl:when>
           
           <xsl:when test="contains(@name, 'Error Codes')">
              <xsl:variable name="name" select="jpw:getValuesName(@name)"></xsl:variable>
              <xsl:variable name="tbl" select="jpw:getValuesTable(@name)"></xsl:variable>
              <xsl:if test="string-length($name) &gt; 1">
<enum label="Table {$tbl}" name="ErrorCodes" type="error" >
   <desc><xsl:value-of select="@desc"/></desc>
    <xsl:apply-templates mode="ecodes"/>
</enum>
              </xsl:if>
           </xsl:when>

           <xsl:when test="contains(@name, 'values')">
              <xsl:variable name="name" select="jpw:getValuesName(@name)"></xsl:variable>
              <xsl:variable name="tbl" select="jpw:getValuesTable(@name)"></xsl:variable>
              <xsl:if test="string-length($name) &gt; 1">
<enum label="Table {$tbl}" name="{$name}" >
   <desc><xsl:value-of select="@desc"/></desc>
    <xsl:apply-templates mode="values"/>
</enum>
              </xsl:if>
           </xsl:when>

           <xsl:when test="contains(@name, 'Format')">
              <xsl:variable name="name" select="jpw:getValuesName(@name)"></xsl:variable>
              <xsl:variable name="tbl" select="jpw:getValuesTable(@name)"></xsl:variable>
              <xsl:if test="string-length($name) &gt; 1">
<format label="Table {$tbl}" name="{$name}"  >
   <desc><xsl:value-of select="@desc"/></desc>
    <xsl:apply-templates mode="format"/>
</format>
              </xsl:if>
           </xsl:when>

           <xsl:when test="contains(@name, 'Table')">
              <xsl:variable name="names" select="tokenize(@name,' ')"></xsl:variable>
              <xsl:variable name="name" select="normalize-space($names[3])"></xsl:variable>
              <xsl:variable name="tbl" select="normalize-space($names[2])"></xsl:variable>
              <xsl:variable name="desc" select="@desc"></xsl:variable>
              <xsl:if test="string-length($name) &gt; 1">
<tlv label="Table {$tbl}" name="{$name}" desc="{$desc}">
   <desc><xsl:value-of select="@desc"/></desc>
    <xsl:apply-templates mode="tlv"/>
</tlv>
              </xsl:if>
           </xsl:when>
           
       </xsl:choose>
    </xsl:template>
    
    <xsl:template match="row" mode="pdu">
        <xsl:choose>
            <xsl:when test="count(./column)=6">
               <xsl:if test="not(starts-with(column[2]/text(), 'Field Name'))">
                 <xsl:variable name="name" select="normalize-space(column[2]/text())"/>
                 <xsl:variable name="size" select="normalize-space(column[3]/text())"/>
                 <xsl:variable name="type" select="normalize-space(column[4]/text())"/>
                 <xsl:variable name="val" select="normalize-space(column[5]/text())"/>
                 <xsl:variable name="ref"  select="normalize-space(column[6]/text())"/>
                 <xsl:choose>
                     <xsl:when test="starts-with($val, '0x')">
                         <field name="{$name}" size="{$size}" type="{$type}" value="{$val}" ref="{$ref}"/>
                     </xsl:when>
                     <xsl:otherwise>
                         <field name="{$name}" size="{$size}" type="{$type}" ref="{$ref}"><xsl:value-of select="$val"/></field>
                     </xsl:otherwise>
                 </xsl:choose>
               </xsl:if>
            </xsl:when>

            <xsl:when test="count(./column)=5 ">
               <xsl:if test="not(starts-with(column[2]/text(), 'Optional'))">
                 <xsl:variable name="name" select="normalize-space(column[2]/text())"/>
                 <xsl:variable name="type" select="normalize-space(column[3]/text())"/>
                 <xsl:variable name="desc" select="normalize-space(column[4]/text())"/>
                 <xsl:variable name="ref" select="normalize-space(column[5]/text())"/>
                 <field name="{$name}" type="{$type}" ref="{$ref}"><xsl:value-of select="$desc"/></field>
               </xsl:if>
            </xsl:when>

            <xsl:when test="count(./column)=4 ">
               <xsl:if test="not(starts-with(column[2]/text(), 'Optional'))">
                 <xsl:variable name="name" select="normalize-space(column[2]/text())"/>
                 <xsl:variable name="desc" select="normalize-space(column[3]/text())"/>
                 <xsl:variable name="ref" select="normalize-space(column[4]/text())"/>
                 <optional name="{$name}" ref="{$ref}"><xsl:value-of select="$desc"/></optional>
               </xsl:if>
            </xsl:when>
        </xsl:choose>
    </xsl:template>

    <xsl:template match="row" mode="values">
       <xsl:choose>
         <xsl:when test="not(starts-with(column[2]/text(), ' Value'))">
            <xsl:variable name="name" select="normalize-space(column[1]/text())"/>
            <xsl:variable name="value" select="normalize-space(column[2]/text())"/>
            <field name="{$name}" value="{$value}"/>
         </xsl:when>
        </xsl:choose>
    </xsl:template>

    <xsl:template match="row" mode="commandID">
       <xsl:choose>
         <xsl:when test="not(starts-with(column[1]/text(), 'Command ID'))">
            <xsl:variable name="name" select="normalize-space(column[1]/text())"/>
            <xsl:variable name="value" select="normalize-space(column[2]/text())"/>
            <field name="{$name}" value="{$value}"></field>
         </xsl:when>
        </xsl:choose>
    </xsl:template>
    
    <xsl:template match="row" mode="ecodes">
       <xsl:choose>
         <xsl:when test="not(starts-with(column[1]/text(), 'Error C'))">
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

    <xsl:template match="row" mode="tlv">
        <xsl:choose>
            <xsl:when test="count(./column)=6">
               <xsl:if test="not(starts-with(column[2]/text(), 'Field Name'))">
                 <xsl:variable name="name" select="normalize-space(column[2]/text())"/>
                 <xsl:variable name="size" select="normalize-space(column[3]/text())"/>
                 <xsl:variable name="type" select="normalize-space(column[4]/text())"/>
                 <xsl:variable name="val" select="normalize-space(column[5]/text())"/>
                 <xsl:variable name="ref"  select="normalize-space(column[6]/text())"/>
                 <xsl:choose>
                     <xsl:when test="starts-with($val, '0x')">
                         <field name="{$name}" size="{$size}" type="{$type}" value="{$val}" ref="{$ref}"/>
                     </xsl:when>
                     <xsl:otherwise>
                         <field name="{$name}" size="{$size}" type="{$type}" ref="{$ref}"><xsl:value-of select="$val"/></field>
                     </xsl:otherwise>
                 </xsl:choose>
               </xsl:if>
            </xsl:when>

            <xsl:when test="count(./column)=5 ">
               <xsl:if test="not(starts-with(column[1]/text(), 'Field'))">
                 <xsl:variable name="name" select="normalize-space(column[1]/text())"/>
                 <xsl:variable name="size" select="normalize-space(column[2]/text())"/>
                 <xsl:variable name="type" select="normalize-space(column[3]/text())"/>
                 <xsl:variable name="desc" select="normalize-space(column[4]/text())"/>
                 <xsl:variable name="ref" select="normalize-space(column[5]/text())"/>
                 <field name="{$name}" size="{$size}" type="{$type}" ref="{$ref}"><xsl:value-of select="$desc"/></field>
               </xsl:if>
            </xsl:when>

            <xsl:when test="count(./column)=4 ">
               <xsl:if test="not(starts-with(column[2]/text(), 'Optional'))">
                 <xsl:variable name="name" select="normalize-space(column[2]/text())"/>
                 <xsl:variable name="desc" select="normalize-space(column[3]/text())"/>
                 <xsl:variable name="ref" select="normalize-space(column[4]/text())"/>
                 <optional name="{$name}" ref="{$ref}"><xsl:value-of select="$desc"/></optional>
               </xsl:if>
            </xsl:when>
        </xsl:choose>
    </xsl:template>
    
    <xsl:template match="row" mode="tlvref">
       <xsl:choose>
         <xsl:when test="not(starts-with(column[1]/text(), 'Field'))">
            <xsl:variable name="field" select="normalize-space(column[1]/text())"/>
            <xsl:variable name="size" select="normalize-space(column[2]/text())"/>
            <xsl:variable name="type" select="normalize-space(column[3]/text())"/>
            <xsl:variable name="desc" select="normalize-space(column[4]/text())"/>
            <field field="{$field}" size="{$size}" type="{$type}"><xsl:value-of select="$desc"/></field>
         </xsl:when>
        </xsl:choose>
    </xsl:template>
    
    
    <xsl:template match="*"/>
    
    <xsl:function name="jpw:getName">
       <xsl:param name="name"/>
       <xsl:variable name="names" select="tokenize(normalize-space($name), '\s+')"/>
         <xsl:choose>
           <xsl:when test="count($names) = 6">
               <xsl:choose>
                  <xsl:when test="upper-case($names[5]) = 'PDU'">
                     <xsl:value-of select="$names[4]"/>
                  </xsl:when>
                  <xsl:otherwise>
                     <xsl:value-of select="$names[5]"/>
                  </xsl:otherwise>
               </xsl:choose>
           </xsl:when>
           <xsl:when test="count($names) = 5">
               <xsl:choose>
                   <xsl:when test="upper-case($names[4]) = 'PDU'">
                      <xsl:value-of select="$names[3]"/>
                  </xsl:when>
                  <xsl:otherwise>
                      <xsl:value-of select="$names[4]"/>
                  </xsl:otherwise>
               </xsl:choose>
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
