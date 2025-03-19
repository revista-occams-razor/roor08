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
  EVP_PKEY         *pub_key = NULL;
  /* Función Hash*/
  const EVP_MD      *md;
  EVP_MD_CTX        *mdctx;

  if (argc != 5) {
    fprintf (stderr, "Usage:¨\n%s public.pem hash-algo input_file firma\n",
	     argv[0]);
    exit (1);
  }
  libctx = NULL; /* Usa el contexto de librería por defecto */

  /* Adquirimos las claves para el firmado */
  dctx = OSSL_DECODER_CTX_new_for_pkey (&pub_key, NULL, NULL, NULL,
					EVP_PKEY_PUBLIC_KEY,libctx, NULL);

  /* Lee clave pública */
  FILE *f = fopen (argv[1], "rb");
  OSSL_DECODER_from_fp(dctx, f);
  fclose (f);
  OSSL_DECODER_CTX_free(dctx);

  /* Lee firma */
  int           size;
  int           esig_len = 0;
  unsigned char esig[1024];
  
  f = fopen (argv[4], "rb");
  if ((esig_len = fread (esig, 1, 1024, f)) < 0){
    fprintf (stderr, "Error leyendo firma digital\n");
  }
  fclose (f);


  /* creamos función Hash */
  if ((md = EVP_get_digestbyname (argv[2])) == NULL) {
        ERR_print_errors_fp (stderr);
  }

  mdctx = EVP_MD_CTX_create ();

  if (EVP_VerifyInit (mdctx, md) <= 0) {
    ERR_print_errors_fp (stderr);
    exit (1);
  }

  f = fopen (argv[3], "rb");
  unsigned char buf[1024];

  while (!feof (f)) {
    if ((size = fread (buf, 1, 1024, f)) <= 0) break;
    EVP_VerifyUpdate (mdctx, buf, size);
  }
  unsigned char sig[1024];
  unsigned int  sig_len;
    
  if (EVP_VerifyFinal(mdctx, esig, esig_len, pub_key) <=0) {
    //ERR_print_errors_fp (stderr);
    printf ("Firma incorrecta\n");
    exit (1);
  }
  printf ("Verificación OK\n");
  
}
// gcc -O0 -g -o firmado firmado.c -lcrypto -lssl
