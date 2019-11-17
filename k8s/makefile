K8S_VERSION=1.16.0
MINISHIFT_VERSION=1.34.1
OPENSHIFT_VERSION=3.10.14
ORIGIN_VERSION=3.11.0
ORIGIN_TAG=0cbc58b

main: k8s

k8stools: minikube minishift openshift
	# fabric8

#####################################################
# minikube; minishift; openshift/origin; fabric8
# minikube: https://kubernetes.io/docs/tasks/tools/install-minikube/
minikube:
	curl -Lo minikube https://storage.googleapis.com/minikube/releases/latest/minikube-linux-amd64
	chmod +x minikube

# minishift: https://github.com/minishift/minishift/releases
minishift:minishift-${MINISHIFT_VERSION}-linux-amd64.tgz

minishift-${MINISHIFT_VERSION}-linux-amd64.tgz:
	wget https://github.com/minishift/minishift/releases/download/v${MINISHIFT_VERSION}/$@ -O $@

#  http://www.openshift.org
# openshift: trial version:https://developers.redhat.com/products/openshift/download
openshift: oc-${OPENSHIFT_VERSION}-linux.tar.gz

oc-${OPENSHIFT_VERSION}-linux.tar.gz:
	wget https://developers.redhat.com/download-manager/file/$@ -O $@

# Openshift/Origin:trial version OKD: https://www.okd.io/download.html
# https://github.com/openshift/origin/releases/tag/v3.11.0
origin: openshift-origin-client-tools-v${ORIGIN_VERSION}-${ORIGIN_TAG}-linux-64bit.tar.gz \
	openshift-origin-server-v${ORIGIN_VERSION}-${ORIGIN_TAG}-linux-64bit.tar.gz

openshift-origin-client-tools-v${ORIGIN_VERSION}-${ORIGIN_TAG}-linux-64bit.tar.gz:
	wget https://github.com/openshift/origin/releases/download/v${ORIGIN_VERSION}/$@ -O $@

openshift-origin-server-v${ORIGIN_VERSION}-${ORIGIN_TAG}-linux-64bit.tar.gz:
	wget https://github.com/openshift/origin/releases/download/v${ORIGIN_VERSION}/$@ -O $@

# https://fabric8.io/
fabric8:
	curl -sS https://get.fabric8.io/download.txt | bash

#####################################################


#####################################################
# kubernetes-client/server/node
# https://kubernetes.io/docs/setup/release/notes/
k8s: kubernetes-client-linux-amd64.tar.gz \
     kubernetes-server-linux-amd64.tar.gz \
     kubernetes-node-linux-amd64.tar.gz

clean_k8s:
	${RM} -rf kubernetes-client-linux-amd64.tar.gz 
	${RM} -rf kubernetes-server-linux-amd64.tar.gz 
	${RM} -rf kubernetes-node-linux-amd64.tar.gz

kubernetes-client-linux-amd64.tar.gz:
	wget https://dl.k8s.io/v${K8S_VERSION}/$@ -O $@

# 400MB
kubernetes-server-linux-amd64.tar.gz:
	wget https://dl.k8s.io/v${K8S_VERSION}/$@ -O $@

kubernetes-node-linux-amd64.tar.gz:
	wget https://dl.k8s.io/v${K8S_VERSION}/$@ -O $@
#####################################################
