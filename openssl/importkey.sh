#!/bin/sh

if [ $# -lt 1 ]; then
    echo "USAGE: ./importkey.sh server.pem root.pem"
    exit 1
fi

echo "generating keystore from server certificate $1 and client root certificate $2..."

rm -f keystore.jks

openssl pkcs12 -export -out keystore.p12 -inkey $1 -in $1 -passout pass:password
keytool -importkeystore -destkeystore keystore.jks -srcstoretype PKCS12 -srckeystore keystore.p12 -srcstorepass password -deststorepass password
keytool -importcert -noprompt -srcstorepass password -deststorepass password -alias ca -keystore keystore.jks -trustcacerts -file $2
