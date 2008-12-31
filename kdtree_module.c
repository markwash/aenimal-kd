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
	// decref on all the objects in the tree
	double x, y;
	PyObject *o;
	kdtree_iter_ctx_t *ctx;
	ctx = kdtree_iter_ctx_new(self->kdt);
	while (ctx != NULL) {
		kdtree_iter_ctx_next(&ctx, &x, &y, (const void **) &o);
		Py_DECREF(o);
	}

	// free the tree
	kdtree_free(self->kdt);
	self->kdt = NULL;

	self->ob_type->tp_free((PyObject *) self);
}

static int
KDTree_init(KDTree *self, PyObject *args, PyObject *kwds)
{
	// if the tree isn't null, we're being called twice,
	// which just isn't cool
	if (self->kdt != NULL) {
		PyErr_SetObject(PyExc_NotImplementedError, (PyObject *) self);
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

	self->kdt = kdtree_new(cap);
	if (self->kdt == NULL) {
		PyErr_SetObject(PyExc_MemoryError, (PyObject *) self);
		return -1;
	}
	
	return 0;
	
}

static int key_as_two_doubles(PyObject *key, double *x, double *y)
{
	PyObject *x_elem = NULL, *y_elem = NULL;
	PyObject *x_float = NULL, *y_float = NULL;	

	// check that the object is sequential
	if (!PySequence_Check(key)) {
		goto keyerror;
	}

	// check that there are exactly two elements
	if (PySequence_Size(key) != 2) {
		goto keyerror;
	}
	
	// extract two elements
	if ((x_elem = PySequence_GetItem(key, 0)) == NULL) {
		goto keyerror;
	}
	if ((y_elem = PySequence_GetItem(key, 1)) == NULL) {
		goto keyerror;
	}

	// check that both are numbers
	if (!PyNumber_Check(x_elem)) {
		goto keyerror;
	}
	if (!PyNumber_Check(y_elem)) {
		goto keyerror;
	}

	// coerce numbers to floats
	if ((x_float = PyNumber_Float(x_elem)) == NULL) {
		goto keyerror;
	}
	if ((y_float = PyNumber_Float(y_elem)) == NULL) {
		goto keyerror;
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

	// return key error
	keyerror:
	PyErr_SetObject(PyExc_KeyError, key);
	Py_XDECREF(x_elem);
	Py_XDECREF(y_elem);
	Py_XDECREF(x_float);
	Py_XDECREF(y_float);
	return -1;

}

static Py_ssize_t
KDTree_size(KDTree *self)
{
	return kdtree_size(self->kdt);
}

static PyObject *
KDTree_get_item(KDTree *self, PyObject *key)
{
	double x, y;
	if (key_as_two_doubles(key, &x, &y) == -1) {
		return NULL;
	}

	PyObject *ret;
	ret = (PyObject *) kdtree_get(self->kdt, x, y);
	if (ret == NULL) {
		PyErr_SetObject(PyExc_KeyError, key);
		return NULL;
	}
	
	Py_INCREF(ret);
	return ret;
}

static int
KDTree_set_item(KDTree *self, PyObject *key, PyObject *value)
{
	double x, y;
	if (key_as_two_doubles(key, &x, &y) == -1) {
		return -1;
	}

	if (value == NULL) {
		// actually deleting
		Py_XDECREF((PyObject *) kdtree_get(self->kdt, x, y));
		kdtree_del(self->kdt, x, y);
	} else {
		Py_INCREF(value);
		kdtree_add(self->kdt, x, y, value);
	}

	return 0;
}

static PyMappingMethods KDTree_as_mapping = {
	(inquiry) KDTree_size,			/* inquiry mp_length;				__len__ */
	(binaryfunc) KDTree_get_item,	/* binaryfunc mp_subscript;			__getitem__ */
	(objobjargproc) KDTree_set_item,/* objobjargproc mp_ass_subscript;	__setitem__ */
};

static int
KDTree_contains(KDTree *self, PyObject *key)
{
	double x, y;
	if (key_as_two_doubles(key, &x, &y) == -1) {
		return -1;
	}

	return kdtree_has(self->kdt, x, y);
}

static PySequenceMethods KDTree_as_sequence = {
	0,				/* lenfunc sq_length */
	0,				/* binaryfunc sq_concat */
	0,				/* ssizeargfunc sq_repeat */
	0,				/* ssizeargfunc sq_item */
	0,				/* ssizessizeargfunc sq_slice */
	0,				/* ssizeobjargproc sq_ass_item */
	0,				/* ssizessizeobjargproc sq_ass_slice */
	(objobjproc) KDTree_contains,/* objobjproc sq_contains */
	0,				/* binaryfunc sq_inplace_concat */
	0,				/* ssizeargfunc sq_inplace_repeat */
};

static PyObject *
KDTree_nn(KDTree *self, PyObject *args)
{
	double x, y;
	if (!PyArg_ParseTuple(args, "dd", &x, &y)) {
		return NULL;
	}

	neighbor_t nb;
	kdtree_nn(self->kdt, x, y, &nb, 0);

	return Py_BuildValue("dddO", nb.x, nb.y, nb.dist,
			(PyObject *) nb.data);
}

static PyMethodDef KDTree_methods[] = {
	{"nn", (PyCFunction) KDTree_nn, 
		METH_VARARGS, "nearest neighbor search"},
	{NULL},	/* Sentinel */
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
	&KDTree_as_sequence,	/*tp_as_sequence*/
	&KDTree_as_mapping,		/*tp_as_mapping*/
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
	KDTree_methods,			/* tp_methods */
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

