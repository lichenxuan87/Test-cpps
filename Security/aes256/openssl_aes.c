/**
  AES encryption/decryption demo program using OpenSSL EVP apis
  gcc -Wall openssl_aes.c -lcrypto

  this is public domain code. 

  Saju Pillai (saju.pillai@gmail.com)
**/

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <termios.h>			/* For  secure password input */
# include <sys/types.h>
# include <sys/stat.h>
# include <openssl/evp.h>
# include <openssl/aes.h>
# include <error.h>
# include <fcntl.h>


#define SIZE 2048

/**
 * Create a 256 bit key and IV using the supplied key_data. salt can be added for taste.
 * Fills in the encryption and decryption ctx objects and returns 0 on success
 **/
int aes_init(unsigned char *key_data, int key_data_len, EVP_CIPHER_CTX *e_ctx,
             EVP_CIPHER_CTX *d_ctx)
{

	int i, nrounds = 1;
	unsigned char key[32], iv[32];
	EVP_CIPHER *cipherType = EVP_aes_256_cbc();

	/*
	* Gen key & IV for AES 256 CBC mode. A SHA1 digest is used to hash the supplied key material.
	* nrounds is the number of times the we hash the material. More rounds are more secure but
	* slower.
	*/
	i = EVP_BytesToKey(cipherType, EVP_md5(), NULL, key_data, key_data_len, nrounds, key, iv);
	if (i != 32) {
		printf("Key size is %d bits - should be 256 bits\n", i);
		return -1;
	}

	EVP_CIPHER_CTX_init(e_ctx);
	EVP_EncryptInit_ex(e_ctx, cipherType, NULL, key, iv);
	EVP_CIPHER_CTX_init(d_ctx);
	EVP_DecryptInit_ex(d_ctx, cipherType, NULL, key, iv);


	printf("key=");
	for (i = 0; i < cipherType->key_len; i++)
		printf("%02X", key[i]);
	printf("\n");


	printf("iv =");
	for (i = 0; i < cipherType->iv_len; i++)
		printf("%02X", iv[i]);
	printf("\n");

	return 0;
}



int aes_decrypt(EVP_CIPHER_CTX *d,int in,int out)				/* returns 0: SUCCESS 1: ERROR */
{
    int inlen=0,flen=0,outlen=0;
    char inbuf[SIZE+AES_BLOCK_SIZE]={0};                                /****** CHECK ???? ****/
    char outbuf[SIZE+AES_BLOCK_SIZE]={0};

    if(!EVP_DecryptInit_ex(d, NULL, NULL, NULL, NULL))
    {   
            perror("\n Eror in DECinit:");
            return 1;
    }   

    while((inlen = read(in,inbuf,SIZE)) >0) 
    {   
            if(!EVP_DecryptUpdate(d,(unsigned char*)outbuf, &outlen,(unsigned char*)inbuf,inlen))
            {   
                    perror("\n Error,DECRYPT_UPDATE:");
                    return 1;
            }   
            if((write(out,outbuf,outlen)) != outlen)
            {   
                   perror("\n ERROR,Writing dec bytes:");
                   return 1;
            }   
    }   

    if(!EVP_DecryptFinal_ex(d,(unsigned char*)outbuf,&flen))
    {   
            perror("\n Error,DECRYPT_FINAL:");
            return 1;
    }

    if((write(out,outbuf,flen)) != flen)
    {
            perror("\n ERROR,Writng FINAL dec bytes:");
            return 1;
    }
    return 0;				/* SUCCESS */

}


/*
 * Encrypt *len bytes of data
 * All data going in & out is considered binary (unsigned char[])
 */
int aes_encrypt(EVP_CIPHER_CTX *e, int in, int out)
{
	char inbuf [SIZE]={0};
    char outbuf[SIZE+AES_BLOCK_SIZE]={0};
    int inlen = 0,flen=0,outlen =0;						

    if(!EVP_EncryptInit_ex(e, NULL, NULL, NULL, NULL))    /* allows reusing of e for multiple cipher cycles CHECK ????*/
    {
            perror("\n Error,ENCRYPR_INIT:");
            return 1;
    }

    while((inlen = read(in,inbuf,SIZE)) > 0)
    {
            if(!EVP_EncryptUpdate(e,(unsigned char*) outbuf, &outlen,(unsigned char*) inbuf,inlen))                 /* Update cipher text */
            {
                    perror("\n ERROR,ENCRYPR_UPDATE:");
                    return 1;
            }
            if(write(out,outbuf,outlen) != outlen)
            {
                    perror("\n ERROR,Cant write encrypted bytes to outfile:");
                    return 1;
            }
    }

    if(!EVP_EncryptFinal_ex(e, (unsigned char*) outbuf, &flen))                     /* updates the remaining bytes */
    {
            perror("\n ERROR,ENCRYPT_FINAL:");
            return 1;
    }

    if(write(out,outbuf,flen) != flen)
    {
            perror("\n ERROR,Wriring final bytes of data:");
            return 1;
    }

    return 0;			/* SUCCESS */
}


int main()
{
    /* "opaque" encryption, decryption ctx structures that libcrypto uses to record
     status of enc/dec operations */
    EVP_CIPHER_CTX en, de;

    const char* INPUT_KEY = "1234";
    unsigned char *key_data = (unsigned char*)INPUT_KEY;
    int key_data_len = strlen(INPUT_KEY);

    char* in_path = "README";
    char* encrypted_path = "encrypted";
    char* decrypted_path = "decrypted";

    int inFile, outFile;

    /* gen key and iv. init the cipher ctx object */
    if (aes_init(key_data, key_data_len, &en, &de)) {
        printf("Couldn't initialize AES cipher\n");
        return -1;
    }

    if((inFile = open((char *)in_path,O_RDONLY)) <0)			/* Opening the input file  */
	{
		perror("\n ERROR,OPEN_INFILE_C_FILE::");
		return 1;	
	}

    if((outFile = open(encrypted_path,O_CREAT|O_RDWR,0400|0200)) <0)				/* Creating tmp file for writing */
	{
		perror("\n ERROR,CANT create temp file_C_FILE::");
		return 1;
	}

    if(aes_encrypt(&en,inFile,outFile))							/* ENCRYPTING */
	{
		printf("ERROR,ENCRYPTING_C_FILE\n");
		return 1;
	}

    printf("Encrypt success\n");
    close(inFile);
    close(outFile);

    if((inFile = open((char *)encrypted_path,O_RDONLY)) <0)			/* Opening the input file  */
	{
		perror("\n ERROR,OPEN_INFILE_C_FILE::");
		return 1;	
	}

    if((outFile = open(decrypted_path,O_CREAT|O_RDWR,0400|0200)) <0)				/* Creating tmp file for writing */
	{
		perror("\n ERROR,CANT create temp file_C_FILE::");
		return 1;
	}


    if(aes_decrypt(&de,inFile,outFile))								/* Decrypting */
	{
		printf("ERROR,decrypting file_C_FILE\n");
		return 1;
	}

    printf("Decrypt success\n");

    close(inFile);
    close(outFile);
   
    EVP_CIPHER_CTX_cleanup(&en);
    EVP_CIPHER_CTX_cleanup(&de);

    return 0;
}
  
