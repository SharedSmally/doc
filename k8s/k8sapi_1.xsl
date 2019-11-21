<xsl:stylesheet
    xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
    xmlns:xs="http://www.w3.org/2001/XMLSchema"
    xmlns:cpw="http://www.jpw.com/product/app/cxx"
    exclude-result-prefixes="cpw xs"
    version="2.0">

    <xsl:output method="xml" indent="yes"/>
    <xsl:strip-space elements="*"/>

    <xsl:template match="/">
        <xsl:apply-templates/>
    </xsl:template>

    <xsl:template match="k8s">
<k8s version="{@version}" date="{@date}">
           <xsl:apply-templates/>
</k8s>
    </xsl:template>

<!--
    <xsl:template match="resource">
       <xsl:variable name="node1" select="preceding-sibling::*[1]"/>
       <xsl:variable name="node2" select="preceding-sibling::*[2]"/>
<resource name="{name($node1)}">
       <xsl:if test="name($node1)='category'">
            <xsl:attribute name="group"><xsl:value-of select="$node1/@group"/></xsl:attribute>
            <xsl:attribute name="version"><xsl:value-of select="$node1/@version"/></xsl:attribute>
            <xsl:attribute name="kind"><xsl:value-of select="$node1/@kind"/></xsl:attribute>
       </xsl:if>
       <xsl:if test="name($node1)='h3'">
            <xsl:attribute name="name"><xsl:value-of select="$node1/@name"/></xsl:attribute>
       </xsl:if>
       <xsl:if test="name($node1)='h2'">
            <xsl:attribute name="name"><xsl:value-of select="$node1/@name"/></xsl:attribute>
       </xsl:if>
       <xsl:if test="name($node2)='group'">
            <xsl:attribute name="name"><xsl:value-of select="$node2/@name"/></xsl:attribute>
       </xsl:if>
           <xsl:apply-templates/>
</resource>
    </xsl:template>
--> 

    <xsl:template match="operation">
       <xsl:variable name="node1" select="preceding-sibling::operations[1]"/>
       <xsl:variable name="node2" select="preceding-sibling::h2[1]"/>
<operation category="{$node1/@name}" name="{$node2/@name}" >
       <xsl:if test="name($node1)='category'">
            <xsl:attribute name="group"><xsl:value-of select="$node1/@group"/></xsl:attribute>
            <xsl:attribute name="version"><xsl:value-of select="$node1/@version"/></xsl:attribute>
            <xsl:attribute name="kind"><xsl:value-of select="$node1/@kind"/></xsl:attribute>
       </xsl:if>
       <xsl:if test="name($node1)='h3'">
            <xsl:attribute name="name"><xsl:value-of select="$node1/@name"/></xsl:attribute>
       </xsl:if>
       <xsl:if test="name($node1)='h2'">
            <xsl:attribute name="name"><xsl:value-of select="$node1/@name"/></xsl:attribute>
       </xsl:if>
       <xsl:if test="name($node2)='group'">
            <xsl:attribute name="name"><xsl:value-of select="$node2/@name"/></xsl:attribute>
       </xsl:if>
           <xsl:apply-templates/>
</operation>
    </xsl:template>
   
    <xsl:template match="field" >
       <xsl:copy-of select="."/>       
    </xsl:template>

    <xsl:template match="*">
    </xsl:template>
    
   <xsl:function name="cpw:getText">
       <xsl:param name="node"/>
       <xsl:variable name="t1" select="$node/text()"/>
       <xsl:variable name="t2" select="$node/STRONG/text()"/>
       <xsl:choose>
          <xsl:when test="string-length($t1)>0"><xsl:value-of select="$t1"/></xsl:when>
          <xsl:when test="string-length($t2)>0"><xsl:value-of select="$t2"/></xsl:when>
       </xsl:choose>
   </xsl:function>

</xsl:stylesheet>
