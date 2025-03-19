#include <stdio.h>
#include <string.h>
#include <unistd.h>

char *clave = "ClaveSuperSecreta";
char buf[1024];

int main () {
  printf ("PID: %ld\n", getpid());
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
