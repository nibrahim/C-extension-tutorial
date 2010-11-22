#include <Python.h>

/** Here, we create our new type **/

/* This is the PyObject which Python will manipulate the object
   using */
typedef struct {
    PyObject_HEAD
} PyCSVFile;

/* Type Method definitions */
static int
PyCSVFile_init(PyCSVFile *self, PyObject *args, PyObject *kwds)
{
  PyObject *file = NULL;
  if (! PyArg_ParseTuple(args,"O", &file)) {
    return -1;
  }
 
  return 0;
}

/* Adding the methods to the type */
/* static PyMethodDef Noddy_methods[] = { */
/*     {"name", (PyCFunction)Noddy_name, METH_NOARGS, */
/*      "Return the name, combining the first and last name" */
/*     }, */
/*     {NULL}  /\* Sentinel *\/ */
/* }; */


/* This is the Python type definition which is used to find what
   function to call when type methods are accessed */
static PyTypeObject PyCSVFileType = {
  PyVarObject_HEAD_INIT(NULL, 0)        /* The metaclass */
  "pycsv.CSVFile",			/* tp_name */
  sizeof(PyCSVFile),			/* tp_basicsize */
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
  "CSVFile objects",			/* tp_doc */
  0,					/* tp_traverse */
  0,					/* tp_clear */
  0,					/* tp_richcompare */
  0,					/* tp_weaklistoffset */
  0,					/* tp_iter */
  0,					/* tp_iternext */
  0,					/*Noddy_methods,              tp_methods */
  0,					/*Noddy_members,              tp_members */
  0,					/* tp_getset */
  0,					/* tp_base */
  0,					/* tp_dict */
  0,					/* tp_descr_get */
  0,					/* tp_descr_set */
  0,					/* tp_dictoffset */
  (initproc)PyCSVFile_init,		/* tp_init */
  0,					/* tp_alloc */
  0,					/* tp_new */
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
   NULL,      /* m_reload   : unused */
   NULL,      /* m_traverse : GC traversal function */
   NULL,      /* m_clear    : GC clear function */
   NULL,      /* m_free     : Memory free function */
};

PyMODINIT_FUNC /* The only non static function in file */
PyInit_pycsv(void)
{
  PyObject *c;
  PyCSVFileType.tp_new = PyType_GenericNew;
  if (PyType_Ready(&PyCSVFileType) < 0)
        return NULL;
  
  c = PyModule_Create(&pycsvmodule);
  if (c == NULL)
    return NULL;

  Py_INCREF(&PyCSVFileType);
  PyModule_AddObject(c, "CSVFile", (PyObject *)&PyCSVFileType);
  return c;
}
