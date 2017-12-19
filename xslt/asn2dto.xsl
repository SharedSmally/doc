<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet version="2.0"
    xmlns:cpw="http://www.cpw.com/app/xsl/app"
    xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

<xsl:output method="xml" indent="yes" />
<xsl:strip-space elements="*" />

<xsl:variable name="seqTag" select="' ::= SEQUENCE '"/>
<xsl:variable name="choiceTag" select="' ::= CHOICE '"/>
<xsl:variable name="enumTag" select="' ::= ENUMERATED '"/>
<xsl:variable name="bitsTag" select="' ::= BIT STRING '"/>
<xsl:variable name="optTag" select="' OPTIONAL'"/>
<xsl:variable name="sizeStartTag" select="'(SIZE ('"/>
<xsl:variable name="sizeEndTag" select="'))'"/>

<xsl:template match="/">
        <xsl:apply-templates select="/dto"/>

</xsl:template>

<xsl:template match="/dto">
    <dto>
        <xsl:copy-of select="@*"/>
        <xsl:apply-templates/>
    </dto>
</xsl:template>


<xsl:template match="module">
    <module>
         <xsl:if test="not(@name)">
            <xsl:attribute name="name">
                <xsl:value-of select="cpw:stripNewline(substring-before(./desc/text(),' DEFINITIONS '))"/>
            </xsl:attribute>
        </xsl:if>
        <xsl:copy-of select="@*"/>

        <xsl:apply-templates/>
    </module>
</xsl:template>

<xsl:template match="import/text()">
  <xsl:for-each select="tokenize(., '\n\r?')[.]">
    <xsl:variable name="impt" select="."/>
    <xsl:variable name="name" select="cpw:strip(substring-after($impt, ' FROM '))"/>
    <xsl:variable name="value" select="cpw:strip(substring-before($impt, ' FROM '))"/>
    <xsl:if test="string-length($name)>0">
        <import>
            <xsl:attribute name="name"><xsl:value-of select="$name"/></xsl:attribute>
            <xsl:sequence select="$value"></xsl:sequence>
        </import>
    </xsl:if>
  </xsl:for-each>
</xsl:template>

<!--
<import>
    xxx,xxx FROM yyy
</import>
 -->
<xsl:template match="import">
    <xsl:apply-templates/>
</xsl:template>

<xsl:template match="desc">
</xsl:template>

<!--
PolygonDescription ::= SEQUENCE (SIZE (3..15)) OF Coordinate
 -->
<xsl:template match="type">
    <xsl:for-each select="./tokenize(text(), '\n\r?')[.]">
        <xsl:variable name="t0" select="cpw:strip(.)"/>
        <xsl:if test="string-length($t0) > 0">

        </xsl:if>
    </xsl:for-each>
</xsl:template>

<!-- element:  list of structs -->
<xsl:template match="element/text()">
  <xsl:for-each select="tokenize(., '\n\r?\n\r?')[.]">
    <xsl:variable name="elem" select="."/>
    <xsl:choose>
        <xsl:when test="contains($elem, $seqTag)">
            <xsl:call-template name="seqElement">
                <xsl:with-param name="name" select="cpw:strip(substring-before($elem, $seqTag))"/>
                <xsl:with-param name="fields" select="substring-after($elem, $seqTag)"/>
            </xsl:call-template>
        </xsl:when>

        <xsl:when test="contains($elem, $choiceTag)">
            <xsl:call-template name="choiceElement">
                <xsl:with-param name="name" select="cpw:strip(substring-before($elem, $choiceTag))"/>
                <xsl:with-param name="fields" select="substring-after($elem, $choiceTag)"/>
            </xsl:call-template>
        </xsl:when>

        <xsl:when test="contains($elem, $enumTag)">
            <xsl:call-template name="enumElement">
                <xsl:with-param name="name" select="cpw:strip(substring-before($elem, $enumTag))"/>
                <xsl:with-param name="fields" select="substring-after($elem, $enumTag)"/>
            </xsl:call-template>
        </xsl:when>

        <xsl:when test="contains($elem, $bitsTag)">
            <xsl:call-template name="bitsElement">
                <xsl:with-param name="name" select="cpw:strip(substring-before($elem, $enumTag))"/>
                <xsl:with-param name="fields" select="substring-after($elem, $enumTag)"/>
            </xsl:call-template>
        </xsl:when>

        <xsl:otherwise>
            <xsl:variable name="t0" select="cpw:strip($elem)"/>
            <xsl:if test="string-length($t0) > 0">
                <xsl:message><xsl:value-of select="concat('Unknown: ', $elem)"/></xsl:message>
            </xsl:if>
        </xsl:otherwise>
    </xsl:choose>

  </xsl:for-each>
</xsl:template>

<xsl:template match="element">
    <xsl:apply-templates/>
</xsl:template>

<xsl:template name="seqElement">
    <xsl:param name="name"/>
    <xsl:param name="fields"/>
    <element>
        <xsl:attribute name="name"><xsl:value-of select="$name"/></xsl:attribute>
        <xsl:call-template name="fieldElements">
            <xsl:with-param name="fields" select="$fields"/>
        </xsl:call-template>
    </element>
</xsl:template>

<xsl:template name="choiceElement">
    <xsl:param name="name"/>
    <xsl:param name="fields"/>
    <union>
        <xsl:attribute name="name"><xsl:value-of select="$name"/></xsl:attribute>
        <xsl:call-template name="fieldElements">
            <xsl:with-param name="fields" select="$fields"/>
        </xsl:call-template>
    </union>
</xsl:template>

<xsl:template name="fieldElements">
    <xsl:param name="fields"/>
    <xsl:for-each select="tokenize($fields, '\n\r?')[.]">
        <xsl:variable name="f0" select="cpw:strip(.)"/>
        <xsl:if test="not( $f0 = '{' or $f0 = '}' or $f0 = '...' or  $f0 = '' )">
            <!-- Format: name [index] type[(SIZE (...)][(range)] [OPTIONAL] -->
            <xsl:variable name="f1" select="normalize-space(substring-before($f0, ' ['))"/>
            <xsl:variable name="f2" select="normalize-space(substring-after($f0, ' ['))"/>
            <xsl:variable name="f3" select="normalize-space(substring-before($f2, '] '))"/>
            <xsl:variable name="f4" select="normalize-space(substring-after($f2, '] '))"/>
            <xsl:variable name="f5" select="normalize-space(replace($f4,$optTag,''))"/>  <!--  type -->

            <field>
                <xsl:attribute name="index"><xsl:value-of select="$f3"/></xsl:attribute>
                <xsl:attribute name="name"><xsl:value-of select="$f1"/></xsl:attribute>

                <xsl:choose>
                    <xsl:when test="contains($f5, $sizeStartTag)"> <!--  handle (SIZE (size)):  -->
                        <xsl:variable name="r1" select="normalize-space(substring-before($f5,$sizeStartTag))"/>
                        <xsl:variable name="r2" select="normalize-space(substring-after($f5,$sizeStartTag))"/>
                        <xsl:variable name="r3" select="normalize-space(substring-before($r2,$sizeEndTag))"/>
                        <xsl:attribute name="type"><xsl:value-of select="$r1"/></xsl:attribute>
                        <xsl:attribute name="size"><xsl:value-of select="$f3"/></xsl:attribute>
                    </xsl:when>

                    <xsl:when test="contains($f5,'(')">  <!--  handle range (range):  -->
                        <xsl:variable name="r1" select="normalize-space(substring-before($f5,'('))"/>
                        <xsl:variable name="r2" select="normalize-space(substring-after($f5,'('))"/>
                        <xsl:variable name="r3" select="normalize-space(substring-before($r2,')'))"/>
                        <xsl:attribute name="type"><xsl:value-of select="$r1"/></xsl:attribute>
                        <xsl:attribute name="range"><xsl:value-of select="$r3"/></xsl:attribute>
                    </xsl:when>

                    <xsl:otherwise>
                        <xsl:attribute name="type"><xsl:value-of select="$f5"/></xsl:attribute>
                    </xsl:otherwise>
                </xsl:choose>

                <xsl:if test="contains($f4, $optTag)">
                    <xsl:attribute name="optional"><xsl:value-of select="'true'"/></xsl:attribute>
               </xsl:if>
               <xsl:sequence select="$f0"/>
            </field>
        </xsl:if>
    </xsl:for-each>

</xsl:template>

<xsl:template name="enumElement">
    <xsl:param name="name"/>
    <xsl:param name="fields"/>
    <enum>
        <xsl:attribute name="name"><xsl:value-of select="$name"/></xsl:attribute>
        <xsl:for-each select="tokenize($fields, '\n\r?')[.]">
            <xsl:variable name="f0" select="cpw:strip(.)"/>
            <xsl:if test="not( $f0 = '{' or $f0 = '}' or $f0 = ', ...'  or $f0 = '' )">
                <!-- Format: name(value) -->
                <xsl:variable name="f1" select="normalize-space(substring-before($f0, '('))"/>
                <xsl:variable name="f2" select="normalize-space(substring-after($f0, '('))"/>
                <xsl:variable name="f3" select="normalize-space(substring-before($f2, ')'))"/>
                <field>
                    <xsl:attribute name="value"><xsl:value-of select="$f3"/></xsl:attribute>
                    <xsl:attribute name="name"><xsl:value-of select="$f1"/></xsl:attribute>
                    <xsl:sequence select="$f0"/>
                </field>
            </xsl:if>
        </xsl:for-each>
    </enum>
</xsl:template>

<xsl:template name="bitsElement">
    <xsl:param name="name"/>
    <xsl:param name="fields"/>
    <bits>
        <xsl:attribute name="name"><xsl:value-of select="$name"/></xsl:attribute>
        <xsl:for-each select="tokenize($fields, '\n\r?')[.]">
            <xsl:variable name="f0" select="cpw:strip(.)"/>
            <xsl:if test="not( $f0 = '{' or $f0 = '}' or $f0 = '...' )">
                <field><xsl:sequence select="$f0"></xsl:sequence>
                </field>
            </xsl:if>
        </xsl:for-each>
    </bits>
</xsl:template>

<!--
maxLidSize INTEGER ::= 64
 -->
<xsl:template match="const">
    <xsl:for-each select="./tokenize(text(), '\n\r?')[.]">
        <xsl:variable name="t0" select="cpw:strip(.)"/>
        <xsl:if test="string-length($t0) > 0">
            <xsl:variable name="name" select="cpw:strip(substring-before($t0, ' '))"/>
            <xsl:variable name="t1" select="cpw:strip(substring-after($t0, ' '))"/>
            <xsl:variable name="type" select="cpw:strip(substring-before($t1, ' ::= '))"/>
            <xsl:variable name="value" select="cpw:strip(substring-after($t1, ' ::= '))"/>
            <const>
                <xsl:attribute name="name"><xsl:value-of select="$name"/></xsl:attribute>
                <xsl:attribute name="type"><xsl:value-of select="$type"/></xsl:attribute>
                <xsl:attribute name="value"><xsl:value-of select="$value"/></xsl:attribute>
            </const>
        </xsl:if>
    </xsl:for-each>
</xsl:template>

<xsl:function name="cpw:strip">
    <xsl:param name="t0"/>
    <xsl:variable name="t1" select="replace($t0,',$', '', 'm')"/>
    <xsl:variable name="t2" select="replace($t1,';$', '', 'm')"/>
    <xsl:variable name="t3" select="replace($t2,'\s+$', '', 'm')"/>
    <xsl:variable name="t4" select="replace($t3,'^\s+', '', 'm')"/>
    <xsl:variable name="t5" select="replace($t4,'\s+', ' ', 'm')"/>
    <xsl:variable name="t6" select="replace($t5,';$', '', 'm')"/>
    <xsl:value-of select="$t6"/>
</xsl:function>

<xsl:function name="cpw:stripNewline">
    <xsl:param name="t0"/>
    <xsl:variable name="t1" select="translate($t0,'&#x0d;', '')" />
    <xsl:variable name="t2" select="translate($t1,'&#x0a;', '')" />
    <xsl:variable name="t3" select="replace($t2,'\s+', '')" />
    <xsl:value-of select="$t3"/>
</xsl:function>

</xsl:stylesheet>
