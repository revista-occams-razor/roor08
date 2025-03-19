#include <stdio.h>
#include <string.h>
#include <unistd.h>

char *clave = "ClaveSuperSecreta";


int main () {
  char buf[1024];
  printf ("PID: %ld (buf: %p)\n", getpid(), buf);
	printf ("S3DY3. Sistema Super Secreto de Yvil Yenius\n");
  printf ("Introduce la clave: ");
  gets (buf);
  if (strncmp (buf, clave, strlen(clave)) == 0) {
    printf ("Acceso al sistema guay\n");
    getchar ();
  } else {
    printf ("Mala suerte\n");
    getchar();
  }
}
