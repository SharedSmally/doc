<?xml version="1.0" encoding="UTF-8"?>
<!-- 
   generate java classes for DAO.
   command line args: srcdir=xxx  
 -->
<xsl:stylesheet version="2.0"
    xmlns="http://www.jpw.com/app/dao.xsd"
    xmlns:xs="http://www.w3.org/2001/XMLSchema"
    xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" 
    xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
    xmlns:jpw="http://www.jpw.com/x2j"
    >
    
    <xsl:output method="xml" indent="yes" version="1.0" encoding="UTF-8" />

    <!-- Pretty Print Output: omit-xml-declaration="yes" -->
    <xsl:strip-space elements="*" />

    <xsl:variable name='newline' select="'&#xA;'"/>
    <xsl:variable name='separator' select="' '"/>
    <xsl:variable name='sps' select="'    '"/>
    <xsl:variable name='sps2' select="concat($sps,$sps)"/>
    <xsl:variable name='sps3' select="concat($sps2,$sps)"/>
    <xsl:variable name='sps4' select="concat($sps2,$sps2)"/>

    <!-- base namespace. -->
    <xsl:variable name="basens" select="'com.jpw.'" />

    <!-- Receives the baseDir. -->
    <xsl:param name="srcdir" select="'src'" />

    <!--  templates  -->
    <xsl:template match="/">
        <xsl:apply-templates/> 
    </xsl:template>
    
    <xsl:template match="dao">
        <xsl:variable name="fullns" select="concat($basens,./@id)" />
        <xsl:variable name="nsdir" select="jpw:nspath($fullns)" />
        <xsl:for-each select="enum|struct|class">
            <xsl:variable name="name" select="jpw:ucfirst(@name)" />
            <xsl:variable name="fname" select="concat($nsdir, '/', $name,'.java')" />
            <xsl:result-document method="text" href="{$fname}">
                <xsl:value-of select="concat('package ', $fullns, ';', $newline,$newline)"/>
                <xsl:if test="count(../import)>0">
                    <xsl:apply-templates select="../import"/>
                    <xsl:value-of select="$newline"/>
                </xsl:if>
                <xsl:if test="count(./import)>0">
                    <xsl:apply-templates select="./import"/>
                    <xsl:value-of select="$newline"/>
                </xsl:if>
                <xsl:apply-templates select="."/>
            </xsl:result-document>
        </xsl:for-each>

        <java>
            <xsl:attribute name="namespace"><xsl:value-of select="$fullns"/></xsl:attribute>
            <xsl:attribute name="path"><xsl:value-of select="$nsdir"/></xsl:attribute>
             
             <xsl:if test="count(./enum)>0">
                  <enum> <xsl:value-of select="jpw:join(./enum, 'name')"/></enum>
            </xsl:if>
            <xsl:if test="count(./class)>0">
                <class> <xsl:value-of select="jpw:join(./class, 'name')"/></class>
            </xsl:if>
            <xsl:if test="count(./struct)>0">
                <struct> <xsl:value-of select="jpw:join(./struct, 'name')"/></struct>
            </xsl:if>
        </java>
    </xsl:template>
    
    <xsl:template match="import">
        <xsl:variable name="ns" select="@namespace"/>
        <xsl:for-each select="tokenize(./text(),$separator)">
            <xsl:value-of select="concat('import ', $ns, '.', .,';', $newline)"/>
        </xsl:for-each>
    </xsl:template>
    
    <!-- 
    <xsl:template match="desc">
       <xsl:message >desc </xsl:message>
    </xsl:template>
    <xsl:template match="description">
       <xsl:message >detail desc </xsl:message>
    </xsl:template>
    -->

    <xsl:template match="enum">
        <xsl:variable name="name" select="jpw:ucfirst(./@name)" />
        <xsl:variable name="base" select="jpw:getBase(.)"/>

        <xsl:value-of select="concat('public enum ', $name, $newline, '{', $newline)"/>

        <xsl:variable name="items" select="./item"/>
        <xsl:for-each select="$items">
            <xsl:value-of select="concat($sps, ./@name, ' ( ', jpw:getEnumValue($items, position()), ' )')"/>
            <xsl:choose>
                <xsl:when test="position()=last()"><xsl:value-of select="';'"/> </xsl:when>
                <xsl:otherwise><xsl:value-of select="','"/> </xsl:otherwise>
            </xsl:choose>
            <xsl:value-of select="$newline"/>
        </xsl:for-each>
        <!--   <xsl:apply-templates/>    -->
        
        <xsl:value-of select="concat($newline, $sps, 'public ', $base, ' getValue()', $newline)"/>
        <xsl:value-of select="concat($sps, '{', $newline)"/>
        <xsl:value-of select="concat($sps2, 'return value_ ;', $newline)"/>
        <xsl:value-of select="concat($sps, '}', $newline)"/>

        <xsl:value-of select="concat($newline, $sps, 'private ', $base, ' value_;', $newline)"/>
        
        <xsl:value-of select="concat($newline, $sps, $name, '( ', $base, ' value )', $newline)"/>
        <xsl:value-of select="concat($sps, '{', $newline)"/>
        <xsl:value-of select="concat($sps2, 'value_ = value; ', $newline)"/>
        <xsl:value-of select="concat($sps, '}', $newline)"/>
        
        <xsl:value-of select="concat('}', $newline)"/>
    </xsl:template>
    
    <!-- 
    <xsl:template match="item">
        <xsl:variable name="name" select="jpw:ucfirst(@name)" />
        <xsl:variable name="val" select="jpw:ucfirst(@value)" />
        <xsl:value-of select="concat(' ', $name, ' = ', $val, ';', $newline)"/>
    </xsl:template>
    -->

    <!-- struct -->
    <xsl:template match="class">
        <xsl:variable name="name" select="jpw:ucfirst(./@name)" />
        <xsl:value-of select="concat('public class ', $name, $newline, '{', $newline)"/>
        <xsl:apply-templates  mode="class"/>
        <xsl:value-of select="concat('}',$newline)"/>
    </xsl:template>

    <xsl:template match="struct">
        <xsl:variable name="name" select="jpw:ucfirst(./@name)" />
        <xsl:value-of select="concat('public class ', $name, $newline, '{', $newline)"/>
        <xsl:apply-templates mode="struct"/>
        <xsl:value-of select="concat('}',$newline)"/>
    </xsl:template>

    <xsl:template match="elem" mode="class">
        <xsl:variable name="name" select="@name" />
        <xsl:variable name="type" select="@type" />
        <xsl:variable name="size" select="@size" />
        
        <xsl:choose>
            <xsl:when test="$size='*'">
                <xsl:value-of select="jpw:listGetSet($name,$type)"/>
            </xsl:when>
            <xsl:when test="$size='0'">
                <xsl:value-of select="jpw:optionalGetSet($name,$type)"/>
            </xsl:when>
            <xsl:when test="$size='1' or not($size)">
                <xsl:value-of select="jpw:singleGetSet($name,$type)"/>
            </xsl:when>
            <xsl:otherwise>
                <xsl:value-of select="jpw:arrayGetSet($name,$type,$size)"/>
            </xsl:otherwise>
        </xsl:choose>
        
        <xsl:text>class {$name};</xsl:text>
    </xsl:template>

    
    <xsl:template match="elem" mode="struct">
        <xsl:variable name="name" select="jpw:ucfirst(@name)" />
        <xsl:variable name="type" select="jpw:ucfirst(@type)" />
        <xsl:value-of select="concat($sps, 'public ', $type, ' ', $name, ';', $newline)"/>
    </xsl:template>

    <xsl:template match="*" mode="class struct">
    </xsl:template>

<!-- functions -->
<xsl:function name = "jpw:getBase">
    <xsl:param name="node" />
    <xsl:choose>
        <xsl:when test="$node/@base">
            <xsl:value-of select="$node/@base"/>
        </xsl:when>
        <xsl:otherwise>
            <xsl:value-of select="'int'"/>
        </xsl:otherwise>
    </xsl:choose>
</xsl:function>

<xsl:function name = "jpw:nspath">
    <xsl:param name="ns" />
    <xsl:variable name="nsdir" select="replace($ns,'\.','/')" />
    <xsl:choose>
        <xsl:when test="$srcdir and ends-with($srcdir,'/')">
            <xsl:value-of select="concat($srcdir,$nsdir)"/>
        </xsl:when>
        <xsl:when test="$srcdir and not(ends-with($srcdir,'/'))">
            <xsl:value-of select="concat($srcdir,'/',$nsdir)"/>
        </xsl:when>
        <xsl:otherwise>
            <xsl:value-of select="$nsdir"/>
        </xsl:otherwise>
    </xsl:choose> 
</xsl:function>

<xsl:function name = "jpw:ucfirst">
    <xsl:param name="str" />
    <xsl:value-of select="concat(upper-case(substring($str, 1, 1)), substring($str, 2))" />
</xsl:function>
   
<xsl:function name = "jpw:join">
    <xsl:param name="nodes" />
    <xsl:param name="attrname" />
    <xsl:for-each select="$nodes">
        <xsl:if test="position() != 1">,</xsl:if><xsl:value-of select="@*[name() = $attrname]"/>
    </xsl:for-each>
</xsl:function>

<xsl:function name = "jpw:getEnumValue">
    <xsl:param name="nodes" />
    <xsl:param name="pos" />
    
    <xsl:variable name="node" select="$nodes[position()=$pos]" />
    <xsl:variable name="preInd" select="jpw:dec($pos)" />
    
    <xsl:choose>
        <xsl:when test="$node/@value">
            <xsl:value-of select="$node/@value"/>
        </xsl:when>
        <xsl:when test="($pos=1) and ($node/../@start)">
            <xsl:value-of select="$node/../@start"/>
        </xsl:when>
        <xsl:when test="$pos>1">
            <xsl:value-of select="jpw:inc(jpw:getEnumValue($nodes,$preInd))"/>
        </xsl:when>
        <xsl:otherwise>
            <xsl:value-of select="'0'"/>
        </xsl:otherwise>
    </xsl:choose>

</xsl:function>

<!-- math ops: number,floor,ceiling,abs -->
<xsl:function name="jpw:dec">
    <xsl:param name="val"/>
    <xsl:value-of select="floor(number($val) - number(1))" />
</xsl:function>
<xsl:function name="jpw:inc">
    <xsl:param name="val"/>
    <xsl:value-of select="floor(number($val) + number(1))" />
</xsl:function>


    <!--  optional:0; mandatory:1; fixedSize:n; variedSize:* -->
    <xsl:function name="jpw:optionalGetSet">
        <xsl:param name="name"/>
        <xsl:param name="type"/>
        <xsl:variable name="uname" select="jpw:ucfirst($name)" />
        
        <xsl:value-of select="concat($sps, 'protected ', $type, ' ', $name, ' = null;', $newline)"/>
        
        <xsl:value-of select="concat($newline, $sps,'public ', $type, ' get', $uname,'( )', $newline)"/>
        <xsl:value-of select="concat($sps, '{', $newline)"/>
        <xsl:value-of select="concat($sps2, 'return ',$name, ';', $newline)"/>
        <xsl:value-of select="concat($sps, '}', $newline)"/>

        <xsl:value-of select="concat($newline, $sps, 'public void set', $uname,'( ', $type, ' value )', $newline)"/>
        <xsl:value-of select="concat($sps, '{', $newline)"/>
        <xsl:value-of select="concat($sps2, $name, ' = value; ', $newline)"/>
        <xsl:value-of select="concat($sps, '}', $newline)"/>

        <xsl:value-of select="concat($newline, $sps,'public boolean has', $uname,'( )', $newline)"/>
        <xsl:value-of select="concat($sps, '{', $newline)"/>
        <xsl:value-of select="concat($sps2, 'return ',$name, ' != null;', $newline)"/>
        <xsl:value-of select="concat($sps, '}', $newline)"/>
    </xsl:function>

    <xsl:function name="jpw:singleGetSet">
        <xsl:param name="name"/>
        <xsl:param name="type"/>
        <xsl:variable name="uname" select="jpw:ucfirst($name)" />
        
        <xsl:value-of select="concat($sps, 'protected ', $type, ' ', $name, ';', $newline)"/>
        
        <xsl:value-of select="concat($newline, $sps,'public ', $type, ' get', $uname,'( )', $newline)"/>
        <xsl:value-of select="concat($sps, '{', $newline)"/>
        <xsl:value-of select="concat($sps2, 'return ',$name, ';', $newline)"/>
        <xsl:value-of select="concat($sps, '}', $newline)"/>

        <xsl:value-of select="concat($newline, $sps, 'public void set', $uname,'( ', $type, ' value )', $newline)"/>
        <xsl:value-of select="concat($sps, '{', $newline)"/>
        <xsl:value-of select="concat($sps2, $name, ' = value; ', $newline)"/>
        <xsl:value-of select="concat($sps, '}', $newline)"/>
    </xsl:function>
    <xsl:function name="jpw:arrayGetSet">
        <xsl:param name="name"/>
        <xsl:param name="type"/>
        <xsl:param name="size"/>
        <xsl:variable name="uname" select="jpw:ucfirst($name)" />
        
        <xsl:value-of select="concat($sps, 'protected ', $type, '[] ', $name, ' = new ', $type,'[',$size,'];', $newline)"/>

        <xsl:value-of select="concat($newline, $sps,'public ', $type, '[] get', $uname,'( )', $newline)"/>
        <xsl:value-of select="concat($sps, '{', $newline)"/>
        <xsl:value-of select="concat($sps2, 'return ',$name, ';', $newline)"/>
        <xsl:value-of select="concat($sps, '}', $newline)"/>

        <xsl:value-of select="concat($newline, $sps,'public ', $type, ' get', $uname,'( int index )', $newline)"/>
        <xsl:value-of select="concat($sps, '{', $newline)"/>
        <xsl:value-of select="concat($sps2, 'return ',$name, '[ index ];', $newline)"/>
        <xsl:value-of select="concat($sps, '}', $newline)"/>

        <xsl:value-of select="concat($newline, $sps, 'public void set', $uname,'( ', $type, ' v, int index )', $newline)"/>
        <xsl:value-of select="concat($sps, '{', $newline)"/>
        <xsl:value-of select="concat($sps2, $name, '[ index ] = v; ', $newline)"/>
        <xsl:value-of select="concat($sps, '}', $newline)"/>
    </xsl:function>
    
    <xsl:function name="jpw:listGetSet">
        <xsl:param name="name"/>
        <xsl:param name="type"/>
        <xsl:variable name="uname" select="jpw:ucfirst($name)" />
        
        <xsl:value-of select="concat($sps, 'protected List&lt;', $type, '&gt; ', $name, ' = new ArrayList&lt;',$type,'&gt;();', $newline)"/>
        
        <xsl:value-of select="concat($newline, $sps,'public List&lt;', $type, '&gt; get', $uname,'( )', $newline)"/>
        <xsl:value-of select="concat($sps, '{', $newline)"/>
        <xsl:value-of select="concat($sps2, 'return ',$name, ';', $newline)"/>
        <xsl:value-of select="concat($sps, '}', $newline)"/>

        <xsl:value-of select="concat($newline, $sps, 'public void clear', $uname,'( )', $newline)"/>
        <xsl:value-of select="concat($sps, '{', $newline)"/>
        <xsl:value-of select="concat($sps2, $name, '.clear(); ', $newline)"/>
        <xsl:value-of select="concat($sps, '}', $newline)"/>

        <xsl:value-of select="concat($newline, $sps, 'public void add', $uname,'( ', $type, ' v )', $newline)"/>
        <xsl:value-of select="concat($sps, '{', $newline)"/>
        <xsl:value-of select="concat($sps2, $name, '.add(v); ', $newline)"/>
        <xsl:value-of select="concat($sps, '}', $newline)"/>

    </xsl:function>
 
</xsl:stylesheet>
