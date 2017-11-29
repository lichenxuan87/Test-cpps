#include <stdio.h>
#include <openssl/sha.h>
#include <openssl/rsa.h>
#include <openssl/rand.h>
#include <openssl/objects.h>
#include <assert.h>
#include <openssl/x509.h>
#include <openssl/pem.h>
#include <string.h>

#include <jsoncpp/json/json.h>
#include <jsoncpp/json/reader.h>
#include <jsoncpp/json/value.h>
#include <string>
#include <iostream>

using namespace std;


BIO *bio_err = NULL;

const char* FOTA_CA_CERT_PATH = "fota_ca.crt";
const char* FOTA_CERT_PATH = "fota.crt";

const char* CTL_FILE_PATH = "/etc/ssl/ctl";

#define BASE64_BUFF_SIZE 1024

const int  BUFSIZE = 8*1024;

const char* CTL = "{\
\"id_list\":\"12:21:23:10:41:21,15:11:26:80:E1:32\",\
\"sign\":\"Zth2gFIrizb3WnLc79QpMmB/1yQQ4Y726vvryDuVzA4GO1hk/5mCAcI0Lt9r42QC\
V+rEBjDSqTx3git2p/FrSguUeE9DdBbbnA4KIP6UHpMmQJaDqhHKM19ZGgR9zSfr\
r2mRhlFrrAv7zMk4yqTi2d5YjvCDn1vMkBAJHmo9rKDfg4S1Kku205sREyP3Lyuo\
kSRuNnAeplTMh3uuRSroJ6KximKdZmt7ZZxdNnpq19ew1+Fvt0JLf8T11PEBeNl6\
kYwvS1T8O32OdaTcqmdQmzS/cDaHvEBpxdGUphCRbQHqk+mRYhqnSQ4g5oH/APbx\
mcSLoJ6A75GEWKzyOh/rVg==\"}";


bool verify(const char* certPath, const char* signedString, const char* signature);
bool do_verify(BIO *bp, unsigned char *sigin, int siglen);
int main()
{
    // !!!!This is mandatory!!!!
    OpenSSL_add_all_algorithms();

    //------------------ Get id and signature list -----------------
	Json::Value root;
	Json::Reader reader;
	bool parsingSuccessful = reader.parse(CTL, root);

	if (!parsingSuccessful)
	{
		printf("Parsing json string failed\n");
		return -1;
	}

	std::string id_list = root["id_list"].asString();
	id_list = id_list;
	std::string signature = root["sign"].asString();
	signature = signature + "\n";

	printf("Parsing result: id_list: %s, signature: %s\n", id_list.c_str(), signature.c_str());

	//------------------ Verify CTL list----------------------
    if( verify(FOTA_CA_CERT_PATH, id_list.c_str(), signature.c_str()))
    {
    	printf("Verified OK!\n");
    }
    else
    {
    	printf("Verified Failed!\n");
    }


    //------------------ Save CTL list under ssl path -----------------
    FILE* ctlFile = fopen(CTL_FILE_PATH, "w");

    if (ctlFile != NULL)
    {
    	if (0 == fwrite(id_list.c_str(), sizeof(char), id_list.length(), ctlFile))
		{
    		printf("Write %s failed\n", CTL_FILE_PATH);
		}

    	fflush(ctlFile);

    	fclose(ctlFile);
    }
    else
    {
    	printf("Open file %s failed\n", CTL_FILE_PATH);
    }

    return 0;
}

bool verify(const char* certPath, const char* signedString, const char* signature)
{
	bool result = false;

    // Get public key
	FILE* certFile = fopen(certPath, "rb");
	X509 *mycert = PEM_read_X509 (certFile, NULL, NULL, NULL);
	EVP_PKEY *publicKey = X509_get_pubkey(mycert);


    // -------------Convert signature from b64 to binary---------------//
    int siglen = EVP_PKEY_size(publicKey) * 2;
    unsigned char* sigbuf = (unsigned char*)OPENSSL_malloc(siglen);

    cout << "Start Decoding Base64\n" << endl;

    BIO * b64  = BIO_new(BIO_f_base64());
    BIO * bmem = BIO_new_mem_buf(const_cast<char*>(signature),
    		strlen(signature));

    bmem = BIO_push(b64, bmem);
    siglen = BIO_read(bmem, sigbuf, siglen);

    for (int i = 0; i< siglen; i++ )
    {
        if (i % 16 == 0)
            printf("\n");
        printf("%02x ", sigbuf[i]);
    }
    printf("\n");

    BIO_free_all(bmem);


    // Get digest method
    const EVP_MD *md = EVP_sha256();

    // For parsing files
    BIO *bmd = BIO_new(BIO_f_md());
    BIO *in = NULL;
    BIO *sigbio = NULL;

    // Prepare for verify
    EVP_MD_CTX *mctx = NULL;
    EVP_PKEY_CTX *pctx = NULL;
    BIO_get_md_ctx(bmd, &mctx);

    EVP_DigestVerifyInit(mctx, &pctx, md, NULL, publicKey);


    // -------------Prepare id list---------------//
    in = BIO_new_mem_buf(const_cast<char*>(signedString),
    		strlen(signedString));
    in = BIO_push(bmd, in);

    // Verify 1st file
    result = do_verify(in, (unsigned char*)sigbuf, siglen);

	fclose(certFile);
	X509_free(mycert);
	EVP_PKEY_free(publicKey);
    BIO_free(sigbio);
    BIO_free_all(bmd);

    return result;
}

bool do_verify(BIO *bp,
        unsigned char *sigbuff,
        int siglen)
{
    unsigned char* buff = (unsigned char *)OPENSSL_malloc(BUFSIZE);

    int i;
    for (;;) {
        i = BIO_read(bp, (char *)buff, BUFSIZE);
        if (i < 0) {
            printf( "Read Error\n");
            return 1;
        }

        if (i == 0)
        {
            break;
        }
        else
        {
			for (int j = 0; j< i; j++ )
			{
				if (j % 16 == 0)
					printf("\n");
				printf("%02x ", buff[j]);
			}
			printf("\n");
        }
    }

    OPENSSL_free(buff);

    // Final verify
    EVP_MD_CTX *ctx;
    BIO_get_md_ctx(bp, &ctx);

    return (EVP_DigestVerifyFinal(ctx, sigbuff, (unsigned int)siglen) > 0);


}
