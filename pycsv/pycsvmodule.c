#include <Python.h> /* Includes string.h */
#include "structmember.h"

#include "csv.h"

/* We put all the non python extras that we need over here */
typedef struct {
  PyObject *cell_callback;
  PyObject *row_callback;
  PyObject *callback_data;
} CSVCallbacks;

void 
cell_callback(void *c_cell_data, size_t len, void *extra_data)
{
  PyObject *py_cell_callback = ((CSVCallbacks *)extra_data)->cell_callback;
  PyObject *py_callback_data = ((CSVCallbacks *)extra_data)->callback_data;
  PyUnicodeObject *py_cell_data;
  py_cell_data = (PyUnicodeObject *)PyUnicode_FromStringAndSize((const char *)c_cell_data, len);

  if (py_cell_callback != Py_None) {
    /* We should actually check for errors here */
    PyObject_CallFunctionObjArgs(py_cell_callback, 
				 py_cell_data,
				 py_callback_data,
				 NULL); 
  }
}

void 
row_callback(int terminator, void *extra_data) 
{
  PyObject *py_row_callback = ((CSVCallbacks *)extra_data)->row_callback;
  PyObject *py_callback_data = ((CSVCallbacks *)extra_data)->callback_data;
  if (py_row_callback != Py_None) {
    /* We should actually check for errors here */
    PyObject_CallFunctionObjArgs(py_row_callback, 
				 py_callback_data,
				 NULL); 
  }
}


/** Here, we create our new type **/

/* This is the PyObject which Python will manipulate the object
   using */
typedef struct {
    PyObject_HEAD
    PyObject *file;
} PyCSVFile;

/* Type Method definitions */

static void
PyCSVFile_dealloc(PyCSVFile* self)
{
    Py_XDECREF(self->file);
    Py_TYPE(self)->tp_free((PyObject*)self);
}

static PyObject *
PyCSVFile_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
  PyCSVFile *retval;
  retval = (PyCSVFile *)type->tp_alloc(type, 0);
  if (retval != NULL) {
    Py_INCREF(Py_None);
    retval->file = Py_None;
  }
  return (PyObject *)retval;
}

static int
PyCSVFile_init(PyCSVFile *self, PyObject *args, PyObject *kwds)
{
  PyObject *file = NULL, *tmp;
  if (! PyArg_ParseTuple(args,"O", &file)) {
    return -1;
  }

  if (file) {
    tmp = self->file; 
    Py_INCREF(file);
    self->file = file;
    Py_XDECREF(tmp);
    /* Not as follows

       Py_XDECREF(self->file);
       Py_INCREF(file);
       self->file = file;

       The destructor code could access the ->file member
    */
  }
  PyObject_SetAttrString((PyObject *)self, "_file", file);
  return 0;
}


/* Methods and attributes */
static PyMemberDef PyCSVFile_members[] = {
  {"_file", T_OBJECT_EX, offsetof(PyCSVFile, file), 0, "File"},
  {NULL}
};

/* Custom Methods for the class */

static PyObject *
PyCSVFile_parse(PyCSVFile *self, PyObject *args)
{
  PyObject *python_cell_callback = Py_None;
  PyObject *python_row_callback  = Py_None;
  PyObject *python_ext_data      = Py_None;
  char *data              = NULL;
  CSVCallbacks callbacks;
  struct csv_parser parser;

  if (! PyArg_ParseTuple(args,"|OOO", &python_cell_callback, &python_row_callback, &python_ext_data)) {
    return NULL;
  }
  data = PyBytes_AsString(PyUnicode_AsASCIIString(PyObject_CallMethod(self->file, "read", NULL)));
  callbacks.cell_callback = python_cell_callback;
  callbacks.row_callback  = python_row_callback;
  callbacks.callback_data = python_ext_data;
  csv_init(&parser, CSV_APPEND_NULL);
  csv_parse(&parser, 
	    data, strlen(data), 
	    cell_callback, 
	    row_callback,
	    &callbacks);
  Py_RETURN_NONE;

  /* return contents;  */
}

static PyMethodDef PyCSVFile_methods[] = {
  {"parse", (PyCFunction)PyCSVFile_parse, METH_VARARGS,
   "Parses the actual CSV File"
  },
  {NULL}  /* Sentinel */
};



/* This is the Python type definition which is used to find what
   function to call when type methods are accessed */
static PyTypeObject PyCSVFileType = {
  PyVarObject_HEAD_INIT(NULL, 0)        /* The metaclass */
  "pycsv.CSVFile",			/* tp_name */
  sizeof(PyCSVFile),			/* tp_basicsize */
  0,					/* tp_itemsize */
  (destructor)PyCSVFile_dealloc,            /*tp_dealloc*/
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
  PyCSVFile_methods,                    /* tp_methods */
  PyCSVFile_members,                    /* tp_members */
  0,					/* tp_getset */
  0,					/* tp_base */
  0,					/* tp_dict */
  0,					/* tp_descr_get */
  0,					/* tp_descr_set */
  0,					/* tp_dictoffset */
  (initproc)PyCSVFile_init,		/* tp_init */
  0,					/* tp_alloc */
  PyCSVFile_new,                        /* tp_new */
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
