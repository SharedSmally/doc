K8S_VERSION=1.16
K8S_URL=https://kubernetes.io/docs/reference/generated/kubernetes-api/v${K8S_VERSION}/

main: k8sapiREST.xml k8sapiRes.xml k8sapiEx.xml k8sapiIndex.xml

k8sapiIndex.xml:k8sapiIndex1.xml 
	xsl k8sapiIndex.xsl $< $@

k8sapiIndex1.xml:k8sapiIndex0.xml 
	xsl k8sapiIndex1.xsl $< $@

k8sapiIndex0.xml:k8s.xml 
	xsl k8sapiIndex0.xsl $< $@

k8sapiEx.xml:k8s.xml 
	xsl k8sapiEx.xsl $< $@

k8sapiREST.xml:k8sapiREST0.xml
	xsl k8sapiREST.xsl $< $@

k8sapiREST0.xml:k8sapi.xml
	xsl k8sapiREST0.xsl $< $@

k8sapiRes.xml:k8sapi.xml
	xsl k8sapiRes.xsl $< $@

k8sapi.xml:k8s.xml    
	xsl k8sapi.xsl $< $@

k8s.xml: k8s.html
	cp $< $@
	@sed -i '/DOCTYPE html/d' $@  #remove lines:sed -i '/pattern to match/d' ./infile
	@sed -i -E 's/<META(.+)>/<META\1\/>/g' $@
	@sed -i -E 's/<LINK(.+)>/<LINK\1\/>/g' $@
# 3808: move </P> to 3797
# 3822: <P> => </P>
# 14236: & => and
# 2267: remove additional </UL>

k8s.html:
	wget ${K8S_URL} -O $@

clean:
	${RM} k8sapiREST.xml
	${RM} k8sapiREST0.xml
#	${RM} k8sapiRes.xml

cleanall: clean
	${RM} k8sapi.xml
	${RM} k8s.xml
	${RM} k8s.html
