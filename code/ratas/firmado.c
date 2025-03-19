#include <openssl/evp.h>
//#include <openssl/pem.h>
#include <openssl/err.h>
#include <openssl/decoder.h>
//#include <openssl/core_names.h>



//#include <openssl/aes.h>
//#include <openssl/rand.h>

#include <stdio.h>
#include <stdio.h>
//#include <string.h>

int main (int argc, char *argv[]) {
  OSSL_LIB_CTX *libctx = NULL;
  /* Manejo de Claves Claves */
  OSSL_DECODER_CTX *dctx = NULL;
  EVP_PKEY_CTX     *pkctx = NULL;
  EVP_PKEY         *priv_key = NULL;
  /* Función Hash*/
  const EVP_MD      *md;
  EVP_MD_CTX        *mdctx;

  if (argc != 4) {
    fprintf (stderr, "Usage:¨\n%s private.pem hash-algo input_file\n",
	     argv[0]);
    exit (1);
  }
  libctx = NULL; /* Usa el contexto de librería por defecto */

  /* Adquirimos las claves para el firmado */
  dctx = OSSL_DECODER_CTX_new_for_pkey (&priv_key, NULL, NULL, NULL,
					EVP_PKEY_KEYPAIR,libctx, NULL);

  /* Lee par de claves */
  FILE *f = fopen (argv[1], "rb");
  OSSL_DECODER_from_fp(dctx, f);
  fclose (f);
  OSSL_DECODER_CTX_free(dctx);

  

  /* creamos función Hash */
  if ((md = EVP_get_digestbyname (argv[2])) == NULL) {
        ERR_print_errors_fp (stderr);
  }

  mdctx = EVP_MD_CTX_create ();

  if (EVP_SignInit (mdctx, md) <= 0) {
    ERR_print_errors_fp (stderr);
    exit (1);
  }

  f = fopen (argv[3], "rb");
  unsigned char buf[1024];
  int           size;
  while (!feof (f)) {
    if ((size = fread (buf, 1, 1024, f)) <= 0) break;
    EVP_SignUpdate (mdctx, buf, size);
  }
  unsigned char sig[1024];
  unsigned int  sig_len;
    
  if (EVP_SignFinal(mdctx, sig, &sig_len, priv_key) <=0) {
    ERR_print_errors_fp (stderr);
    exit (1);
  }
#if 0  
  /* Print Signature */
  for (int i = 0; i < sig_len; i++) {
        if (i != 0 && i % 30 == 0) printf ("\n");
    printf ("%02x", (unsigned char) sig[i]);

  }
  printf ("\n");
#endif
  fwrite (sig, 1, sig_len, stdout);
}
// gcc -O0 -g -o firmado firmado.c -lcrypto -lssl
