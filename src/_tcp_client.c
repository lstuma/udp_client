#include <Python.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

// Function declarations

int tcpconnect(char* address, int port);
int tcpsend(int sock, char* msg);
int tcpclose(int sock);
char* tcpreceive(int sock, char* msg_out);

// Python functions

static PyObject* _send(PyObject* self, PyObject* args)
{
  PyObject* _msg; PyObject* sock;

  if(args == NULL) return NULL;

  // Parse argumentss
  if(!PyArg_ParseTuple(args, "U|i", &_msg, &sock)) return NULL;

  // check if argument is even a string
  if(!PyUnicode_Check(_msg)) return NULL;

  // message
  char* msg = NULL;

  // get the address
  msg = PyUnicode_AsUTF8(_msg);

  tcpsend(sock, msg);

  return PyLong_FromLong(1);
}

static PyObject* _receive(PyObject* self, PyObject* args)
{
  PyObject* sock;

  if(args == NULL) return NULL;

  // Parse argumentss
  if(!PyArg_ParseTuple(args, "i", &sock)) return NULL;

  char msg[1024];
  bzero(msg, sizeof(msg));

  tcpreceive(sock, msg);

  if(msg) return PyUnicode_FromString(msg);
  else return NULL;
}


static PyObject* _close(PyObject* self, PyObject* args)
{
  PyObject* sock;

  if(args == NULL) return NULL;

  // Parse argumentss
  if(!PyArg_ParseTuple(args, "i", &sock)) return NULL;

  return PyBool_FromLong(tcpclose(sock));
}

static PyObject* _connect(PyObject* self, PyObject* args)
{
  PyObject* _address; PyObject* port;

  if(args == NULL) return NULL;

  // Parse argumentss
  if(!PyArg_ParseTuple(args, "U|i", &_address, &port)) return NULL;

  // check if argument is even a string
  if(!PyUnicode_Check(_address)) return NULL;

  // address
  char* address = NULL;

  // get the address
  address = PyUnicode_AsUTF8(_address);
  // connect
  int sock = tcpconnect(address, port);

  // return the socket
  return PyLong_FromLong(sock);
}

// Method definition
static struct PyMethodDef methods[] = {
    {"connect", (PyCFunction)_connect, METH_VARARGS},
    {"send", (PyCFunction)_send, METH_VARARGS},
    {"receive", (PyCFunction)_receive, METH_VARARGS},
    {"close", (PyCFunction)_close, METH_VARARGS},
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
  return PyModule_Create(&module);
}