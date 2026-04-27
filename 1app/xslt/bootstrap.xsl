<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet version="1.0"
	xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
	xmlns:cpw="http://example.com">
	<xsl:include href="bootstrapFn.xsl"/>
	<xsl:output method="html" indent="yes" version="4.0" />
	
	<!--  match root / -->
	<xsl:template match="/">
	    <xsl:text disable-output-escaping='yes'>&lt;!doctype html&gt;&#xa;</xsl:text>
	    <xsl:apply-templates/>
	</xsl:template>
	
	<!--  match  /page -->
	<xsl:template match="/page">
		<html lang="en">
			<head>
				<meta charset="utf-8" />
				<meta name="viewport" content="width=device-width, initial-scale=1" />
				<title><xsl:value-of select="@title"/></title>
				<link href="https://cdn.jsdelivr.net/npm/bootstrap@5.3.8/dist/css/bootstrap.min.css" 
				   rel="stylesheet" integrity="sha384-sRIl4kxILFvY47J16cr9ZwB07vP4J8+LH7qKQnuqkuIAvNWLzeN8tE5YBujZqJLB" 
				   crossorigin="anonymous"/>
			</head>
			<body>
			    <xsl:apply-templates/>
			    <!-- Optional JavaScript; choose one of the two! -->
			    <!-- Option 1: Bootstrap Bundle with Popper -->
			    <script src="https://cdn.jsdelivr.net/npm/bootstrap@5.3.8/dist/js/bootstrap.bundle.min.js" integrity="sha384-FKyoEForCGlyvwx9Hj09JcYn3nv7wiPVlz7YYwJrWVcXK/BmnVDxM+D2scQbITxI" crossorigin="anonymous"></script>
			    <!-- Option 2: Separate Popper and Bootstrap JS -->
				<!--
				<script src="https://cdn.jsdelivr.net/npm/@popperjs/core@2.11.8/dist/umd/popper.min.js" integrity="sha384-I7E8VVD/ismYTF4hNIPjVp/Zjvgyol6VFvRkX/vR+Vc4jQkC+hVqc2pM8ODewa9r" crossorigin="anonymous"></script>
				<script src="https://cdn.jsdelivr.net/npm/bootstrap@5.3.8/dist/js/bootstrap.min.js" integrity="sha384-G/EV+4j2dNv+tEPo3++6LCgdCROaejBqfUeNjuKAiuXbjrxilcCdDz6ZAVfHWe1Y" crossorigin="anonymous"></script>
				-->
			</body>
		</html>
	</xsl:template>
	
<!-- section 1:  match  container/row/col -->
	<xsl:template match="container">
		<div class="{cpw:container(.)}">
			<xsl:apply-templates/>
		</div>
	</xsl:template>
	<xsl:template match="container/row"> <!--  size; cols= -->
		<div class="{cpw:row(.)}">
			<xsl:apply-templates/>
		</div>
	</xsl:template>
	<xsl:template match="container/row/col">
		<div class="{cpw:column(.)}">
			<xsl:apply-templates/>
		</div>	
	</xsl:template>
	
<!--  section 1: match  grid/col -->
	<xsl:template match="grid">
		<div class="{cpw:grid(.)}">
		     <xsl:variable name="style" select="cpw:gridStyle(.)"/>
		     <xsl:if test="$style"><xsl:attribute name="style"><xsl:value-of select="$style"/></xsl:attribute></xsl:if>
			<xsl:apply-templates/>
		</div>
	</xsl:template>
	<xsl:template match="grid/col"> <!--  size; cols= -->
		<div class="{cpw:gridCol(.)}">
		   <xsl:variable name="col" select="cpw:gridCol(.)"/>
		   <xsl:if test="$col"><xsl:attribute name="class"><xsl:value-of select="$col"/></xsl:attribute></xsl:if>
		   <xsl:apply-templates/>
		</div>
	</xsl:template>
	
<!--  section 2: match  form -->	
	<xsl:template match="form"> 
		<form>
		   <xsl:apply-templates/>
		</form>
	</xsl:template>
	<!--  form-control-{bp}; disabled/readonly -->
	<xsl:template match="label"> 
		     <xsl:variable name="id" select="cpw:getDefault(@id,@name)"/>
		     <xsl:variable name="label" select="@label"/>
		     <xsl:variable name="disable" select="cpw:getDefault(@disable,'false')"/>
		     
		     <label for="{$id}" class="form-label"><xsl:value-of select="$label"/></label>
	</xsl:template>
	<xsl:template match="password"> 
		<div class="mb-3">
		     <xsl:variable name="id" select="cpw:getDefault(@id,@name)"/>
		     <xsl:variable name="name" select="cpw:getDefault(@name,@id)"/>
		     <xsl:variable name="label" select="@label"/>
		     <xsl:variable name="disable" select="cpw:getDefault(@disable,'false')"/>
		     
		     <xsl:if test="$label"><label for="{$id}" class="form-label"><xsl:value-of select="$label"/></label></xsl:if>
             <input type="password" class="form-control" id="{$id}">
                <xsl:if test="$disable='true'"><xsl:attribute name="disabled"><xsl:value-of select="$disable"/></xsl:attribute></xsl:if>
             </input>
		</div>
	</xsl:template>
	<xsl:template match="input"> 
		<div class="mb-3">
		     <xsl:variable name="id" select="cpw:getDefault(@id,@name)"/>
		     <xsl:variable name="name" select="cpw:getDefault(@name,@id)"/>
		     <xsl:variable name="type" select="cpw:getDefault(@type,'input')"/>
		     <xsl:variable name="label" select="@label"/>
		     <xsl:variable name="help" select="@help"/>
		     <xsl:variable name="val" select="@val"/>
		     <xsl:variable name="disable" select="cpw:getDefault(@disable,'false')"/>
		     
		     <xsl:if test="$label"><label for="{$id}" class="form-label"><xsl:value-of select="$label"/></label></xsl:if>
             <input type="{$type}" class="form-control" id="{$id}">
                <xsl:if test="$val"><xsl:attribute name="value"><xsl:value-of select="$val"/></xsl:attribute></xsl:if>
                <xsl:if test="$help"><xsl:attribute name="aria-describedby"><xsl:value-of select="concat($id,'Help')"/></xsl:attribute></xsl:if>
                <xsl:if test="$disable='true'"><xsl:attribute name="disabled">true</xsl:attribute></xsl:if>
             </input>
             <xsl:if test="count(option)>0">
             <datalist id="{$id}">
             <xsl:for-each select="option">
             	<option><xsl:value-of select="text()"/></option>
             </xsl:for-each>
             </datalist>
             </xsl:if>
             <xsl:if test="$help"><div id="{concat($id,'Help')}" class="form-text"><xsl:value-of select="$help"/></div></xsl:if>
		</div>
	</xsl:template>
	<xsl:template match="textarea"> 
		<div class="mb-3">
		     <xsl:variable name="id" select="cpw:getDefault(@id,@name)"/>
		     <xsl:variable name="name" select="cpw:getDefault(@name,@id)"/>
		     <xsl:variable name="type" select="cpw:getDefault(@type,'input')"/>
		     <xsl:variable name="label" select="@label"/>
		     <xsl:variable name="help" select="@help"/>
		     <xsl:variable name="val" select="@val"/>
		     <xsl:variable name="disable" select="cpw:getDefault(@disable,'false')"/>
		     
		     <xsl:if test="$label"><label for="{$id}" class="form-label"><xsl:value-of select="$label"/></label></xsl:if>
             <textarea class="form-control" id="{$id}" name="{$name}" rows="{@rows}">
                <xsl:if test="$val"><xsl:attribute name="value"><xsl:value-of select="$val"/></xsl:attribute></xsl:if>
                <xsl:if test="$help"><xsl:attribute name="aria-describedby"><xsl:value-of select="concat($id,'Help')"/></xsl:attribute></xsl:if>
                <xsl:if test="$disable='true'"><xsl:attribute name="disabled">true</xsl:attribute></xsl:if>
             </textarea>
             <xsl:if test="$help"><div id="{concat($id,'Help')}" class="form-text"><xsl:value-of select="$help"/></div></xsl:if>
		</div>
	</xsl:template>
	<xsl:template match="inputs"> 
		<div class="{cpw:form(.)}">
		   <xsl:apply-templates/>
		</div>
	</xsl:template>
	<xsl:template match="check"> 
    	<div class="mb-3">
    	   <div class="form-check">
    	     <xsl:variable name="id" select="cpw:getDefault(@id,@name)"/>
		     <xsl:variable name="name" select="cpw:getDefault(@name,@id)"/>
		     <xsl:variable name="label" select="@label"/>
		     <xsl:variable name="val" select="@val"/>
		     <xsl:variable name="disable" select="cpw:getDefault(@disable,'false')"/>
		     
		     <input type="checkbox" class="form-check-input" id="{$id}">
		         <xsl:if test="$disable='true'"><xsl:attribute name="disabled">true</xsl:attribute></xsl:if>
		     </input>
		     <xsl:if test="$label"><label for="{$id}" class="form-check-label"><xsl:value-of select="$label"/></label></xsl:if>
      		</div>
    	</div>
    </xsl:template>
	<xsl:template match="radio"> 
		<div class="{cpw:form(.)}">
		   <xsl:apply-templates/>
		</div>
	</xsl:template>
	<xsl:template match="select"> 
    	<div class="mb-3">
    	     <xsl:variable name="id" select="cpw:getDefault(@id,@name)"/>
		     <xsl:variable name="name" select="cpw:getDefault(@name,@id)"/>
		     <xsl:variable name="label" select="@label"/>
		     <xsl:variable name="val" select="@val"/>
		     <xsl:variable name="disable" select="cpw:getDefault(@disable,'false')"/>
		     
             <select id="{$id}" class="form-select"  aria-label="{$label}">
                <xsl:if test="$label"><xsl:attribute name="aria-label"><xsl:value-of select="$label"/> </xsl:if>
             <option selected><xsl:value-of select="$label"/></option>
             <xsl:for-each select="option">
                 <option value="{@value}"><xsl:value-of select="./text()"/></option>
             </xsl:for-each>
      		</select>
    	</div>
	</xsl:template>
	<xsl:template match="range"> 
		<div class="{cpw:form(.)}">
		   <xsl:apply-templates/>
		</div>
	</xsl:template>
		<xsl:template match="button"> 
		<button type="submit" class="{cpw:button(.)}"><xsl:value-of select="cpw:getDefault(@label,'Submit')"/></button>
	</xsl:template>
	
	<xsl:template match="*"></xsl:template>

<!--  <xsl:apply-templates select="." mode="serialize"/>  -->
<xsl:template match="*" mode="serialize">
    <xsl:text>&lt;</xsl:text>
    <xsl:value-of select="name()"/>
    <xsl:apply-templates select="@*" mode="serialize" />
    <xsl:choose>
        <xsl:when test="node()">
            <xsl:text>&gt;</xsl:text>
            <xsl:apply-templates mode="serialize" />
            <xsl:text>&lt;</xsl:text>
            <xsl:value-of select="name()"/>
            <xsl:text>&gt;</xsl:text>
        </xsl:when>
        <xsl:otherwise>
            <xsl:text> /&gt;</xsl:text>
        </xsl:otherwise>
    </xsl:choose>
</xsl:template>
<xsl:template match="@*" mode="serialize">
    <xsl:text> </xsl:text>
    <xsl:value-of select="name()"/>
    <xsl:text>="</xsl:text>
    <xsl:value-of select="."/>
    <xsl:text>"</xsl:text>
</xsl:template>
<xsl:template match="text()" mode="serialize">
    <xsl:value-of select="."/>
</xsl:template>

</xsl:stylesheet>
