#include <stdio.h>
#include <openssl/sha.h>
#include <openssl/rsa.h>
#include <openssl/rand.h>
#include <openssl/objects.h>
#include <assert.h>
#include <openssl/x509.h>
#include <openssl/pem.h>
#include <string.h>


BIO *bio_err = NULL;

const char* FOTA_CERT_PATH = "fota.crt";
const char* CTL_FILE_PATH = "/etc/ssl/ctl";

int main()
{
    // !!!!This is mandatory!!!!
    OpenSSL_add_all_algorithms();

    //------------------ Open CTL list under ssl path -----------------
    FILE* ctlFile = fopen(CTL_FILE_PATH, "r");

    if (ctlFile == NULL)
    {
    	printf("Open file %s failed\n", CTL_FILE_PATH);
    	return 1;
    }

	fseek(ctlFile, 0, SEEK_END);
	long lSize = ftell(ctlFile);
	rewind(ctlFile);

	char* buffer = (char*)malloc(sizeof(char)*lSize);

	size_t result = fread(buffer, 1, lSize, ctlFile);

	if (result != lSize)
	{
		printf("Reading error!\n");
		return 1;
	}

	//------------------- Get serial number -------------------
	FILE* certFile = fopen(FOTA_CERT_PATH, "rb");
	X509 *mycert = PEM_read_X509 (certFile, NULL, NULL, NULL);

	//Serial number is an array of ASCII: 0x12 0x21 0x23 0x10 0x41 0x21
	ASN1_INTEGER *serail = X509_get_serialNumber(mycert);

	char serialNumber[255];

	// Convert serial number to string: 12:21:23:10:41:21
	int i;
	for (i = 0; i < serail->length; i++) {
		sprintf(&serialNumber[3*i], "%02x%c", serail->data[i],
					   ((i + 1 == serail->length) ? '\0' : ':'));
	}

	printf("SerialNumber: %s\n", serialNumber);

	X509_free(mycert);

	//------------------- Check if serial number is included in ctl -------------
	const char* separator = ",";
	int compareResult = -1;

	char* pch = strtok(buffer, separator);
	while (pch != NULL)
	{
		if (0 == strncmp(pch, serialNumber, 255))
		{
			compareResult = 0;
			break;
		}
		pch = strtok(buffer, separator);
	}

    if( compareResult == 0)
    {
    	printf("Certificate is in CTL list!\n");
    }
    else
    {
    	printf("Certificate is not in CTL list!\n");
    }




    return 0;
}

