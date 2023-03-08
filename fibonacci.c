#include <Python.h>

static PyObject* fibonacci(PyObject* self, PyObject* args) {
    PyObject* input_list;
    if (!PyArg_ParseTuple(args, "O", &input_list)) {
        return NULL;
    }

    if (!PyList_Check(input_list)) {
        PyErr_SetString(PyExc_TypeError, "Expected a list of integers.");
        return NULL;
    }

    Py_ssize_t size = PyList_Size(input_list);
    PyObject* output_dict = PyDict_New();
    if (!output_dict) {
        return NULL;
    }

    for (Py_ssize_t i = 0; i < size; ++i) {
        PyObject* input_obj = PyList_GetItem(input_list, i);
        if (!PyLong_Check(input_obj)) {
            PyErr_SetString(PyExc_TypeError, "Expected a list of integers.");
            Py_DECREF(output_dict);
            return NULL;
        }

        long long input = PyLong_AsLongLong(input_obj);
        if (input == -1 && PyErr_Occurred()) {
            Py_DECREF(output_dict);
            return NULL;
        }

        if (input < 0) {
            PyErr_SetString(PyExc_ValueError, "Expected a non-negative integer.");
            Py_DECREF(output_dict);
            return NULL;
        }

        if (input == 0) {
            PyObject* output_obj = PyLong_FromLongLong(0);
            if (!output_obj) {
                Py_DECREF(output_dict);
                return NULL;
            }

            if (PyDict_SetItem(output_dict, input_obj, output_obj) < 0) {
                Py_DECREF(output_obj);
                Py_DECREF(output_dict);
                return NULL;
            }
        }
        else {
            long long a = 0, b = 1;
            for (long long j = 2; j <= input; ++j) {
                long long c = a + b;
                a = b;
                b = c;
            }

            PyObject* output_obj = PyLong_FromLongLong(b);
            if (!output_obj) {
                Py_DECREF(output_dict);
                return NULL;
            }

            if (PyDict_SetItem(output_dict, input_obj, output_obj) < 0) {
                Py_DECREF(output_obj);
                Py_DECREF(output_dict);
                return NULL;
            }
        }
    }

    return output_dict;
}


static PyMethodDef FibonacciMethods[] = {
    {"fibonacci", fibonacci, METH_VARARGS, "Calculate Fibonacci numbers."},
    {NULL, NULL, 0, NULL}
};

static struct PyModuleDef fibmodule = {
    PyModuleDef_HEAD_INIT,
    "fibonacci",
    "Fibonacci module",
    -1,
    FibonacciMethods
};

PyMODINIT_FUNC PyInit_fibonacci(void) {
    return PyModule_Create(&fibmodule);
}

