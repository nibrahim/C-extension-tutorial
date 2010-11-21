#include <Python.h>

static PyMethodDef PyCSVMethods[] = {
  {NULL, NULL, 0, NULL} 
};

static struct PyModuleDef pycsvmodule = {
   PyModuleDef_HEAD_INIT,
   "pycsv",   /* name of module */
   "",        /* docstring */
   -1,
   PyCSVMethods
};

PyMODINIT_FUNC /* The only non static function in file */
PyInit_pycsv(void)
{
    return PyModule_Create(&pycsvmodule);
}
