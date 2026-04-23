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
	
	<!--  match  container/row/col -->
	<xsl:template match="container">
		<div class="{cpw:getContainerClass(.)}">
			<xsl:apply-templates/>
		</div>
	</xsl:template>
	<xsl:template match="container/row"> <!--  size; cols= -->
		<div class="{cpw:getRowClass(.)}">
			<xsl:apply-templates/>
		</div>
	</xsl:template>
	<xsl:template match="container/row/col">
		<div class="{cpw:getColumnClass(.)}">
			<xsl:apply-templates/>
		</div>	
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
