#!/bin/sh

# script to generate root cert

if [ $# -lt 2 ]; then
    echo "USAGE: ./gencert.sh <-sha2> CA.cnf cert.cnf"
    exit 1
fi

SHA2PARAM=
SHA2CAPARM=

if [ $1 = "-sha2" ]; then
    echo "SHA2 encryption requested"
    SHA2PARAM="-sha256 -newkey rsa:2048"
    SHA2CAPARAM="-md sha256"
    shift
fi

CACNF=$1
if [ `dirname $CACNF` = "." ]; then
    CACNF=`pwd`/`basename $CACNF`
fi

if [ ! -r "$CACNF" ]; then
    echo "OpenSSL CA cnf file is invalid!"
    exit 1
fi

CNF=$2
if [ `dirname $CNF` = "." ]; then
    CNF=`pwd`/`basename $CNF`
fi

if [ ! -r "$CNF" ]; then
        echo "OpenSSL cnf file is invalid!"
    exit 1
fi

echo "generating certificates from $CNF signed by $CACNF..."
rm -fr sslcert
mkdir sslcert
cd sslcert
echo '100001' > serial
touch certindex.txt

export OPENSSL_CONF=/etc/pki/tls/openssl.cnf

openssl req -new -x509 -extensions v3_ca -keyout key.pem -out ca.pem -days 3650 -batch -passout pass:password -config $CACNF $SHA2PARAM
openssl req -new -nodes -keyout test.key -out test.csr -batch -config $CNF $SHA2PARAM
openssl ca -out testcert.pem -passin pass:password -batch -config $CNF -in test.csr $SHA2CAPARAM |& grep Signature

cat testcert.pem test.key > cert.pem    # this is server.pem with private key used by server
rm testcert.pem test.key
mv ca.pem root.pem    # this is clientca.pem used by client
