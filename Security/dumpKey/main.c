#include <stdio.h>
#include <openssl/sha.h>
#include <openssl/rsa.h>
#include <openssl/rand.h>
#include <openssl/objects.h>
#include <assert.h>
#include <openssl/x509.h>
#include <openssl/pem.h>
#include <math.h>
#include <string.h>

const char* CERT_PATH = "testkey_sha256.x509.pem";
//const char* CERT_PATH = "server.crt";

int dumpKey();

int printBN(char* buff, int index, BIGNUM *a);

int main()
{
    // !!!!This is mandatory!!!!
	OpenSSL_add_all_algorithms();

	dumpKey();

    return 0;
}


int dumpKey()
{
	// Get public key
	FILE* certFile = fopen(CERT_PATH, "rb");
	X509 *mycert = PEM_read_X509 (certFile, NULL, NULL, NULL);

	char buffer[2048] = {0};

	int index = 0;
	int version = 0;

	// Get signature type
	int useSHA256 = 0;

	i2t_ASN1_OBJECT(buffer, 2048, mycert->sig_alg->algorithm);
	if (0 == strncmp(buffer, "sha256", 6))
	{
		useSHA256 = 1;
	}
	memset(buffer, 0, 2048);

	// Get exponent
	EVP_PKEY *publicKey = X509_get_pubkey(mycert);
	BIGNUM* pubexp = publicKey->pkey.rsa->e;

	// Determine version
	BIGNUM* temp = BN_new();

	BN_set_word(temp, 3);
	if (0 == BN_cmp(pubexp, temp))
	{
		version = useSHA256 == 1 ? 3 : 1;
	}

	BN_set_word(temp, 65537);
	if (0 == BN_cmp(pubexp, temp))
	{
		version = useSHA256 == 1 ? 4 : 2;
	}


	index += sprintf(&buffer[index], "v%d ", version);
	index += sprintf(&buffer[index], "{");


	printBN(buffer, index, publicKey->pkey.rsa->n);

	printf("%s\n", buffer);

	BN_free(temp);
	EVP_PKEY_free(publicKey);
	X509_free(mycert);
	fclose(certFile);
	return 0;
}

int printBN(char* buff, int index, BIGNUM *a)
{
    int i = 0;
    int numOf32bit = 0;
    int ret = 0;

    BN_CTX* ctx = BN_CTX_new();

    if (a->neg)
	{
    	buff[0] = '-';
	}

    if (BN_is_zero(a))
	{
    	buff[0] = '-';
	}


#ifdef BIT_64
    // For 64 bit system, BN_BITS2 is 64 bits
    numOf32bit = a->top * 2;
#else
    // For 32 bit system, BN_BITS2 is 32 bits
    numOf32bit = a->top;
#endif

    index += sprintf(&buff[index], "%d", numOf32bit);

    BIGNUM* B = BN_new();
    BIGNUM* exp = BN_new();
    BIGNUM* temp = BN_new();
    BIGNUM* N0inv = BN_new();
    BIGNUM* R = BN_new();
    BIGNUM* RR = BN_new();

    // Get N0inv
    BN_set_word(temp, 0x2L);
    BN_set_word(exp, 32);
    BN_exp(B, temp, exp, ctx);
    //printf("%s\n", BN_bn2hex(B));

    BN_sub(N0inv, B, BN_mod_inverse(temp, a, B, ctx));
    //printf("%s\n", BN_bn2hex(N0inv));

    index += sprintf(&buff[index],",0x");
    index += sprintf(&buff[index], "%s", BN_bn2hex(N0inv));

    // Get R and RR
    BN_set_word(temp, 0x2L);
	BN_set_word(exp, numOf32bit * 32);
	BN_exp(R, temp, exp, ctx);

	BN_mul(RR, R, R, ctx);
	BN_mod(RR, RR, a, ctx);
	//printf("%s\n", BN_bn2hex(RR));

	// Write big number as little endian array of integers
    index += sprintf(&buff[index], ",{");
    for (i = numOf32bit - 1; i >= 0; i--) {
    	BN_mod(temp, a, B, ctx);
    	unsigned int n = BN_get_word(temp);
    	index += sprintf(&buff[index], "%u", n);

    	if (i != 0)
    	{
    		index += sprintf(&buff[index], ",");
    	}

    	BN_div(a, temp, a, B, ctx);
    }
    index += sprintf(&buff[index], "}");


    // Write RR as little endian array of integers
    index += sprintf(&buff[index], ",{");
	for (i = numOf32bit - 1; i >= 0; i--) {
		BN_mod(temp, RR, B, ctx);
		unsigned int n = BN_get_word(temp);
		index += sprintf(&buff[index], "%u", n);

		if (i != 0)
		{
			index += sprintf(&buff[index], ",");
		}

		BN_div(RR, temp, RR, B, ctx);
	}
	index += sprintf(&buff[index], "}");

    index += sprintf(&buff[index], "}");


    BN_CTX_free(ctx);
    BN_free(B);
    BN_free(N0inv);
    BN_free(temp);
    BN_free(R);
    BN_free(RR);

    return (ret);
}
