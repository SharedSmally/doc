<xsl:stylesheet 
    xmlns:xsl="http://www.w3.org/1999/XSL/Transform" 
    xmlns:xs="http://www.w3.org/2001/XMLSchema"
    xmlns:jpw="http://www.jpw.com/product/app"
    version="2.0">

    <xsl:output method="text" indent="yes"/>
    <xsl:strip-space elements="*"/>

    <!--  project base dir -->
    <xsl:param name="pdir" required="yes"/>
    <!--  project download document dir: $ddir/xzip/x3gpp/$name; $ddir/xdoc/x3gpp/$name -->
    <xsl:param name="ddir" required="yes"/>

    <xsl:variable name="newline"><xsl:text>
</xsl:text></xsl:variable>
    <xsl:variable name='tbl'><xsl:text>&#x9;</xsl:text></xsl:variable>
    <xsl:variable name='sps' select="'     '"/>
    <xsl:variable name='targets' select="'main gen package deploy clean cleanall'"/>
    <xsl:variable name="name" select="/x3gpp/@name"/>
    <xsl:variable name="ppdir" select="concat($pdir, '/project/', $name)"/>
    <xsl:variable name="dddir" select="concat($ddir, '/xzip/x3gpp/', $name)"/>
    <xsl:variable name="zzdir" select="concat($ddir, '/xdoc/x3gpp/', $name)"/>
    
    <xsl:variable name="coding" select="/x3gpp/@coding"/>
    <xsl:variable name="site" select="'http://www.3gpp.org/'"/>
    
    <xsl:template match="/">
        <xsl:apply-templates/>
    </xsl:template>

    <xsl:template match="/x3gpp">
        <xsl:apply-templates/>
    </xsl:template>
    
    <xsl:template match="/x3gpp/release">
        <xsl:apply-templates/>
    </xsl:template>

    <xsl:template match="/x3gpp/release/spec">
        <xsl:variable name="mkfile" select="concat($pdir,'/makefile')"></xsl:variable>
    
        <xsl:variable name="mkfile" select="concat($pdir,'/',@version,'/makefile')"></xsl:variable>
        
        <xsl:variable name="pomfile" select="concat($pdir,'/',@version,'/pom.xml')"></xsl:variable>
    </xsl:template>
    

    <xsl:template name="subdirMakefile">
SUBDIRS = `ls -d */`

<xsl:for-each select="tokenize($targets,' ')">
<xsl:variable name="target" select="."/>
<xsl:value-of select="$target"/>:
	for p in ${SUBDIRS}; do \
		cd $$p &amp;&amp; make <xsl:value-of select="$target"/> &amp;&amp; cd ../;  \
	done

</xsl:for-each>
    </xsl:template>


    <xsl:template name="createPomXml">
    </xsl:template>
</xsl:stylesheet>
