K8S_VERSION=1.16
K8S_URL=https://kubernetes.io/docs/reference/generated/kubernetes-api/v${K8S_VERSION}/
#
main: k8sapi.xml

test: index.html
        @sed -i '/DOCTYPE html/d' $<  #remove lines:sed -i '/pattern to match/d' ./infile
        @sed -i -E 's/<META(.+)>/<META\1\/>/g' $<
        @sed -i -E 's/<LINK(.+)>/<LINK\1\/>/g' $<

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
        ${RM} k8sapi.xml

cleanall: clean
        ${RM} k8s.xml
        ${RM} k8s.html
