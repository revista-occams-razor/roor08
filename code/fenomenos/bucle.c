#include <stdio.h>
#include <setjmp.h>


int main () {
  jmp_buf b1;
	int  i = 0;
  setjmp (b1);
	printf ("Contando %d\n",i++);
	longjmp(b1,0);
}
