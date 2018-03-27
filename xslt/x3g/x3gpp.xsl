<xsl:stylesheet 
    xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
    xmlns:jpw="http://www/jpw.com/xslt" 
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
    
    <xsl:template match="/">
        <xsl:for-each-group  select="/x3gpp/group/series" group-by="@category"> 
             <xsl:variable name="fname" select="concat('x3g/',@category, '/makefile')"/>
             <xsl:result-document method="text" href="{$fname}">
                 <xsl:call-template name="subdirMakefile"/>
             </xsl:result-document>
        </xsl:for-each-group> 

        <xsl:apply-templates/>
    </xsl:template>

    <xsl:template match="/x3gpp">
        <xsl:apply-templates/>
    </xsl:template>
    
    <xsl:template match="/x3gpp/group">
        <xsl:apply-templates/>
    </xsl:template>

    <xsl:template match="/x3gpp/group/series">
        <xsl:apply-templates/>
    </xsl:template>

    <xsl:template match="/x3gpp/group/series/spec">
        <xsl:variable name="fname" select="concat('x3g/',../@category, '/', ./@name, '/makefile')"/>
        <xsl:variable name="projmk" select="concat('project/',../@category, '/', ./@name, '/makefile')"/>
         <xsl:variable name="coding" select="jpw:getCoding(.)"/>
        <xsl:result-document method="text" href="{$fname}">
NAME=<xsl:value-of select="@name"/>
SERIES_NUM=<xsl:value-of select="../@number"/>
SPEC_NUM=<xsl:value-of select="@number"/>
<xsl:value-of select="concat($newline, 'URL=http://www.3gpp.org/ftp/Specs/archive/',../@number,'_series/',../@number,'.',@number)"/>

-include <xsl:value-of select="@name"/>.cfg

main: pom

pom: latest.xml
	xsl ${X3GPP_HOME}/meta/x3pom.xsl ${X3GPP_HOME}/<xsl:value-of select="$projmk"/> $&lt;

<xsl:value-of select="concat('latest.xml :',@name, '.xml')"/>
	xsl ${X3GPP_HOME}/meta/x3latest.xsl $@ $&lt;

<xsl:value-of select="concat(@name, '.xml : download/',@name, '.xml')"/>
	xsl ${X3GPP_HOME}/meta/x3cfg.xsl $@ $&lt;

<xsl:value-of select="concat('download/', @name, '.xml : download/',@name, '.xhtml')"/>
	xsl ${X3GPP_HOME}/meta/x3xml.xsl $@ $&lt; coding=<xsl:value-of select="$coding"/> name=<xsl:value-of select="concat(@name,$newline2)"/>  

<xsl:value-of select="concat('download/', @name, '.xhtml : download/',@name, '.html' )"/>
	cp $&lt; $@
	@sed -i 's/&lt;br&gt;/&lt;\/br&gt;&lt;br&gt;/g' $@
	@sed -i 's/&lt;hr&gt;/&lt;hr\/&gt;/g' $@
	@sed -i 's/&lt;pre&gt;/&lt;pre&gt;&lt;br&gt;/g' $@
	@sed -i 's/&lt;\/pre&gt;/&lt;\/br&gt;&lt;\/pre&gt;/g' $@

<xsl:value-of select="concat('download/', @name, '.html:')"/>
	mkdir -p download/
	wget ${URL} -q -O $@

clean:
	${RM} -rf <xsl:value-of select="concat(@name,'.xml')"/>
	${RM} -rf <xsl:value-of select="'latest.xml'"/>
	
cleanall:clean
	${RM} -rf <xsl:value-of select="concat('download/', @name,'.*')"/>

        </xsl:result-document>
        
        <xsl:variable name="cfgname" select="concat('x3g/',../@category, '/', ./@name, '/', @name,'.cfg')"/>
        <xsl:result-document method="text" href="{$cfgname}">
<xsl:value-of select="concat('CXX_OPTIONS=', $asn1cxx, $newline2)"/>
<xsl:value-of select="concat('JAVA_OPTIONS=', $asn1java, $newline2)"/>
        </xsl:result-document>
    </xsl:template>

    <xsl:template match="*"/>
    
    <xsl:function name="jpw:getCoding">
        <xsl:param name="node"/>
        <xsl:choose>
           <xsl:when test="$node/@coding">
               <xsl:value-of select="$node/@coding"/>
           </xsl:when>
           <xsl:when test="$node/../@coding">
               <xsl:value-of select="$node/../@coding"/>
           </xsl:when>
           <xsl:when test="$node/../../@coding">
               <xsl:value-of select="$node/../../@coding"/>
           </xsl:when>
           <xsl:otherwise>
               <xsl:value-of select="'PER'"/>
           </xsl:otherwise>
        </xsl:choose>
    </xsl:function>
    
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
