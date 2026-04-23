<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet version="1.0"
	xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
	xmlns:xs="http://www.w3.org/2001/XMLSchema"
	xmlns:cpw="http://example.com">
	<xsl:include href="constants.xsl"/>
	
	
	<!-- breakpoint: container-(xsExtra small)/sm(Small)/md(Medium)/lg(Large)/xl(Extra large)/xxl(Extra extra large)/fluid(Full)
	     attibute: @{bp}_xx or @xx_{bp} or @x{bp}
	 -->
    <xsl:function name="cpw:getClass" as="xs:string">
       <xsl:param name="prefix" as="xs:string"/>
       <xsl:param name="val"/>
       <xsl:value-of select="if ($val) then concat($prefix,'-',$val) else ''"/>
    </xsl:function>
    
	<!--  get class: container-xx; text-xx -->
    <xsl:function name="cpw:getBPClass" as="xs:string">
       <xsl:param name="prefix" as="xs:string"/>
       <xsl:param name="bp"/>
       <xsl:variable name="bp1" select="if ($bp) then $bp else ''"/>
       <xsl:variable name="bp2" select="if ($bp1='xs') then '' else $bp1"/>
       <xsl:value-of select="if ($bp2='') then $prefix else concat($prefix,'-',$bp2)"/>
    </xsl:function>

    <xsl:function name="cpw:getContainerClass" as="xs:string">
       <xsl:param name="container"/>
       <xsl:value-of select="cpw:getBPClass('container',$container/@size)"/>
       <xsl:message>container @size=<xsl:value-of select="$container/@size"/></xsl:message>
    </xsl:function>

    <!--  size: xs/sm/md/lg/xl/xxl-{}=size: size=0,1-12,auto -->
    <xsl:function name="cpw:getSizeClass" as="xs:string">
       <xsl:param name="prefix" as="xs:string"/>
       <xsl:param name="size"/>
       <xsl:choose>
          <xsl:when test="$size"><xsl:value-of select="if ($size='') then $prefix else concat($prefix,'-',$size)"/></xsl:when>
         <xsl:otherwise><xsl:value-of select="''"/></xsl:otherwise>
       </xsl:choose>
    </xsl:function>
    <xsl:function name="cpw:getSizesClass" as="xs:string">
       <xsl:param name="prefix" as="xs:string"/>
       <xsl:param name="xsval"/>
       <xsl:param name="smval"/>
       <xsl:param name="mdval"/>
       <xsl:param name="lgval"/>
       <xsl:param name="xlval"/>
       <xsl:param name="xxlval"/>
       <xsl:variable name="xs" select="cpw:getSizeClass($prefix,$xsval)"/>
       <xsl:variable name="sm" select="cpw:getSizeClass(concat($prefix,'-sm'),$smval)"/>
       <xsl:variable name="md" select="cpw:getSizeClass(concat($prefix,'-md'),$mdval)"/>
       <xsl:variable name="lg" select="cpw:getSizeClass(concat($prefix,'-lg'),$lgval)"/>
       <xsl:variable name="xl" select="cpw:getSizeClass(concat($prefix,'-xl'),$xlval)"/>
       <xsl:variable name="xxl" select="cpw:getSizeClass(concat($prefix,'-xxl'),$xxlval)"/>
       <xsl:value-of select="normalize-space(string-join( ($xs, $sm, $md, $lg, $xl, $xxl), ' '))"/>
    </xsl:function>


    <xsl:function name="cpw:getSizeClasses" as="xs:string">
       <xsl:param name="prefix" as="xs:string"/>
       <xsl:param name="node"/>
       <xsl:variable name="xs" select="cpw:getSizeClass($prefix,$node/@xs)"/>
       <xsl:variable name="sm" select="cpw:getSizeClass(concat($prefix,'-sm'),$node/@sm)"/>
       <xsl:variable name="md" select="cpw:getSizeClass(concat($prefix,'-md'),$node/@md)"/>
       <xsl:variable name="lg" select="cpw:getSizeClass(concat($prefix,'-lg'),$node/@lg)"/>
       <xsl:variable name="xl" select="cpw:getSizeClass(concat($prefix,'-xl'),$node/@xl)"/>
       <xsl:variable name="xxl" select="cpw:getSizeClass(concat($prefix,'-xxl'),$node/@xxl)"/>
       <xsl:variable name="items" select="($xs, $sm, $md, $lg, $xl, $xxl)" />
       <xsl:variable name="size" select="normalize-space(string-join( $items, ' '))"/>
       <xsl:value-of select="if ($size='') then $prefix else $size"/>
    </xsl:function>
    
    <!--  for row-cols-xxx-yyy -->
    <xsl:function name="cpw:getRowColSizeClasses" as="xs:string">
       <xsl:param name="node"/>
       <xsl:value-of select="cpw:getSizesClass('row-cols',$node/@cxs,$node/@csm,$node/@cmd,$node/@clg,$node/@cxl,$node/@cxxl)"/>
    </xsl:function>

    <!--  for order-xxx-yyy: first|last|-1|0-12 -->
    <xsl:function name="cpw:getOrder" as="xs:string">
       <xsl:param name="node"/>
       <xsl:value-of select="cpw:getSizesClass('order',$node/@xs,$node/@sm,$node/@md,$node/@lg,$node/@xl,$node/@xxl)"/>
    </xsl:function>

    <!--  for offset-xxx-yyy: first|last|-1|0-12 -->
    <xsl:function name="cpw:getOffset" as="xs:string">
       <xsl:param name="node"/>
       <xsl:value-of select="cpw:getSizesClass('offset',$node/@xs,$node/@sm,$node/@md,$node/@lg,$node/@xl,$node/@xxl)"/>
    </xsl:function>
    
    <!--  Margin: me|ms-xxx-yyy: auto|0-12 -->
    <xsl:function name="cpw:getMargin" as="xs:string">
       <xsl:param name="node"/>
       <xsl:value-of select="cpw:getSizesClass('ms',$node/@xs,$node/@sm,$node/@md,$node/@lg,$node/@xl,$node/@xxl)"/>
    </xsl:function>
    
    <!--  Horizontal gutters: gx-xx-*:0-12 -->
    <!--  Vertical gutters: gy-xx-*:0-12 -->
    <!--  Horizontal & Vertical gutters: g-xxx-*:0-12 -->
    <xsl:function name="cpw:getGutter" as="xs:string">
       <xsl:param name="node"/>
       <xsl:value-of select="cpw:getSizesClass('g',$node/@xs,$node/@sm,$node/@md,$node/@lg,$node/@xl,$node/@xxl)"/>
    </xsl:function>
    <xsl:function name="cpw:getGutterX" as="xs:string">
       <xsl:param name="node"/>
       <xsl:value-of select="cpw:getSizesClass('gx',$node/@xs,$node/@sm,$node/@md,$node/@lg,$node/@xl,$node/@xxl)"/>
    </xsl:function>
    <xsl:function name="cpw:getGutterY" as="xs:string">
       <xsl:param name="node"/>
       <xsl:value-of select="cpw:getSizesClass('gy',$node/@xs,$node/@sm,$node/@md,$node/@lg,$node/@xl,$node/@xxl)"/>
    </xsl:function>
    
    <!-- vertical align: align-items-*: align-self-*: start|center|end -->
    <!-- Horizontal align: justify-content-*: start|center|end|around|between:evenly -->
    <!--  Order: order-*; order-md-* -->
    
    <!-- additional row-cols-xxx -->
    <xsl:function name="cpw:getRowClass" as="xs:string">
       <xsl:param name="row"/>
       <xsl:variable name="size" select="cpw:getSizeClasses('row',$row)"/>
       <xsl:variable name="cols" select="cpw:getRowColSizeClasses($row)"/>
       
       <xsl:variable name="align" select="cpw:getClass('align-items',$row/@align)"/>
       <xsl:variable name="salign" select="cpw:getClass('align-self',$row/@salign)"/>
       <xsl:variable name="justify" select="cpw:getClass('justify-content',$row/@justify)"/>
       
       <xsl:value-of select="normalize-space(string-join(($size,$cols,$align,$salign,$justify), ' ') )"/>
    </xsl:function>
    
    <xsl:function name="cpw:getColumnClass" as="xs:string">
       <xsl:param name="col"/>
       <xsl:variable name="size" select="cpw:getSizeClasses('col',$col)"/>
       <xsl:variable name="align" select="cpw:getClass('align-items',$col/@align)"/>
       <xsl:variable name="salign" select="cpw:getClass('align-self',$col/@salign)"/>
       <xsl:variable name="justify" select="cpw:getClass('justify-content',$col/@justify)"/>
       <xsl:value-of select="normalize-space(string-join(($size,$align,$salign,$justify), ' ') )"/>
    </xsl:function>
</xsl:stylesheet>
