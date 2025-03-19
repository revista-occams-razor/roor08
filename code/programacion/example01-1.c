#define PY_SSIZE_T_CLEAN
#include <Python.h>

int
main(int argc, char *argv[])
{
  Py_Initialize ();
    
  PyRun_SimpleString("from time import time,ctime\n"
		     "print('Today is', ctime(time()))\n");
  
  if (Py_FinalizeEx() < 0) {
    exit(120);
  }
  return 0;

}
