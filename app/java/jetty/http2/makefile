NAME=jhttp
DOMAIN=dev.jpw.com
MVN=${M2_HOME}/bin/mvn

TARGETS=compile package install clean

main: package

${TARGETS}:
	${MVN} $@ -Dmaven.test.skip=true

test:
	${MVN} $@

copy_dep:
	${MVN} dependency:copy-dependencies

# The classpath option after Java 6 supports wildcards:
# - Use straight quotes (")
# - Use *, not *.jar
runApp:
	java -cp "target/lib/*:target/jhttp-1.0-SNAPSHOT.jar" com.jpw.app.App \
	-Xbootclasspath/p:${HOME}/.m2/repository/org/mortbay/jetty/alpn/alpn-boot/8.1.13.v20181017/alpn-boot-8.1.13.v20181017.jar
#
run:
	${MVN} exec:exec 

#test using Browser: https://${hostname}:8443/
#test using curl: -k: testing a server with self-signed certs
curl:
	curl -k --http2 https://localhost:8443  
