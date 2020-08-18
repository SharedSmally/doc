TARGETS=compile package install

main: package

${TARGETS}:
	mvn $@

dep:
	mvn dependency:copy-dependencies -DoutputDirectory=target/

#run:
#	java -cp target/suplsvc-1.0-SNAPSHOT.jar:target/netty-all-4.1.51.Final.jar com.jpw.app.App

run:
	mvn exec:java -Dexec.mainClass="com.jpw.app.App"  -Dexec.classpathScope=runtime -Dexec.args="9999 arg1 arg2" 
