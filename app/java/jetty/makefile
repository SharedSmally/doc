NAME=jhttp
DOMAIN=dev.jpw.com
MVN=${M2_HOME}/bin/mvn

TARGETS=compile package install clean

main: package

${TARGETS}:
	${MVN} $@ -Dmaven.test.skip=true

test:
	${MVN} $@

run:
	${MVN} exec:java -Dexec.mainClass="com.jpw.app.App"  -Dexec.classpathScope=runtime
