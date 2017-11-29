/*
 * rsaEnDe.c
 *
 *  Created on: 18 May, 2017
 *      Author: administrator
 */

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <openssl/x509.h>
# include <openssl/x509_vfy.h>
#include <openssl/pem.h>
#include <openssl/err.h>

const char* PRIVATE_KEY = "server.key";
const char* PUBLIC_CERT = "server.crt";

const char* AES_KEY_FILE = "aes_key";

const char* ENCYRPTED_FILE = "signature";
const char* DECRYPTED_FILE = "decrypted";

void encrypt();
void decrypt();

int main()
{
	OpenSSL_add_all_algorithms();


	encrypt();
	decrypt();

	return 0;

}


void encrypt()
{
	int keysize = 0;

	// Encrypt
	FILE *fp = fopen(PRIVATE_KEY, "r");
	EVP_PKEY *pkey = PEM_read_PrivateKey(fp, NULL, NULL, NULL);

	RSA* rsa = EVP_PKEY_get1_RSA(pkey);
	EVP_PKEY_free(pkey);

	BIO* in = BIO_new_file(AES_KEY_FILE, "rb");
	BIO* out = BIO_new_file(ENCYRPTED_FILE, "wb");

	keysize = RSA_size(rsa);
	unsigned char* rsa_in = OPENSSL_malloc(keysize * 2);
	unsigned char* rsa_out = OPENSSL_malloc(keysize);

	int rsa_inlen = BIO_read(in, rsa_in, keysize * 2);

	int rsa_outlen = RSA_private_encrypt(rsa_inlen, rsa_in, rsa_out, rsa, RSA_PKCS1_PADDING);

	BIO_write(out, rsa_out, rsa_outlen);

	RSA_free(rsa);
	BIO_free(in);
	BIO_free_all(out);
	if (rsa_in)
		OPENSSL_free(rsa_in);
	if (rsa_out)
		OPENSSL_free(rsa_out);

	printf("Encrypt success!\n");
}

void decrypt()
{
	FILE *certFile = fopen(PUBLIC_CERT, "rb");

	// Get RSA from public cert
	X509 *mycert = PEM_read_X509 (certFile, NULL, NULL, NULL);
	EVP_PKEY *publicKey = X509_get_pubkey(mycert);
	X509_free(mycert);

	RSA* rsa = EVP_PKEY_get1_RSA(publicKey);
	EVP_PKEY_free(publicKey);

	BIO* in = BIO_new_file(ENCYRPTED_FILE, "rb");
	BIO* out = BIO_new_file(DECRYPTED_FILE, "wb");

	int keysize = RSA_size(rsa);
	unsigned char* rsa_in = OPENSSL_malloc(keysize * 2);
	unsigned char* rsa_out = OPENSSL_malloc(keysize);

	// Read ENCYRPTED_FILE
	int rsa_inlen = BIO_read(in, rsa_in, keysize * 2);

	// Decrypt
	int rsa_outlen = RSA_public_decrypt(rsa_inlen, rsa_in, rsa_out, rsa, RSA_PKCS1_PADDING);

	// Write DECRYPTED_FILE
	BIO_write(out, rsa_out, rsa_outlen);

	RSA_free(rsa);
	BIO_free(in);
	BIO_free_all(out);
	if (rsa_in)
		OPENSSL_free(rsa_in);
	if (rsa_out)
		OPENSSL_free(rsa_out);

	printf("Decrypted success!\n");
}
