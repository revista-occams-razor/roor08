#define PY_SSIZE_T_CLEAN
#include <Python.h>
//#include <wchar.h>
#include <unistd.h>
#include <fcntl.h>

static PyObject* mimod_test1 (PyObject *self, PyObject *args);

static PyMethodDef mimodMethods[] = {
  {"test1", mimod_test1, METH_VARARGS, "Función de prueba cutre"},
  {NULL, NULL, 0, NULL},
};

static PyModuleDef _Module = {
  PyModuleDef_HEAD_INIT, "mimod", NULL, -1, mimodMethods,
  NULL, NULL, NULL, NULL
};

static PyObject*
PyInit_mimod (void) {
  printf ("**Moduilo importado..\n");
  return PyModule_Create (&_Module);
}


static PyObject*
mimod_test1 (PyObject *self, PyObject *args) {
  char  *str;
  int   a, b;
  if (!PyArg_ParseTuple (args, "sii", &str, &a, &b))
    return NULL;
  printf ("TEST1: Cadena: '%s' Suma: %d\n", str, a+b);
  return PyLong_FromLong(a+b);
}


//extern void* _binary_libs_tgz_start;
//extern void* _binary_libs_tgz_size;

extern int _binary_libs_tgz_start;
extern int _binary_libs_tgz_size;

// Set PYTHONPATH=.
// Py_SetPath (".") DEPRECATED
int
main(int argc, char *argv[])
{
  //unsigned char *p =  (unsigned char*)((uint64_t)&_binary_libs_tgz_start);
  //size_t         ps = (long) ((uint64_t)&_binary_libs_tgz_size);

  //printf ("Binary data at: %p\n",    &_binary_libs_tgz_start);
  //printf ("Binary data size: %lx\n", &_binary_libs_tgz_size);

  
  // Pre inicializacion https://docs.python.org/3/c-api/init.html#pre-init-safe
  //printf ("Binary data at: %p\n",    (void*)((uint64_t)&_binary_lib_tgz_start));
  //printf ("Binary data size: %lx\n", (long) ((uint64_t)&_binary_lib_tgz_size));

  printf ("Binary data at: %p\n",    &_binary_libs_tgz_start);
  printf ("Binary data size: %lx\n", (long)&_binary_libs_tgz_size);
  mkdir ("/tmp/example04", 0777);
  int fd = open ("/tmp/example04/libs.tgz", O_CREAT | O_WRONLY, 0777);
  write (fd, &_binary_libs_tgz_start, (long)&_binary_libs_tgz_size);
  close (fd);
  system ("tar xzf /tmp/example04/libs.tgz -C /tmp/example04");
  

  
#if 1
  PyStatus status;
  PyConfig config;

  PyConfig_InitPythonConfig (&config);
  config.module_search_paths_set = 1;
  config.isolated = 1;
  PyWideStringList_Append (&config.module_search_paths, L".");
  PyWideStringList_Append (&config.module_search_paths, L"/tmp/example04/libs");
  
#endif
  PyImport_AppendInittab ("mimod", &PyInit_mimod);

#if 1
  status = Py_InitializeFromConfig(&config);
  if (PyStatus_Exception(status)) {
    goto exception;
  }
  PyConfig_Clear(&config);
#endif
  Py_Initialize ();
  // Add C defined moduile
 
  PyObject *pName = PyUnicode_DecodeFSDefault ("func1");
  PyObject *pModule = PyImport_Import (pName);
  Py_DECREF (pName);
  
  if (pModule) {
    printf ("%s", "El módulo se ha importado con exito\n");
    /* Obtengamos la función a llamar */
    PyObject *pFunc = PyObject_GetAttrString (pModule, "foo");
    if (pFunc) {
      printf ("%s", "Función encontrada... Listos para ejecutar\n");
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
      Py_XDECREF(pFunc);
      Py_DECREF(pModule);

    }
  }
  system ("rm -Rf /tmp/example04");
  if (Py_FinalizeEx() < 0) {
    exit(120);
    

#if 1
exception:
    PyConfig_Clear(&config);
    if (PyStatus_IsExit(status)) {
        return status.exitcode;
    }
    /* Display the error message and exit the process with
       non-zero exit code */
    Py_ExitStatusException(status);
#endif
  }
  
  return 0;

}
