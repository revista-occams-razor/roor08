#define PY_SSIZE_T_CLEAN
#include <Python.h>


// Set PYTHONPATH=.
// Py_SetPath (".") DEPRECATED
int
main(int argc, char *argv[])
{
  Py_Initialize ();

  
  //PyObject *pName = PyUnicode_DecodeFSDefault ("func");
  //PyObject *pModule = PyImport_Import (pName);
  //Py_DECREF (pName);
  PyObject *pModule = PyImport_ImportModule ("func");
  
  if (pModule) {
    /* Obtengamos la función a llamar */
    PyObject *bar = PyObject_GetAttrString (pModule, "bar");
    printf ("bar = %ld\n", PyLong_AsLong(bar));
    PyObject *pFunc = PyObject_GetAttrString (pModule, "foo");
    if (pFunc && PyCallable_Check(pFunc)) {
      PyObject *pArgs = PyTuple_New (3); // 3 Parámetros
      PyObject *pValue = PyUnicode_FromString ("Hola Mundo!");
      PyTuple_SetItem (pArgs, 0, pValue);
      
      pValue = PyLong_FromLong (10);
      PyTuple_SetItem (pArgs, 1, pValue);
      pValue = PyLong_FromLong (20);
      PyTuple_SetItem (pArgs, 2,pValue);
      
      pValue = PyObject_CallObject (pFunc, pArgs);
      

      printf ("Resultado : %ld\n", PyLong_AsLong(pValue));
      Py_DECREF(pArgs);
      Py_DECREF(pValue);
    }
    
    Py_XDECREF(pFunc);
    Py_DECREF (pModule);
  }
  if (Py_FinalizeEx() < 0) {
    exit(120);    
  }

  return 0;

}
