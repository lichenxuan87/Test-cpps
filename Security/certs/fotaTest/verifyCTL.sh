#!/bin/bash

if [ $# < 2 ]; then
	echo "Usage: ./verifyCTL.sh <certificate> <ctl>"
fi

echo $1
echo $2

CERT=$1
CTL=$2

openssl x509 -inform pem -in $CERT -pubkey -noout > publickey.pem
openssl dgst -sha256 -verify publickey.pem -signature fota-ctl.sign.sha256 $CTL

