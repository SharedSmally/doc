<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet version="2.0"
   xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
   xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
   xmlns:app="http://www.cpw.com/app/common"
>

    <xsl:variable name='cname' select="'com.cpw'"/>

    <!--  common defined variables  -->
    <xsl:variable name='newline'><xsl:text>
    </xsl:text></xsl:variable>
    <xsl:variable name='lf'><xsl:text>&#xa;</xsl:text></xsl:variable> <!--  newline -->
    <xsl:variable name='cr'><xsl:text>&#xd;</xsl:text></xsl:variable> <!--  carriage return -->
    <xsl:variable name='eq'><xsl:text>==</xsl:text></xsl:variable>
    <xsl:variable name='ne'><xsl:text>!=</xsl:text></xsl:variable>
    <xsl:variable name='gt'><xsl:text>&gt;</xsl:text></xsl:variable>
    <xsl:variable name='ge'><xsl:text>&gt;=</xsl:text></xsl:variable>
    <xsl:variable name='lt'><xsl:text>&lt;</xsl:text></xsl:variable>
    <xsl:variable name='le'><xsl:text>&lt;=</xsl:text></xsl:variable>
    <xsl:variable name='quot'><xsl:text>&quot;=</xsl:text></xsl:variable> <!-- "  -->
    <xsl:variable name='apos'><xsl:text>&apos;=</xsl:text></xsl:variable> <!-- '  -->
    <xsl:variable name='amp'><xsl:text>&amp;=</xsl:text></xsl:variable> <!-- &  -->

    <xsl:variable name='sps'><xsl:text>    </xsl:text></xsl:variable>
    <xsl:variable name='sps2' select="concat($sps,$sps)"/>
    <xsl:variable name='sps3' select="concat($sps,$sps2)"/>
    <xsl:variable name='sps4' select="concat($sps2,$sps2)"/>

    <!--  common functions -->
    <xsl:function name = "app:fullns">
        <xsl:param name="ns" />
        <xsl:value-of select="concat($cname,'.',$ns)"/>
    </xsl:function>

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

    <xsl:function name = "app:ucfirst">
        <xsl:param name="str" />
        <xsl:value-of select="concat(upper-case(substring($str, 1, 1)), substring($str, 2))" />
    </xsl:function>

    <xsl:function name = "app:join">
        <xsl:param name="nodes" />
        <xsl:param name="attrname" />
        <xsl:for-each select="$nodes">
            <xsl:if test="position() != 1">,</xsl:if><xsl:value-of select="@*[name() = $attrname]"/>
        </xsl:for-each>
    </xsl:function>

    <!-- math ops: number,floor,ceiling,abs -->
    <xsl:function name="app:dec">
        <xsl:param name="val"/>
        <xsl:value-of select="floor(number($val) - number(1))" />
    </xsl:function>
    <xsl:function name="app:inc">
        <xsl:param name="val"/>
        <xsl:value-of select="floor(number($val) + number(1))" />
    </xsl:function>

<!--
    <xsl:function name="app:merge">
        <xsl:variable name="trapNodes" select="document($trapAction)"/>
        <xsl:variable name="temp">
            <xsl:copy-of select="$ns0"/>
            <xsl:copy-of select="$ns1"/>
        </xsl:variable>
        <xsl:copy>
            <xsl:apply-templates select="document('2.xml')/*/lang[@target='cxx']"/>
            <xsl:apply-templates select="document('3.xml')/*/lang[@target='cxx']"/>
        </xsl:copy>
    </xsl:function>
 -->

</xsl:stylesheet>
