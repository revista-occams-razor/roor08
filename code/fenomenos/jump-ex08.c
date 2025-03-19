#include <stdio.h>

int (*f1)() = NULL;
int (*f2)() = NULL;


int foo (int a) {
  f1 = &&label_foo1 - 0x1234;
  f2 = &&label_foo2 + 0x4321;
  puts ("> foo inicio");
  f1 += 0x1234;
  f2 -= 0x4321;
  
  if (a) {
    __asm__ ("jmp . + 74");
    __asm__ (".asciz \"PRUEBA\"");
  label_foo1:
    puts ("Llamada especial 1");
    __asm__ ("ret");
    __asm__ ("jmp . + 49");
    __asm__ (".asciz \"PRUEBA\"");
  label_foo2:
    puts ("Llamada especial 2");
    __asm__ ("ret");
  }
 label_end:
  puts ("> foo final");
  return 0;
}



int main () {
  puts ("> main ()");
  foo (0);
  f1();
  f2();
  puts ("> main fin");
}
