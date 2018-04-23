ASN1C_VERSION=7.0.5
ASN1C_GROUP=com.objsys
ASN1C_JAVA_HOME=asn1c/java/

main:asn1rt ber per

asn1rt:${ASN1C_JAVA_HOME}/asn1rt.jar
        mvn install:install-file -Dfile=$< -DgroupId=${ASN1C_GROUP} \
            -DartifactId=$@ -Dversion=${ASN1C_VERSION} -Dpackaging=jar

ber:${ASN1C_JAVA_HOME}/asn1rt-jme-ber.jar
        mvn install:install-file -Dfile=$< -DgroupId=${ASN1C_GROUP} \
            -DartifactId=$@ -Dversion=${ASN1C_VERSION} -Dpackaging=jar

per:${ASN1C_JAVA_HOME}/asn1rt-jme-per.jar
        mvn install:install-file -Dfile=$< -DgroupId=${ASN1C_GROUP} \
            -DartifactId=$@ -Dversion=${ASN1C_VERSION} -Dpackaging=jar

