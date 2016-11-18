 xslt
 ===========
 
 ## Transfer
 - (xalan)[https://xml.apache.org/xalan-j/] - xslt 1.0; based in (xerces) [http://xerces.apache.org/xerces2-j/index.html]
   
   export XALAN_HOME=/home/xxx/xalan

   java -cp ${XALAN_HOME}/xalan.jar:${XALAN_HOME}/serializer.jar:${XALAN_HOME}/xercesImpl.jar:${XALAN_HOME}/xml-apis.jar \
     org.apache.xalan.xslt.Process -xsl $1 -in $2 -out $3

 - (Saxon) [http://saxon.sourceforge.net/] - xslt 2.0; Home Edition

   export SAXON_HOME=/home/xxx/saxon

   java -cp ${SAXON_HOME}/saxon9-xqj.jar:${SAXON_HOME}/saxon9he.jar \
     net.sf.saxon.Transform -xsl:$1 -s:$2 -o:$3

