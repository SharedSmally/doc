<xsl:stylesheet
    xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
    xmlns:xs="http://www.w3.org/2001/XMLSchema"
    exclude-result-prefixes="xs"
    version="2.0">

    <xsl:output method="text" indent="yes"/>
    <xsl:strip-space elements="*"/>
    <xsl:param name="url"/>
    <xsl:variable name="sps" select="'                   '"/>
    <xsl:variable name="tab"><xsl:text>	</xsl:text></xsl:variable>
    <xsl:variable name="newline"><xsl:text>
</xsl:text></xsl:variable>
    <xsl:variable name="newline2"><xsl:text>

</xsl:text></xsl:variable>


    <xsl:template match="/">
        <xsl:apply-templates/>
    </xsl:template>

    <xsl:template match="ansible">
URL=<xsl:value-of select="$url"/>
TARGETS = \
<xsl:apply-templates select="modules[@category='index']"/>

clean:
	${RM} ${TARGETS}

    </xsl:template>

    <xsl:template match="modules">
        <xsl:apply-templates/>
    </xsl:template>

    <xsl:template match="module">
       <xsl:variable name="name" select="lower-case(replace(@name,' ',''))"/>
       <xsl:variable name="href" select="@href"/>
       <xsl:variable name="suffix" select="substring($sps,1, string-length($sps)-string-length($name))"/>
       <xsl:value-of select="concat('    ', $name, $suffix, '\', $newline)"/>

       <xsl:result-document method="text" href="{concat($name, '/makefile')}">
          <xsl:value-of select="concat('NAME=', $name, $newline)"/>
          <xsl:value-of select="concat('URL=', $url,'/', $href, $newline2)"/>
          <xsl:value-of select="concat('main:', $name,'.xml',$newline2)"/>
          <xsl:value-of select="concat($name, '.xml: ', $name,'H.xml', $newline)"/>
          <xsl:value-of select="concat($tab, 'xsl ../module.xsl $&lt; $@', $newline2)"/>
          <xsl:value-of select="concat($name, 'H.xml:')"/><xsl:text>
	@wget ${URL} -O $@
	@sed -i '92,94d' $@
	@sed -i '77d' $@
	@sed -i '62d' $@
	@sed -i '49d' $@
	@sed -i '48d' $@
	@sed -i '9d' $@
	@sed -i '7d' $@
	@sed -i '/DOCTYPE html/d' $@
	@sed -i '/title="Commands modules"/d' $@
	@sed -i '/---/d' $@
	@sed -i 's/ &amp; / \&amp;amp; /g' $@
	@sed -i 's/ &amp;&amp; / \&amp;amp;\&amp;amp; /g' $@
	@sed -i 's/ &amp;mdash; / - /g' $@
	@sed -i 's/ &amp;raquo;/ /g' $@
	@sed -i 's/ &amp;copy;/ /g' $@
	
clean:
	${RM} ${NAME}.xml
	
cleanall: clean
	${RM} ${NAME}H.xml
</xsl:text>

       </xsl:result-document>
    </xsl:template>
          
    <xsl:template match="*"/>
</xsl:stylesheet>
