#include <Python.h>
#include "structmember.h"

#include "kdtree.h"

typedef struct {
	PyObject_HEAD
	kdtree_t *kdt;
} KDTree;

static void
KDTree_dealloc(KDTree *self)
{
	self->ob_type->tp_free((PyObject *) self);
}

static int
KDTree_init(KDTree *self, PyObject *args, PyObject *kwds)
{
	// if the tree isn't null, we're being called twice,
	// which just isn't cool
	if (self->kdt != NULL) {
		// TODO: figure out exceptions and set one
		return -1;
	}

	static char* kwdlist[] = {"initcap", NULL};
	size_t cap = 0;

	// parse the arguments to figure out the optional
	// initial capacity
	if (! PyArg_ParseTupleAndKeywords(
				args,
				kwds,
				"|I",
				kwdlist,
				&cap
			) ) {
		return -1;
	}

	// TODO: figure out exceptions and set one
	self->kdt = kdtree_new(cap);
	if (self->kdt == NULL) {
		return -1;
	}
	
	return 0;
	
}

static int object_as_two_doubles(PyObject *o, double *x, double *y)
{
	// check that the object is sequential
	if (!PySequence_Check(o)) {
		// TODO: set key exception
		return -1;
	}

	// check that there are exactly two elements
	if (PySequence_Size(o) != 2) {
		// TODO: set key exception
		return -1;
	}
	
	// extract two elements
	PyObject *x_elem, *y_elem;
	if ((x_elem = PySequence_GetItem(o, 0)) == NULL) {
		return -1;
	}
	if ((y_elem = PySequence_GetItem(o, 1)) == NULL) {
		Py_DECREF(x_elem);
		return -1;
	}

	// check that both are numbers
	if (!PyNumber_Check(x_elem)) {
		// TODO: set key exception
		Py_DECREF(x_elem);
		Py_DECREF(y_elem);
		return -1;
	}
	if (!PyNumber_Check(y_elem)) {
		// TODO: set key exception
		Py_DECREF(x_elem);
		Py_DECREF(y_elem);
		return -1;
	}

	// coerce numbers to floats
	PyObject *x_float, *y_float;
	if ((x_float = PyNumber_Float(x_elem)) == NULL) {
		Py_DECREF(x_elem);
		Py_DECREF(y_elem);
		return -1;
	}
	if ((y_float = PyNumber_Float(y_elem)) == NULL) {
		Py_DECREF(x_elem);
		Py_DECREF(y_elem);
		Py_DECREF(x_float);
		return -1;
	}

	// extract C doubles
	*x = PyFloat_AS_DOUBLE(x_float);
	*y = PyFloat_AS_DOUBLE(y_float);

	// return success
	Py_DECREF(x_elem);
	Py_DECREF(y_elem);
	Py_DECREF(x_float);
	Py_DECREF(y_float);
	return 0;

}

static PyObject *
kdtree_get_item(KDTree *self, PyObject *key)
{
	double x, y;
	if (object_as_two_doubles(key, &x, &y) == -1) {
		return NULL;
	}

	PyObject *ret;
	ret = (PyObject *) kdtree_get(self->kdt, x, y);
	if (ret == NULL) {
		// TODO: set key exception
		return NULL;
	}
	
	Py_INCREF(ret);
	return ret;
}

static int
kdtree_set_item(KDTree *self, PyObject *key, PyObject *value)
{
	if (value == NULL) {
		// TODO: exception?
		return -1;
	}

	double x, y;
	if (object_as_two_doubles(key, &x, &y) == -1) {
		return -1;
	}

	kdtree_add(self->kdt, x, y, value);

	return 0;
}

PyMappingMethods kdtree_mapping = {
	0,				/* inquiry mp_length;				__len__ */
	(binaryfunc) kdtree_get_item,	/* binaryfunc mp_subscript;			__getitem__ */
	(objobjargproc) kdtree_set_item,/* objobjargproc mp_ass_subscript;	__setitem__ */
};


static PyTypeObject KDTreeType = {
	PyObject_HEAD_INIT(NULL)
	0,						/*ob_size*/
	"kdtree.KDTree",		/*tp_name*/
	sizeof(KDTree),			/*tp_basicsize*/
	0,						/*tp_itemsize*/
	(destructor)KDTree_dealloc,	/*tp_dealloc*/
	0,						/*tp_print*/
	0,						/*tp_getattr*/
	0,						/*tp_setattr*/
	0,						/*tp_compare*/
	0,						/*tp_repr*/
	0,						/*tp_as_number*/
	0,						/*tp_as_sequence*/
	&kdtree_mapping,		/*tp_as_mapping*/
	0,						/*tp_hash */
	0,						/*tp_call*/
	0,						/*tp_str*/
	0,						/*tp_getattro*/
	0,						/*tp_setattro*/
	0,						/*tp_as_buffer*/
	Py_TPFLAGS_DEFAULT,		/*tp_flags*/
	"KDTree objects",		/* tp_doc */
	0,						/* tp_traverse */
	0,						/* tp_clear */
	0,						/* tp_richcompare */
	0,						/* tp_weaklistoffset */
	0,						/* tp_iter */
	0,						/* tp_iternext */
	0,						/* tp_methods */
	0,						/* tp_members */
	0,						/* tp_getset */
	0,						/* tp_base */
	0,						/* tp_dict */
	0,						/* tp_descr_get */
	0,						/* tp_descr_set */
	0,						/* tp_dictoffset */
	(initproc)KDTree_init,	/* tp_init */
	0,						/* tp_alloc */
	0,						/* tp_new */
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

