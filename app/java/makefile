TARGETS=compile package install

main: package

${TARGETS}:
	mvn $@

dep:
	mvn dependency:copy-dependencies -DoutputDirectory=target/

run:
	java -cp target/suplsvc-1.0-SNAPSHOT.jar:target/netty-all-4.1.51.Final.jar com.jpw.app.App
