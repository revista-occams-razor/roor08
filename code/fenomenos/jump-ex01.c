#include <stdio.h>

void *f1 = NULL;


int foo (int a) {

  f1 = &&label_foo1;
  puts ("> foo inicio");
  
  if (a) {
  label_foo1:
    puts ("Llamada especial");
    return 0;
  }

  printf ("> foo final\n");
  return 0;
}




int main () { 
  puts ("> main ()");
  foo (0);
  goto *f1;
  //f1();
  puts ("> main fin");
}
