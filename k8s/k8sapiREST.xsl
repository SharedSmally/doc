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
           <xsl:apply-templates select="group"/>
</k8sapi>
    </xsl:template>

    <xsl:template match="group">
       <xsl:variable name="grpname" select="@name"/> 
       <xsl:if test="count(following-sibling::operations[@group=$grpname])>0">
<group>
         <xsl:copy-of select="@*"/>
         <xsl:apply-templates select="following-sibling::operations[@group=$grpname]"/>
</group>
       </xsl:if>
    </xsl:template>

    <xsl:template match="operations"> 
        <xsl:variable name="grpname" select="@group"/>
<operations>
     <xsl:copy-of select="@*[name()!='group']"/>
     <xsl:apply-templates select="following-sibling::operation[@group=$grpname]"/>
</operations>
    </xsl:template>

    <xsl:template match="operation"> 
<operation>
     <xsl:copy-of select="@*[name()!='group' and name()!='operations']"/>
     <xsl:copy-of select="*"/>
</operation>
    </xsl:template>
    
</xsl:stylesheet>
