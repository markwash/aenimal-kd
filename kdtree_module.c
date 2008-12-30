#include <Python.h>
#include "structmember.h"

#include "kdtree.h"

typedef struct {
	PyObject_HEAD
	kdtree_t *kdt;
} KDTreeObject;

static PyTypeObject KDTreeType = {
	PyObject_HEAD_INIT(NULL)
	0,						/*ob_size*/
	"kdtree.KDTree",		/*tp_name*/
	sizeof(KDTreeObject),	/*tp_basicsize*/
	0,						/*tp_itemsize*/
	0,						/*tp_dealloc*/
	0,						/*tp_print*/
	0,						/*tp_getattr*/
	0,						/*tp_setattr*/
	0,						/*tp_compare*/
	0,						/*tp_repr*/
	0,						/*tp_as_number*/
	0,						/*tp_as_sequence*/
	0,						/*tp_as_mapping*/
	0,						/*tp_hash */
	0,						/*tp_call*/
	0,						/*tp_str*/
	0,						/*tp_getattro*/
	0,						/*tp_setattro*/
	0,						/*tp_as_buffer*/
	Py_TPFLAGS_DEFAULT,		/*tp_flags*/
	"KDTree objects",		/* tp_doc */
};

static PyMethodDef methods[] = {
	{NULL}  /* Sentinel */
};

#ifndef PyMODINIT_FUNC	/* declarations for DLL import/export */
#define PyMODINIT_FUNC void
#endif
PyMODINIT_FUNC
initkdtree(void) 
{
	PyObject* m;

	KDTreeType.tp_new = PyType_GenericNew;
	if (PyType_Ready(&KDTreeType) < 0)
		return;

	m = Py_InitModule3("kdtree", methods,
					   "KD Tree extension.");

	Py_INCREF(&KDTreeType);
	PyModule_AddObject(m, "KDTree", (PyObject *)&KDTreeType);
}

