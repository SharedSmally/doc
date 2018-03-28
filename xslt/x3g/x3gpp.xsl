<xsl:stylesheet 
    xmlns:xsl="http://www.w3.org/1999/XSL/Transform" 
    version="2.0">

    <xsl:output method="text"/>
    <xsl:strip-space elements="*"/>

    <xsl:variable name='newline'><xsl:text>
</xsl:text></xsl:variable>
    <xsl:variable name='newline2'><xsl:text>

</xsl:text></xsl:variable>
    <xsl:variable name='tbl'><xsl:text>&#x9;</xsl:text></xsl:variable>
    <xsl:variable name='sps' select="'     '"/>
    <xsl:variable name='targets' select="'main gen package deploy clean cleanall'"/>

    <xsl:variable name="asn1cxx" select="/x3gpp/options[@target='asn1']/cxx/text()"/>
    <xsl:variable name="asn1java" select="/x3gpp/options[@target='asn1']/java/text()"/>
    
    <!--   match /  -->
    <xsl:template match="/">
        <xsl:apply-templates/>
        
        <xsl:for-each-group  select="/x3gpp/group/series" group-by="@category"> 
             <xsl:variable name="fname" select="concat(@category, '/makefile')"/>
             <xsl:result-document method="text" href="{$fname}">
                 <xsl:call-template name="subdirMakefile"/>
             </xsl:result-document>
        </xsl:for-each-group> 
    </xsl:template>

    <!--   match /x3gpp  -->
    <xsl:template match="/x3gpp">
XDOC_DIR=<xsl:value-of select="@xdir"/>
X3G_DIR=$(XDOC_DIR)/x3gpp
X3G_ZIP_DIR=$(X3G_DIR)/zip
X3G_DOC_DIR=$(X3G_DIR)/doc

SUBDIRS = \
<xsl:for-each select="group/series">
    <xsl:value-of select="concat($sps, @category, $sps, '\', $newline)"/>
</xsl:for-each>
<xsl:value-of select="$newline"/>

<xsl:apply-templates/>
    </xsl:template>

    <!--   match /x3gpp/options  -->
    <xsl:template match="/x3gpp/options">
        <xsl:apply-templates/>
    </xsl:template>

    <xsl:template match="/x3gpp/options/*">
        <xsl:value-of select="concat(upper-case(name()),'_', upper-case(../@target), '_OPTIONS=', text(), $newline)"/>
    </xsl:template>

    <!--   match /x3gpp/group  -->
    <xsl:template match="/x3gpp/group">
        <xsl:apply-templates/>
    </xsl:template>

    <!--   match /x3gpp/group/series  -->
    <xsl:template match="/x3gpp/group/series">
        <xsl:apply-templates/>
    </xsl:template>

    <!--   match /x3gpp/group/series/spec  -->  
    <xsl:template match="/x3gpp/group/series/spec">
        <xsl:variable name="fname" select="concat(../@category, '/', ./@name, '/makefile')"/>
        <xsl:variable name="category" select="/x3gpp/options[@target='asn1']/@version"/>
        <xsl:variable name="version" select="/x3gpp/options[@target='asn1']/@version"/>
            
        <xsl:result-document method="text" href="{$fname}">
NAME=<xsl:value-of select="@name"/>
SERIES_NUM=<xsl:value-of select="../@number"/>
SPEC_NUM=<xsl:value-of select="@number"/>
<xsl:value-of select="concat($newline, 'URL=http://www.3gpp.org/ftp/Specs/archive/',../@number,'_series/',../@number,'.',@number)"/>

include ../../x3gpp.cfg
-include <xsl:value-of select="@name"/>.cfg

WK_DIR=${X3G_ZIP_DIR}/<xsl:value-of select="@name"/>

main: cfg

cfg: latest.xml

pom: latest.xml
	xsl ../../meta/x3pom.xsl $&lt; $@

latest.xml:<xsl:value-of select="@name"/>.xml
	xsl ../../meta/x3latest.xsl $&lt; $@
	
<xsl:value-of select="concat(@name, '.xml : ${WK_DIR}/',@name, '.xml')"/>
	xsl ../../meta/x3cfg.xsl $&lt; $@ 

<xsl:value-of select="concat('${WK_DIR}/', @name, '.xml : ${WK_DIR}/',@name, '.xhtml')"/>
	xsl ../../meta/x3xml.xsl $&lt; $@ name=<xsl:value-of select="@name"/> coding=<xsl:value-of select="../../@coding"/> version=<xsl:value-of select="concat($asn1ver, $newline2)"/>

<xsl:value-of select="concat('${WK_DIR}/', @name, '.xhtml : ${WK_DIR}/',@name, '.html' )"/>
	cp $&lt; $@
	@sed -i 's/&lt;br&gt;/&lt;\/br&gt;&lt;br&gt;/g' $@
	@sed -i 's/&lt;hr&gt;/&lt;hr\/&gt;/g' $@
	@sed -i 's/&lt;pre&gt;/&lt;pre&gt;&lt;br&gt;/g' $@
	@sed -i 's/&lt;\/pre&gt;/&lt;\/br&gt;&lt;\/pre&gt;/g' $@

<xsl:value-of select="concat('${WK_DIR}/', @name, '.html:')"/>
	@mkdir -p ${WK_DIR}
	wget ${URL} -q -O $@

clean:
	${RM} -rf latest.xml <xsl:value-of select="concat(@name,'.xml')"/>
	
cleanall:clean
	${RM} -rf <xsl:value-of select="concat('${X3G_ZIP_DIR}/', @name,'.*')"/>

        </xsl:result-document>
        
        <xsl:variable name="cfgname" select="concat(../@category, '/', ./@name, '/', @name,'.cfg')"/>
        <xsl:result-document method="text" href="{$cfgname}">
<xsl:value-of select="concat('CXX_OPTIONS=', $asn1cxx, $newline2)"/>
<xsl:value-of select="concat('JAVA_OPTIONS=', $asn1java, $newline2)"/>
        </xsl:result-document>
    </xsl:template>

    <xsl:template match="*"/>
    
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
    
</xsl:stylesheet>
