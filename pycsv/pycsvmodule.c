#include <Python.h>

/** Here, we create our new type **/

/* This is the PyObject which Python will manipulate the object
   using */
typedef struct {
    PyObject_HEAD
} pycsv_CSVFileObject;

/* This is the Python type definition which is used to find what
   function to call when type methods are accessed */
static PyTypeObject pycsv_PyCSVFileType = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "pycsv.CSVFile",			/* tp_name */
    sizeof(pycsv_CSVFileObject),	/* tp_basicsize */
    0,					/* tp_itemsize */
    0,					/* tp_dealloc */
    0,					/* tp_print */
    0,					/* tp_getattr */
    0,					/* tp_setattr */
    0,					/* tp_reserved */
    0,					/* tp_repr */
    0,					/* tp_as_number */
    0,					/* tp_as_sequence */
    0,					/* tp_as_mapping */
    0,					/* tp_hash  */
    0,					/* tp_call */
    0,					/* tp_str */
    0,					/* tp_getattro */
    0,					/* tp_setattro */
    0,					/* tp_as_buffer */
    Py_TPFLAGS_DEFAULT,			/* tp_flags */
    "CSVFile ",                         /* tp_doc */
};




/** All the stuff below is for the module **/
static PyMethodDef PyCSVMethods[] = {
  {NULL, NULL, 0, NULL} 
};

static struct PyModuleDef pycsvmodule = {
   PyModuleDef_HEAD_INIT,
   "pycsv",   /* name of module */
   "A wrapper for libcsv which exposes csv files as 'file' like objects.",        /* docstring */
   -1,
   PyCSVMethods, /* This could be NULL if we have nothing in the module */
   NULL,      /* m_reload : unused */
   NULL,      /* m_traverse : GC traversal function */
   NULL,      /* m_clear    : GC clear function */
   NULL,      /* m_free     : Memory free function */
};

PyMODINIT_FUNC /* The only non static function in file */
PyInit_pycsv(void)
{
  PyObject *c;
  pycsv_PyCSVFileType.tp_new = PyType_GenericNew;
  if (PyType_Ready(&pycsv_PyCSVFileType) < 0)
        return NULL;
  
  c = PyModule_Create(&pycsvmodule);
  if (c == NULL)
    return NULL;

  Py_INCREF(&pycsv_PyCSVFileType);
  PyModule_AddObject(c, "CSVFile", (PyObject *)&pycsv_PyCSVFileType);
  return c;
}
