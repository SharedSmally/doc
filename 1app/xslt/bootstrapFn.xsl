<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet version="1.0"
   xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
   xmlns:xs="http://www.w3.org/2001/XMLSchema"
   xmlns:cpw="http://example.com">
   <xsl:include href="constants.xsl"/>


    <!--  grid: container/row/col  -->
    <xsl:function name="cpw:container" as="xs:string">
       <xsl:param name="container"/>

       <xsl:variable name="size" select="cpw:getBPClass('container',$container/@bp)"/>
       <xsl:variable name="text" select="cpw:getClass('text',$container/@text)"/>

       <xsl:value-of select="cpw:join( ($size, $text) )"/>
       <!--  <xsl:message>container @bp=<xsl:value-of select="$container/@bp"/></xsl:message>   -->
    </xsl:function>
    
    <!-- vertical align: align-items-*: align-self-*: start|center|end -->
    <!-- Horizontal align: justify-content-*: start|center|end|around|between:evenly -->
    <!--  Order: order-*; order-md-* -->
    <!-- additional row-cols-xxx -->
    <xsl:function name="cpw:row" as="xs:string">
       <xsl:param name="row"/>

       <xsl:variable name="size" select="cpw:getNodeSizesDefault('row',$row)"/>
       <xsl:variable name="cols" select="cpw:getRowColSizeClasses($row)"/>
       <xsl:variable name="align" select="cpw:getClass('align-items',$row/@align)"/>
       <xsl:variable name="salign" select="cpw:getClass('align-self',$row/@salign)"/>
       <xsl:variable name="justify" select="cpw:getClass('justify-content',$row/@justify)"/>
       
       <!-- order: order_xx -->
       <xsl:variable name="order" select="cpw:getOrder($row)"/>
       <!-- offset: offset_xx -->
       <xsl:variable name="offset" select="cpw:getOffset($row)"/>
       <!-- margin: me_xx: mb_xx; ms_xx -->
       <xsl:variable name="margin" select="cpw:getMargin($row)"/>

       <!-- gutter: gx_xx: gy_xx; g_xx -->
       <xsl:variable name="gx" select="cpw:getGutterX($row)"/>
       <xsl:variable name="gy" select="cpw:getGutterY($row)"/>
       <xsl:variable name="g"  select="cpw:getGutter($row)"/>
       
       <xsl:value-of select="cpw:join( ($size,$cols,$align,$salign,$justify,$order,$offset,$margin,$gx,$gy,$g) )"/>
    </xsl:function>
    
    <xsl:function name="cpw:column" as="xs:string">
       <xsl:param name="col"/>

       <xsl:variable name="size" select="cpw:getNodeSizesDefault('col',$col)"/>
       <xsl:variable name="align" select="cpw:getClass('align-items',$col/@align)"/>
       <xsl:variable name="salign" select="cpw:getClass('align-self',$col/@salign)"/>
       <xsl:variable name="justify" select="cpw:getClass('justify-content',$col/@justify)"/>

       <!-- order: order_xx -->
       <xsl:variable name="order" select="cpw:getOrder($col)"/>
       <!-- offset: offset_xx -->
       <xsl:variable name="offset" select="cpw:getOffset($col)"/>
       <!-- margin: me_xx: mb_xx; ms_xx -->
       <xsl:variable name="margin" select="cpw:getMargin($col)"/>

       <!-- gutter: gx_xx: gy_xx; g_xx -->
       <xsl:variable name="gx" select="cpw:getGutterX($col)"/>
       <xsl:variable name="gy" select="cpw:getGutterY($col)"/>
       <xsl:variable name="g"  select="cpw:getGutter($col)"/>
       
       <xsl:value-of select="cpw:join( ($size,$align,$salign,$justify,$order,$offset,$margin,$gx,$gy,$g) )"/>
    </xsl:function>

    
    <!--  grid: grid/col  -->
    <xsl:function name="cpw:grid" as="xs:string">
       <xsl:param name="grid"/>

       <xsl:variable name="size" select="cpw:getBPClass('grid',$grid/@bp)"/>
       <xsl:variable name="text" select="cpw:getClass('text',$grid/@text)"/>

       <xsl:value-of select="cpw:join( ($size, $text) )"/>
    </xsl:function>
    
    <!--  Section 1: grid: rows; cols; gaps -->
    <xsl:function name="cpw:gridStyle" as="xs:string">
       <xsl:param name="grid"/> 

       <xsl:variable name="rows" select="if ($grid/@rows) then concat('--bs-rows: ',$grid/@rows,';') else '' "/>
       <xsl:variable name="cols" select="if ($grid/@cols) then concat('--bs-columns: ',$grid/@cols,';') else '' "/>
       <xsl:variable name="gap" select="if ($grid/@gaps) then concat('--gap: ',$grid/@gap,';') else '' "/>
       <xsl:variable name="cgap" select="if ($grid/@cgaps) then concat('--row-gap: ',$grid/@cgap,';') else '' "/>
       <xsl:variable name="rgap" select="if ($grid/@rgaps) then concat('--column-gap: ',$grid/@rgap,';') else '' "/>

       <xsl:value-of select="cpw:join( ($rows, $cols,$gap,$rgap,$cgap) )"/>
    </xsl:function>
    
    <xsl:function name="cpw:gridCol" as="xs:string">
       <xsl:param name="col"/>

       <xsl:variable name="size" select="cpw:getNodeSizes('g-col',$col)"/>
       <xsl:variable name="start" select="cpw:getSizesClass('g-start',$col/@start,$col/@start_sm,$col/@start_md,$col/@start_lg,$col/@start_xl,$col/@start_xxl)"/>

       <xsl:value-of select="cpw:join( ($size, $start) )"/>
    </xsl:function>
    <xsl:function name="cpw:gridColStyle" as="xs:string">
       <xsl:param name="col"/> 
       <xsl:value-of select="if ($col/@col) then concat('--grid-column: ',$col/@col,';') else '' "/>
    </xsl:function>


    <!-- Form  -->
    <xsl:function name="cpw:form" as="xs:string">
       <xsl:param name="node"/>
       <xsl:value-of select="cpw:getSizesClass('row-cols',$node/@cxs,$node/@csm,$node/@cmd,$node/@clg,$node/@cxl,$node/@cxxl)"/>
    </xsl:function>
    <xsl:function name="cpw:button" as="xs:string">
       <xsl:param name="node"/>
       <xsl:variable name="color" select="cpw:getClass('btn',$node/@color)"/>
       <xsl:value-of select="cpw:join( ('btn', $color) )"/>
    </xsl:function>
    
    <!--  for row-cols-xxx-yyy -->
    <xsl:function name="cpw:getRowColSizeClasses" as="xs:string">
       <xsl:param name="node"/>
       <xsl:value-of select="cpw:getSizesClass('row-cols',$node/@cxs,$node/@csm,$node/@cmd,$node/@clg,$node/@cxl,$node/@cxxl)"/>
    </xsl:function>

    <!-- basic functions for BP based -->
    <!--  for order-xxx-yyy: first|last|-1|0-12 -->
    <xsl:function name="cpw:getOrder" as="xs:string">
       <xsl:param name="node"/>
       <xsl:value-of select="cpw:getSizesClass('order',$node/@order,$node/@order_sm,$node/@order_md,$node/@order_lg,$node/@order_xl,$node/@order_xxl)"/>
    </xsl:function>

    <!--  for offset-xxx-yyy: first|last|-1|0-12 -->
    <xsl:function name="cpw:getOffset" as="xs:string">
       <xsl:param name="node"/>
       <xsl:value-of select="cpw:getSizesClass('offset',$node/@offset,$node/@offset_sm,$node/@offset_md,$node/@offset_lg,$node/@offset_xl,$node/@offset_xxl)"/>
    </xsl:function>
    
    <!--  Margin: me|ms-xxx-yyy: auto|0-12 -->
    <xsl:function name="cpw:getMargin" as="xs:string">
       <xsl:param name="node"/>
       <xsl:value-of select="cpw:getSizesClass('me',$node/@me,$node/@me_sm,$node/@me_md,$node/@me_lg,$node/@me_xl,$node/@me_xxl)"/>
    </xsl:function>
    
    <!--  Horizontal gutters: gx-xx-*:0-12 -->
    <!--  Vertical gutters: gy-xx-*:0-12 -->
    <!--  Horizontal & Vertical gutters: g-xxx-*:0-12 -->
    <xsl:function name="cpw:getGutter" as="xs:string">
       <xsl:param name="node"/>
       <xsl:value-of select="cpw:getSizesClass('g',$node/@g,$node/@g_sm,$node/@g_md,$node/@g_lg,$node/@g_xl,$node/@g_xxl)"/>
    </xsl:function>
    <xsl:function name="cpw:getGutterX" as="xs:string">
       <xsl:param name="node"/>
       <xsl:value-of select="cpw:getSizesClass('gx',$node/@gx,$node/@gx_sm,$node/@gx_md,$node/@gx_lg,$node/@gx_xl,$node/@gx_xxl)"/>
    </xsl:function>
    <xsl:function name="cpw:getGutterY" as="xs:string">
       <xsl:param name="node"/>
       <xsl:value-of select="cpw:getSizesClass('gy',$node/@gy,$node/@gy_sm,$node/@gy_md,$node/@gy_lg,$node/@gy_xl,$node/@gy_xxl)"/>
    </xsl:function>



    <!--  get multiple sizes: such as col-sm-xx col-md-xx  -->
    <xsl:function name="cpw:getNodeSizesDefault" as="xs:string">
       <xsl:param name="prefix" as="xs:string"/>
       <xsl:param name="node"/>
       <xsl:variable name="size" select="cpw:getNodeSizes($prefix,$node)"/>
       
       <xsl:value-of select="if ($size='') then $prefix else $size"/>
    </xsl:function>

    <xsl:function name="cpw:getNodeSizes" as="xs:string">
       <xsl:param name="prefix" as="xs:string"/>
       <xsl:param name="node"/>
       <xsl:value-of select="cpw:getSizesClass('ms',$node/@xs,$node/@sm,$node/@md,$node/@lg,$node/@xl,$node/@xxl)"/>
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
       <xsl:value-of select="cpw:join( ($xs, $sm, $md, $lg, $xl, $xxl) )"/>
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
    
    <!-- breakpoint: container-(xsExtra small)/sm(Small)/md(Medium)/lg(Large)/xl(Extra large)/xxl(Extra extra large)/fluid(Full)
         attibute: @{bp}_xx or @xx_{bp} or @x{bp}
    -->
    <!--  get class: container-xx; text-xx; xs is default -->
    <xsl:function name="cpw:getBPClass" as="xs:string">
       <xsl:param name="prefix" as="xs:string"/>
       <xsl:param name="bp"/>
       <xsl:variable name="bp1" select="if ($bp) then $bp else ''"/>
       <xsl:variable name="bp2" select="if ($bp1='xs') then '' else $bp1"/>
       <xsl:value-of select="if ($bp2='') then $prefix else concat($prefix,'-',$bp2)"/>
    </xsl:function>

    <!--  get {prefix}-{attr} if ${attr} existing -->
    <xsl:function name="cpw:getClass" as="xs:string">
       <xsl:param name="prefix" as="xs:string"/>
       <xsl:param name="val"/>
       <xsl:value-of select="if ($val) then concat($prefix,'-',$val) else ''"/>
    </xsl:function>
    
    <xsl:function name="cpw:getDefault" as="xs:string">
       <xsl:param name="val" as="xs:string"/>
       <xsl:param name="def" as="xs:string"/>
       <xsl:value-of select="if ($val) then $val else $def"/>
    </xsl:function>
    
    <xsl:function name="cpw:join" as="xs:string">
       <xsl:param name="strs"/>
       <xsl:value-of select="normalize-space(string-join(($strs), ' ') )"/>
    </xsl:function>
    
</xsl:stylesheet>



<!-- 
    <xsl:if test="$size = 'xs'"><xsl:value-of select="'container'"/></xsl:if>
    <xsl:if test="$size != 'xs'"><xsl:value-of select="concat('container-',$size)"/></xsl:if>
replaced by
    <xsl:value-of select="if ($size='xs') then 'container' else concat('container-',$size)"/>
-->
