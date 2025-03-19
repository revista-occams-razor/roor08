#include <stdio.h>

int (*f1)() = NULL;
int (*f2)() = NULL;


int foo (int a) {
  f1 = &&label_foo1;
  f2 = &&label_foo2-10;
  f2+=10;
  printf ("> Funcion foo entrada\n");
  
  if (a) {
    __asm__ ("pop %rbp;ret");
    ////__asm__ (".byte 0xe8");
    //__asm__ (".short 0x053b");
    __asm__ ("jmp . -10");
    __asm__ (".asciz \"Prueba\"");
  label_foo1:
    ////__asm__ (".byte 0xe8");
    puts ("Codigo foo 1\n");

    __asm__ ("ret");
    //__asm__ (".byte 0x80");
    __asm__ ("jmp . + 30");
    __asm__ (".asciz \"Pruebb\"");
  label_foo2:
    puts ("Codigo foo 2\n");

    __asm__ ("ret");

  }
 label_end:
  printf ("> Funcion foo salida\n");
  return 0;
}



int main () {
  printf ("> Funcion main\n");
 label_main:
  foo (0);
  //  printf ("Direccion en main: %p\n", &&label_main);
  //  printf ("Direccion en foo: %p\n", f1);
  f1();
  f2();
}
