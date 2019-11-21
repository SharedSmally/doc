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

    <xsl:template match="HTML">
        <xsl:apply-templates select="BODY/DIV[@id='sidebar-wrapper']" mode="side"/>
        <xsl:apply-templates select="BODY/DIV/DIV[@id='page-content-wrapper']"/>
    </xsl:template>

    <xsl:template match="BODY/DIV/DIV">  <!--  API Overview -->
       <xsl:variable name="date" select="tokenize(tokenize(DIV[1]/DIV[2]/DIV[1],': ')[2], '\s+')[1]"/>
       <xsl:variable name="version" select="tokenize(DIV[1]/DIV[2]/DIV[2],': ')[2]"/>
<k8sapi version="{$version}" date="{$date}">
           <xsl:apply-templates/>
</k8sapi>
    </xsl:template>
    
    <!-- example -->
    <xsl:template match="BODY/DIV/DIV/DIV">   
        <xsl:variable name="kube" select="DIV/DIV/PRE[@class='kubectl']"/>
        <xsl:variable name="curl" select="DIV/DIV/PRE[@class='curl']"/>
        <xsl:if test="string-length($kube)>0 or string-length($curl)>0">
<example name="{@id}">
            <xsl:if test="string-length($kube)>0">
    <xsl:value-of select="$kube"/>
            </xsl:if>
            <xsl:if test="string-length($curl)>0">
    <xsl:value-of select="$curl"/>
            </xsl:if>
</example>
        </xsl:if>
    </xsl:template>
 
    <xsl:template match="BODY/DIV/DIV/H1">
<group name="{text()}">
</group>
    </xsl:template>

    <!-- H2 could also be group -->
    <xsl:template match="BODY/DIV/DIV/H2">  <!-- following siblings: request/<P>; response: text or STRONG/text() -->
          <xsl:choose>
              <xsl:when test="count(STRONG)=0">
                 <xsl:variable name="desc" select="normalize-space(following-sibling::P[1]/text())"></xsl:variable>
                 <xsl:choose>
                    <xsl:when test="name(following-sibling::*[1])='TABLE'">
<group name="{text()}" id="{@id}" desc="{$desc}"/>
                    </xsl:when>
                    <xsl:otherwise>
<operation name="{text()}" id="{@id}" desc="{$desc}"/>
                    </xsl:otherwise>
                 </xsl:choose>
              </xsl:when>
              <xsl:otherwise>
                <xsl:variable name="name" select="STRONG"/>
<operations name="{$name}">
</operations>
              </xsl:otherwise>
          </xsl:choose>
    </xsl:template>

    <xsl:template match="BODY/DIV/DIV/H3">
<h3 name="{text()}">
   <xsl:if test="@id">
      <xsl:attribute name="id"><xsl:value-of select="@id"/></xsl:attribute>
   </xsl:if>
</h3>
    </xsl:template>

    <!--  Following HTTP Request -->
    <xsl:template match="BODY/DIV/DIV/CODE"> 
<request>
   <xsl:value-of select="text()"/>
</request>
    </xsl:template>
    
    <xsl:template match="BODY/DIV/DIV/TABLE">  <!--  latest previous sibling of H1, H2, H3; THEAD/TBODY -->
       <xsl:variable name="name" select="THEAD/TR/TH[1]/text()"/>  <!--  FIELD/DESC; Parameter/Desc; CODE/DESC; Group/Id/Kind    -->
         <xsl:choose>
             <xsl:when test="$name='Field'">
<resource>
             <xsl:apply-templates select="TBODY/TR"/>
</resource>
             </xsl:when>
             <xsl:when test="$name='Parameter'">
<parameter>
             <xsl:apply-templates select="TBODY/TR"/>
</parameter>
             </xsl:when>
             <xsl:when test="$name='Code'">
<response>
             <xsl:apply-templates select="TBODY/TR" mode="response"/>
</response>
             </xsl:when>

             <xsl:when test="$name='Group'">
                <xsl:apply-templates select="TBODY/TR" mode="category"/>
             </xsl:when> <!--  group/Version/Kind -->
             
             <xsl:otherwise>
<xsl:message>Unknown filed: <xsl:value-of select="$name"/></xsl:message>
             </xsl:otherwise>
         </xsl:choose>
    </xsl:template>

<!--  
 <TD><CODE>collisionCount</CODE><BR /><I>integer</I></TD><TD>collisionCount is the count of hash collisions for the StatefulSet. The StatefulSet controller uses this field as a collision avoidance mechanism when it needs to create the name for the newest ControllerRevision.</TD> 
-->
    <xsl:template match="TBODY/TR">
       <xsl:variable name="name" select="TD[1]/CODE[1]"/>
       <xsl:variable name="type" select="TD[1]/I[1]"/>
       <xsl:variable name="desc" select="TD[2]"/>
<field name="{$name}" type="{$type}">
    <xsl:value-of select="$desc"/>
</field>
    </xsl:template>

<!-- 
<TR><TD><CODE>networking.k8s.io</CODE></TD><TD><CODE>v1beta1</CODE></TD><TD><CODE>Ingress</CODE></TD></TR>
 -->
    <xsl:template match="TBODY/TR" mode="category">
       <xsl:variable name="group" select="TD[1]/CODE[1]"/>
       <xsl:variable name="version" select="TD[2]/CODE[1]"/>
       <xsl:variable name="kind" select="TD[3]/CODE[1]"/>
<category group="{$group}"  version="{$version}"  kind="{$kind}">

</category>
    </xsl:template>
<!-- 
<TR><TD>200<br /><I><a href="#cronjob-v1beta1-batch">CronJob</a></I></TD><TD>OK</TD></TR>
-->
    <xsl:template match="TBODY/TR" mode="response">
       <xsl:variable name="code" select="TD[1]/text()"/>
       <xsl:variable name="id" select="TD[1]/I[1]/a[1]/@href"/>
       <xsl:variable name="desc" select="TD[2]"/>
       <xsl:variable name="name" select="TD[1]//I[1]"/>
       
<code value="{$code}" id="{$id}" name="{$name}">
    <xsl:value-of select="$desc"/>
</code>
    </xsl:template>

    <xsl:template match="*">
    </xsl:template>
    <xsl:template match="BODY/DIV" mode="side">
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
