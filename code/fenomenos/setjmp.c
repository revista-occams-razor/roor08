#include <stdio.h>
#include <setjmp.h>

jmp_buf b1;

int foo () {
  printf (" > foo inicio\n");
  if (setjmp (b1) != 0) {
    printf ("Llamada especial\n");
  } else
    printf (" > foo final\n");
}

int main () {
  printf ("> main ()\n");
  foo (); // poin setjmp
  longjmp (b1, 1);
  printf ("> main fin\n");
}
