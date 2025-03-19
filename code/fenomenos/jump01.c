#include <stdio.h>

int (*f1)() = NULL;
int (*f2)() = NULL;

int (*b1)() = NULL;
int (*b2)() = NULL;


int foo (int a) {
  f1 = &&label_foo1+1;
  f2 = &&label_foo2;
  printf ("> Función foo entrada\n");
  
  if (a) {
    __asm__ ("pop %rbp;ret");
    //__asm__ (".byte 0xe8");
    __asm__ (".short 0x053b");
  label_foo1:
    __asm__ (".byte 0xe8");
    printf ("Función foo secreta 1: %p\n", &&label_foo1);
    b1 ();

    __asm__ ("ret");
        __asm__ (".byte 0x80");
  label_foo2:
    printf ("Función foo secreta 2: %p\n", &&label_foo2);

    __asm__ ("ret");

  }
 label_end:
  printf ("> Función foo salida\n");
  return 0;
}


int bar (int a) {
  b1 = &&label_bar1;
  b2 = &&label_bar2;
  printf ("> Función foo entrada\n");
  
  if (a) {
    __asm__ ("pop %rbp;ret");
    __asm__ (".byte 0x48");
  label_bar1:
    printf ("Función bar secreta 1: %p\n", &&label_bar1);

    __asm__ ("ret");
  label_bar2:
    printf ("Función bar secreta 2: %p\n", &&label_bar2);

    __asm__ ("ret");

  }
 label_end:
  printf ("> Función foo salida\n");
  return 0;
}


int main () {
  printf ("> Función main\n");
 label_main:
  foo (0);
  bar (0);
  printf ("Dirección en main: %p\n", &&label_main);
  printf ("Dirección en foo: %p\n", f1);
  f1();
  f2();
  b2();
}
