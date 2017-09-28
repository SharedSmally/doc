<?xml version="1.0" encoding="UTF-8"?>
<!-- 
   generate class desc class/*.xml based on xml template files:
   <module namespace="">
      <class name="">
      </class>*
   <module>
 -->
 
<xsl:stylesheet version="2.0" 
   xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
   xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
   xmlns:cpw="http://www.cpw.com/app/xslt"
   exclude-result-prefixes="xsi cpw"
   >
    <xsl:output method="xml" version="1.0" encoding="UTF-8" indent="yes"/>
    <xsl:strip-space elements="*"/>
    
    <!-- Receives the baseDir by srcdir=xxx. default is ./ -->
    <xsl:param name="base" select="'./'" />
    <xsl:param name="lang" select="'c'" />

<xsl:template match="/">
    <xsl:message select="concat('generate codes for ',$lang)"/>
    <xsl:message select="concat('base directory:',$base)"/>
    <xsl:apply-templates/>
</xsl:template>

<xsl:template match="class">
    <xsl:variable name="xmlfile" select="concat(@name, '.xml')" />
    <xsl:variable name="cls" select="document($xmlfile)" />
    <xsl:variable name="outXmlfile" select="concat('class_', $xmlfile)" />
    <xsl:message select="concat('&#xa;','class file xml =',$xmlfile, ', out xml file=', $outXmlfile)"/>
    <xsl:result-document method="xml" href="{$outXmlfile}">
    <class>
       <xsl:attribute name="namespace"><xsl:value-of select="../@namespace" /></xsl:attribute>
       <xsl:attribute name="name"><xsl:value-of select="@name" /></xsl:attribute>
       <desc>class desc</desc>
       <xsl:apply-templates/>
    </class>
    </xsl:result-document>
</xsl:template>

<!--  access specifiers: 0: private; 1:protected; 2:public -->
<xsl:template match="d|d0|d1|d2|s|s0|s1|s2" >
    <xsl:variable name="nodeName" select="local-name()" />
    <xsl:call-template name="genDataNode">
        <xsl:with-param name="names" select="@name|@names" />
        <xsl:with-param name="type" select="@type" />
        <xsl:with-param name="access" select="cpw:getAccess($nodeName)" />
        <xsl:with-param name="property" select="cpw:getDataAccess(.)" />
        <xsl:with-param name="static" select="cpw:isStatic(.)" />
    </xsl:call-template>
    <xsl:call-template name="genDataNode">
        <xsl:with-param name="names" select="text()" />
        <xsl:with-param name="type" select="@type" />
        <xsl:with-param name="access" select="cpw:getAccess($nodeName)" />
        <xsl:with-param name="property" select="cpw:getDataAccess(.)" />
        <xsl:with-param name="static" select="cpw:isStatic(.)" />
    </xsl:call-template>
</xsl:template>

<xsl:template match="m|m0|m1|m2|pm|pm0|pm1|pm2|vm|vm0|vm1|vm2|mc|mc0|mc1|mc2|pmc|pmc0|pmc1|pmc2|vmc|vmc0|vmc1|vmc2|sm|sm0|sm1|sm2" >
    <xsl:variable name="nodeName" select="local-name()" />
    <xsl:call-template name="genMethodNode">
        <xsl:with-param name="names" select="@name|@names" />
        <xsl:with-param name="type" select="@type" />
        <xsl:with-param name="access" select="cpw:getAccess($nodeName)" />
        <xsl:with-param name="const" select="cpw:isConstant(.)" />
        <xsl:with-param name="static" select="cpw:isStatic(.)" />
    </xsl:call-template>
    <xsl:call-template name="genMethodNode">
        <xsl:with-param name="names" select="text()" />
        <xsl:with-param name="type" select="@type" />
        <xsl:with-param name="access" select="cpw:getAccess($nodeName)" />
        <xsl:with-param name="const" select="cpw:isConstant(.)" />
        <xsl:with-param name="static" select="cpw:isStatic(.)" />
    </xsl:call-template>
</xsl:template>

<xsl:template match="c" >
    <xsl:variable name="type" select="@type" />
    <xsl:for-each select="tokenize(./text(), ' ')">
      <xsl:for-each select="tokenize(., ',')">
       <const>
           <xsl:attribute name="name"><xsl:value-of select="."/></xsl:attribute>
           <xsl:attribute name="type"><xsl:value-of select="$type"/></xsl:attribute>
           <desc>data desc</desc>
       </const> 
       </xsl:for-each>
    </xsl:for-each>
</xsl:template>

<xsl:template name="genDataNode">
    <xsl:param name="names"/>
    <xsl:param name="type"/>
    <xsl:param name="access"/>
    <xsl:param name="property"/>
    <xsl:param name="static"/>
    <xsl:for-each select="tokenize($names, ' ')">
      <xsl:for-each select="tokenize(., ',')">
       <data>
           <xsl:attribute name="name"><xsl:value-of select="."/></xsl:attribute>
           <xsl:attribute name="type"><xsl:value-of select="$type"/></xsl:attribute>
           <xsl:attribute name="access"><xsl:value-of select="$access"/></xsl:attribute>
           <xsl:attribute name="property"><xsl:value-of select="$property"/></xsl:attribute>
           <xsl:attribute name="static"><xsl:value-of select="$static"/></xsl:attribute>
           <desc>data desc</desc>
       </data> 
       </xsl:for-each>
    </xsl:for-each>
</xsl:template>

<xsl:template name="genMethodNode">
    <xsl:param name="names"/>
    <xsl:param name="type"/>
    <xsl:param name="access"/>
    <xsl:param name="const"/>
    <xsl:param name="static"/>
    <xsl:for-each select="tokenize($names, ' ')">
      <xsl:for-each select="tokenize(., ',')">
       <method>
           <xsl:attribute name="name"><xsl:value-of select="."/></xsl:attribute>
           <xsl:attribute name="type"><xsl:value-of select="$type"/></xsl:attribute>
           <xsl:attribute name="access"><xsl:value-of select="$access"/></xsl:attribute>
           <xsl:attribute name="const"><xsl:value-of select="$const"/></xsl:attribute>
           <xsl:attribute name="static"><xsl:value-of select="$static"/></xsl:attribute>
           <desc>method desc</desc>
           <impl>
<xsl:text disable-output-escaping="yes">&#xa;&lt;![CDATA[</xsl:text>
IMPL
<xsl:text disable-output-escaping="yes">]]&gt;&#xa;      </xsl:text>
           </impl>
       </method> 
       </xsl:for-each>
    </xsl:for-each>
</xsl:template>

<xsl:template match="import|cimport|himport|jimport" >
     <xsl:copy-of select="."/>
</xsl:template>

<xsl:function name="cpw:getAccess">
    <xsl:param name="name"></xsl:param>
    <xsl:choose>
        <xsl:when test="ends-with($name, '0')">
            <xsl:value-of select="'private'"/>
        </xsl:when>
        <xsl:when test="ends-with($name, '1')">
            <xsl:value-of select="'protected'"/>
        </xsl:when>
        <xsl:when test="ends-with($name, '2')">
            <xsl:value-of select="'public'"/>
        </xsl:when>
        <xsl:otherwise>
            <xsl:value-of select="'public'"/>
        </xsl:otherwise>
    </xsl:choose>
</xsl:function>

<xsl:function name="cpw:getDataAccess">
    <xsl:param name="node"></xsl:param>
    <xsl:choose>
        <xsl:when test="$node/@access">
            <xsl:value-of select="$node/@access"/>
        </xsl:when>
        <xsl:otherwise>
            <xsl:value-of select="'rw'"/>
        </xsl:otherwise>
    </xsl:choose>
</xsl:function>
<xsl:function name="cpw:isStatic">
    <xsl:param name="node"></xsl:param>
    <xsl:choose>
        <xsl:when test="starts-with(local-name($node), 's')">
            <xsl:value-of select="'true'"/>
        </xsl:when>
        <xsl:otherwise>
            <xsl:value-of select="'false'"/>
        </xsl:otherwise>
    </xsl:choose>
</xsl:function>
<xsl:function name="cpw:isConstant">
    <xsl:param name="node"></xsl:param>
    <xsl:choose>
        <xsl:when test="contains(local-name($node), 'c')">
            <xsl:value-of select="'true'"/>
        </xsl:when>
        <xsl:otherwise>
            <xsl:value-of select="'false'"/>
        </xsl:otherwise>
    </xsl:choose>
</xsl:function>

</xsl:stylesheet>


<!--  
   generate class desc class/*.xml based on xml template files:
   <module namespace="">
      <class name="">
         <desc></desc>
         imports
         <import namespace="">classes</import>
         <himport prefix="" suffix="" redefine="" local="true|false">files</himport>
         <cimport prefix="" suffix="" redefine="" local="true|false">files</cimport>
         
         data members
         <sd[0,1,2] type="" access="r|w|rw">static data members</sd[0,1,2]>
         <cd[0,1,2] type="" name="" value="" access="r|w|rw">value</cd[0,1,2]>
         <d[0,1,2] type="" access="r|w|rw">class data members</d[0,1,2]>
         
         operator(s) 
         <op>
         </op>

         operators: 
             math/Arithmetic:+,-,*,/,%;  +=,-=,*=,/=,%=;  
             bitwise:^(XOR),|(OR),&(AND),~(complement),<<(shift left), >>(shit right)
                     ^=, |=, &=, <<=, >>=
             assignment: =
             relational: ==, !=, >, >=, <, <=
             logical: !(NOT, &&(AND), ||(OR)
             inc/dec:  ++, - -
                  T& T::operator++() // prefix
                  T T::operator++(int unused) // postfix
             Subscript operator: []
             Function call operator: ()
             Address of, Reference, and Pointer operators: operator&(), operator*() and operator->()
             comma operator: ,() 
             Member Reference operators: operator->() and operator->*() 
             Memory management operators:
                new (allocate memory for object)
                new[ ] (allocate memory for array)
                delete (deallocate memory for object)
                delete[ ] (deallocate memory for array)
            Conversion operators:
                operator ''type''() const; // const is not necessary, but is good style
                operator int() const;
         <ops name="">
         </ops>

         methods:
         <m[0,1,2]>methods</m[0,1,2]>
         <vm[0,1,2]>virtual methods</vm[0,1,2]>
         <pm[0,1,2]>pure virtual methods</pm[0,1,2]>

         <mc[0,1,2]>const methods</mc[0,1,2]>
         <vmc[0,1,2]>virtual const methods</vmc[0,1,2]>
         <pmc[0,1,2]>pure virtual const methods</pmc[0,1,2]>

         <sm[0,1,2]>static method</sm[0,1,2]>

         convert to method nodes:
         <method name="" type="" template="" 
             virtual="true|false|pure" inline="true|false"
             static="true|false" const="true|false" >
             <desc></desc>
             <template>
<![CDATA[
template_decl
]]>
             </template>
             <return></return>
             <arg name="" type="">
                 <desc></desc>
             </arg>
             <impl></impl>
         </method>

      </class>
   </module>
 -->
