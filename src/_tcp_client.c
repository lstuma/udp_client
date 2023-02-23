#include <Python.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

// Function declarations

int connect(char* address, int port);
int sends(int sock, char* msg);
char* receives(int sock);

// Python functions

static PyObject* _send(PyObject* self, PyObject* args)
{
  return PyUnicode_FromString("NOT IMPLEMENTED");
}

static PyObject* _receive(PyObject* self, PyObject* args)
{
  return PyUnicode_FromString("NOT IMPLEMENTED");
}

static PyObject* _connect(PyObject* self, PyObject* args)
{
  PyObject* _address; PyObject* _port;

  if(args == NULL) return NULL;

  // Parse argumentss
  if(!PyArg_ParseTuple(args, "si", &_address, &_port)) return NULL;

  // port
  port = PyLong_AsLong(_port);

  // check if argument is even a string
  if(!PyString_Check(_address)) return NULL;

  // address
  char* address = NULL;

  // get the address
  address = PyString_AsString(_address);

  // connect
  sock = connect(address, port);

  // return the socket
  return PyLong_fromLong(sock);
}

// Method definition
static struct PyMethodDef methods[] = {
    {"connect", (PyCFunction)_connect, METH_VARARGS},
    {"send", (PyCFunction)_send, METH_VARARGS},
    {"receive", (PyCFunction)_receive, METH_VARARGS},
    {NULL, NULL, NULL}
};

// Module definition
static struct PyModuleDef module = {
    PyModuleDef_HEAD_INIT,
    "tcp_client",
    NULL,
    -1,
    methods
};

// Initialize module
PyMODINIT_FUNC PyInit_tcp_client(void) {
  init();
  return PyModule_Create(&module);
}