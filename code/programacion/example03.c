#define PY_SSIZE_T_CLEAN
#include <Python.h>
//#include <wchar.h>

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


// Set PYTHONPATH=.
// Py_SetPath (".") DEPRECATED
int
main(int argc, char *argv[])
{
  // Pre inicializacion https://docs.python.org/3/c-api/init.html#pre-init-safe

#if 1
  PyStatus status;
  PyConfig config;

  PyConfig_InitPythonConfig (&config);
  config.module_search_paths_set = 1;
  config.isolated = 1;
  PyWideStringList_Append (&config.module_search_paths, L".");
  PyWideStringList_Append (&config.module_search_paths, L"./libs");
  
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
