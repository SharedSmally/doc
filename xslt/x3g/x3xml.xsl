<xsl:stylesheet 
    xmlns:xsl="http://www.w3.org/1999/XSL/Transform" 
    xmlns:xs="http://www.w3.org/2001/XMLSchema"
    xmlns:jpw="http://www.jpw.com/product/app"
    version="2.0">

    <xsl:output method="xml" indent="yes"/>
    <xsl:strip-space elements="*"/>

    <xsl:variable name="newline"><xsl:text>
</xsl:text></xsl:variable>
     <xsl:param name="name" required="yes"/>
   
    <!-- Convert Series html tp xml, such as from  http://www.3gpp.org/ftp/Specs/archive/44_series/44.031/ -->
    <xsl:template match="/">
        <xsl:apply-templates/>
    </xsl:template>

    <xsl:template match="html">
        <xsl:variable name="t1" select="tokenize(head/title/text(), '-')"/>
        <x3gpp name="{$name}">
            <xsl:attribute name="site" select="normalize-space($t1[1])"/>
            <xsl:attribute name="ftp" select="normalize-space($t1[2])"/>
            <xsl:apply-templates select="body/pre/br"/>
        </x3gpp>
    </xsl:template>

    <xsl:template match="br">
        <xsl:variable name="t1" select="normalize-space(text())"/>
        <xsl:if test="string-length($t1)>0">
            <xsl:variable name="date" select="jpw:substring-before-last($t1,' ')"/>
            <xsl:variable name="size" select="jpw:substring-after-last($t1,' ')"/>
            <xsl:variable name="name" select="normalize-space(./A/text())"/>
            <xsl:variable name="dateStr" select="tokenize($date,' ')[1]"/>
            <xsl:variable name="dateStrs" select="tokenize($dateStr,'/')"/>
            <xsl:variable name="ver" select="tokenize($dateStr,'/')"/>
            <xsl:variable name="href" select="normalize-space(./A/@HREF)"/>
            
            <xsl:if test="ends-with($name, '.zip')">
                <spec>
                    <xsl:attribute name="size" select="$size"/>
                    <xsl:attribute name="name" select="$name"/>
                    <xsl:attribute name="href" select="$href"/>
                    <xsl:attribute name="date" select="$date"/>
                    <xsl:attribute name="year" select="$dateStrs[3]"/>
                    <xsl:attribute name="month" select="$dateStrs[1]"/>
                    <xsl:attribute name="day" select="$dateStrs[2]"/>
                    <xsl:attribute name="major" select="jpw:getX3gppVersion(substring($name,7,1))"/>
                    <xsl:attribute name="minor" select="jpw:getX3gppVersion(substring($name,8,1))"/>
                    <xsl:attribute name="patch" select="jpw:getX3gppVersion(substring($name,9,1))"/>
                </spec>
                
            </xsl:if>
        </xsl:if>
    </xsl:template>

    <xsl:template match="*"/>

    <xsl:function name="jpw:getX3gppVersion">
        <xsl:param name="v0"/>
        <xsl:choose>
           <xsl:when test="matches($v0, '\d')">
               <xsl:value-of select="$v0"/>
           </xsl:when>
           <xsl:when test="matches($v0, '[a-zA-Z]')">
               <xsl:value-of select="string-to-codepoints($v0)-87"/>
           </xsl:when>
        </xsl:choose>
    </xsl:function>

<xsl:function name="jpw:substring-before-last">
    <xsl:param name="input" as="xs:string"/>
    <xsl:param name="substr" as="xs:string"/>
    <xsl:sequence 
       select="if ($substr) 
               then 
                  if (contains($input, $substr)) then 
                  string-join(tokenize($input, $substr)
                    [position( ) ne last( )],$substr) 
                  else ''
               else $input"/>
</xsl:function>

<xsl:function name="jpw:substring-after-last">
    <xsl:param name="input" as="xs:string"/>
    <xsl:param name="substr" as="xs:string"/>
    <xsl:sequence 
    select="if ($substr) 
            then
               if (contains($input, $substr))
               then tokenize($input, $substr)[last( )] 
               else '' 
            else $input"/>
</xsl:function>

</xsl:stylesheet>
