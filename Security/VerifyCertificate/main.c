
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

int verifyCertiAgainstCertChain (FILE *cert, char* caCertPath);

static int cb(int ok, X509_STORE_CTX *ctx);

int main (int ac, char **av)
{
    FILE     *certFile = NULL;

    if (ac < 2)
    {
        printf("./verifyCert certPath\n");
        return 1;
    }
    
    // !!!!This is mandatory!!!!
    OpenSSL_add_all_algorithms();
    
    
    //////////// Reading certificate/////
    
    if ((certFile = fopen (av[1], "rb")) == NULL) {
        fprintf (stderr, "Unable to open file %s for input\n", av[1]);
        exit (1);
    }
    
    
    // TODO: we need to verify cert against valid certification list first
    // verify(certFile, crlList)    
    

    if (verifyCertiAgainstCertChain (certFile, "/etc/ssl/certs/") < 1) 
    {
        fprintf (stderr, "Certificate chain is incorrect\n");
        exit (1);
    }
    else
    {
        printf("Verify success!\n");
    }
    
    fclose (certFile);
    return 0;
}


// Verify certificate against certificate chain
int verifyCertiAgainstCertChain (FILE *certPath, char* caCertPath)
{
    X509 *mycert;
    int result;

    mycert = PEM_read_X509 (certPath, NULL, NULL, NULL);

    if (!mycert)
    {
        printf("Wrong cert format\n");
        return -1;
    }

    /* ---------------------------------------------------------- *
    * Initialize the global certificate validation store object. *
    * ---------------------------------------------------------- */
    X509_STORE *store = X509_STORE_new();
    X509_STORE_set_verify_cb(store, cb);

    X509_LOOKUP* lookup = X509_STORE_add_lookup(store, X509_LOOKUP_hash_dir());
    
    int i = X509_LOOKUP_add_dir(lookup, caCertPath, X509_FILETYPE_PEM);
    if (!i) {
        printf("Error loading directory %s\n", caCertPath);
        return -1;
    }
    
    ERR_clear_error();

    /* ---------------------------------------------------------- *
    * Create the context structure for the validation operation. *
    * ---------------------------------------------------------- */
    X509_STORE_CTX *verifyCtx = X509_STORE_CTX_new();
    
    // Add the cert need to be verified here
    if (!X509_STORE_CTX_init(verifyCtx, store, mycert, NULL))
        printf("Error\n");

    /* ---------------------------------------------------------- *
    * Check the complete cert chain can be build and validated.  *
    * Returns 1 on success, 0 on verification failures, and -1   *
    * for trouble with the ctx object (i.e. missing certificate) *
    * ---------------------------------------------------------- */
    result = X509_verify_cert(verifyCtx);
    
    printf("Check result: %d\n", result);

    X509_STORE_CTX_free(verifyCtx);
    X509_STORE_free(store);
    X509_free(mycert);

    return result;    
}

static int cb(int ok, X509_STORE_CTX *ctx)
{
    int cert_error = X509_STORE_CTX_get_error(ctx);
    X509 *current_cert = X509_STORE_CTX_get_current_cert(ctx);

    if (!ok) {
        if (current_cert) {
            X509_NAME_print_ex_fp(stdout,
                                  X509_get_subject_name(current_cert),
                                  0, XN_FLAG_ONELINE);
            printf("\n");
        }
        printf("%serror %d at %d depth lookup:%s\n",
               X509_STORE_CTX_get0_parent_ctx(ctx) ? "[CRL path]" : "",
               cert_error,
               X509_STORE_CTX_get_error_depth(ctx),
               X509_verify_cert_error_string(cert_error));
        switch (cert_error) {
        case X509_V_ERR_NO_EXPLICIT_POLICY:
            //policies_print(NULL, ctx);
        case X509_V_ERR_CERT_HAS_EXPIRED:

            /*
             * since we are just checking the certificates, it is ok if they
             * are self signed. But we should still warn the user.
             */

        case X509_V_ERR_DEPTH_ZERO_SELF_SIGNED_CERT:
            /* Continue after extension errors too */
        case X509_V_ERR_INVALID_CA:
        case X509_V_ERR_INVALID_NON_CA:
        case X509_V_ERR_PATH_LENGTH_EXCEEDED:
        case X509_V_ERR_INVALID_PURPOSE:
        case X509_V_ERR_CRL_HAS_EXPIRED:
        case X509_V_ERR_CRL_NOT_YET_VALID:
        case X509_V_ERR_UNHANDLED_CRITICAL_EXTENSION:
            ok = 1;

        }

        return ok;

    }
    if (cert_error == X509_V_OK && ok == 2)
        //policies_print(NULL, ctx);
    
    ERR_clear_error();
    return (ok);
}

