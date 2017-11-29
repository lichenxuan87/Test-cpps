#include <stdio.h>
#include <openssl/sha.h>
#include <openssl/rsa.h>
#include <openssl/rand.h>
#include <openssl/objects.h>
#include <assert.h>
#include <openssl/x509.h>
#include <openssl/pem.h>

int do_sign(BIO *out, unsigned char *buf, BIO *bp,
          EVP_PKEY *key);
int do_verify(unsigned char *buf, BIO *bp,
        unsigned char *sigin, int siglen);
BIO *bio_err = NULL;

const char* PRIVATE_KEY_PATH = "server.key";
const char* CERT_PATH = "server.crt";
const char* hashMethod = "sha256";
#define BASE64_BUFF_SIZE 1024

const int  BUFSIZE = 8*1024;


int sign();
int verify();

int main()
{
    // !!!!This is mandatory!!!!
	OpenSSL_add_all_algorithms();

	sign();
	verify();

    return 0;
}

int sign()
{
	const char* signFile1 = "README";
	const char* outputFile1 = "READMEsign.sha256";

	// Get private key
	FILE *fp = fopen(PRIVATE_KEY_PATH, "r");
	EVP_PKEY *pkey = PEM_read_PrivateKey(fp, NULL, NULL, NULL);

	if (!pkey)
	{
		printf("Server.key has a wrong format!\n");
		return 1;
	}

	// Get digest method
	EVP_MD *md = EVP_get_digestbyname(hashMethod);

	if (!md)
	{
		printf("%s is not a valid hash method\n", hashMethod);
		return 1;
	}

	// For parsing files
	BIO *bmd = BIO_new(BIO_f_md());
	BIO *in = BIO_new(BIO_s_file());

	// File 1
	BIO *out1 = BIO_new_file(outputFile1, "wb");

	// Prepare for sign
	unsigned char* buff = (unsigned char *)OPENSSL_malloc(BUFSIZE);

	EVP_MD_CTX *mctx = NULL;
	EVP_PKEY_CTX *pctx = NULL;
	BIO_get_md_ctx(bmd, &mctx);

	EVP_DigestSignInit(mctx, &pctx, md, NULL, pkey);

	// Sign
	BIO *inp = BIO_push(bmd, in);
	int result = 0;

	// Sign 1st file
	BIO_read_filename(in, signFile1);
	result = do_sign(out1, buff, inp, pkey);

	if (result)
	{
		printf("Failed!\n");
		return 1;
	}

	fclose(fp);


	return 0;
}


int verify()
{
	//--------------------------------------------------//
	//----------------------Verify----------------------//
	//--------------------------------------------------//
	const char* signedFile1 = "README";
	const char* signatureFile1 = "READMEsign.sha256";

	// Get public key
	FILE* certFile = fopen(CERT_PATH, "rb");
	X509 *mycert = PEM_read_X509 (certFile, NULL, NULL, NULL);
	EVP_PKEY *publicKey = X509_get_pubkey(mycert);

	// Get digest method
	EVP_MD *md = EVP_get_digestbyname(hashMethod);

	if (!md)
	{
		printf("%s is not a valid hash method\n", hashMethod);
		return 1;
	}

	// For parsing files
	BIO *bmd = BIO_new(BIO_f_md());
	BIO *in = NULL;
	BIO *sigbio = NULL;
	BIO *b64 = NULL;


	// Prepare for verify
	unsigned char* buff = (unsigned char *)OPENSSL_malloc(BUFSIZE);

	EVP_MD_CTX *mctx = NULL;
	EVP_PKEY_CTX *pctx = NULL;
	BIO_get_md_ctx(bmd, &mctx);

	EVP_DigestVerifyInit(mctx, &pctx, md, NULL, publicKey);

	// Prepare original file
	int siglen = EVP_PKEY_size(publicKey) * 2;
	unsigned char* sigbuf = OPENSSL_malloc(siglen);

	// -------------First file---------------//
	sigbio = BIO_new_file(signatureFile1, "r");
	in = BIO_new_file(signedFile1, "r");
	in = BIO_push(bmd, in);

	// Converting base64 to binary format
	b64 = BIO_new(BIO_f_base64());
	sigbio = BIO_push(b64, sigbio);

	if (!sigbio) {
        printf("Signature file not found\n");
		return 1;
	}
	if (!sigbuf) {
		printf("Out of memory\n");
		return 1;
	}

	siglen = BIO_read(sigbio, (char*)sigbuf, siglen);
	BIO_free(sigbio);
	if (siglen <= 0) {
        printf("Read signature file Error \n" );
		return 1;
	}

	// Verify 1st file
	do_verify(buff, in, sigbuf, siglen);

	return 0;
}

int do_sign(BIO *out, unsigned char *buf, BIO *bp,
          EVP_PKEY *key)
{
    size_t len;
    int i;

    char base64Buff[BASE64_BUFF_SIZE] = {};

    for (;;) {
        i = BIO_read(bp, (char *)buf, BUFSIZE);
        if (i < 0) {
            printf("Read Error \n" );
            return 1;
        }
        if (i == 0)
            break;
    }


    if (key) {
        EVP_MD_CTX *ctx;
        BIO_get_md_ctx(bp, &ctx);
        len = BUFSIZE;
        if (!EVP_DigestSignFinal(ctx, buf, &len)) {
        	printf("Error Signing Data\n");
            return 1;
        }
    }

    // Convert to base64 and write
    BIO* b64 = BIO_new(BIO_f_base64());
    out = BIO_push(b64, out);
    if (len != BIO_write(out, buf, len))
	{
		printf("error writing output file\n");
	}

    if (!BIO_flush(out)) {
		BIO_printf(bio_err, "bad decrypt\n");
	}

    BIO_free(b64);

    printf("Sign OK\n");

    return 0;
}

int do_verify(unsigned char *buf, BIO *bp,
        unsigned char *sigbuff, int siglen)
{
	size_t len;


	int i;
	for (;;) {
		i = BIO_read(bp, (char *)buf, BUFSIZE);
		if (i < 0) {
			printf( "Read Error\n");
			return 1;
		}
		if (i == 0)
			break;
	}

	// Final verify
	EVP_MD_CTX *ctx;
	BIO_get_md_ctx(bp, &ctx);
	i = EVP_DigestVerifyFinal(ctx, sigbuff, (unsigned int)siglen);
	if (i > 0)
		printf("Verified OK\n");
	else if (i == 0) {
		printf("Verification Failure\n");
		return 1;
	} else {
		printf("Error Verifying Data\n");
		return 1;
	}
	return 0;


}
