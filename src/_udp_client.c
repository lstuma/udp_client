#include <Python.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

// Function declarations

int udpopen();
int udpsend(int sock, char* msg, char* address, short int port);
int udpclose(int sock);
char* udpreceive(int sock, char* msg_out, char* address);

// Python functions

static PyObject* _send(PyObject* self, PyObject* args)
{
  PyObject* _msg; PyObject* _address; PyObject* port; PyObject* sock;

  if(args == NULL) return NULL;

  // Parse argumentss
  if(!PyArg_ParseTuple(args, "U|U|i|i", &_address, &_msg, &port, &sock)) return NULL;

  // check if argument is even a string
  if(!PyUnicode_Check(_msg) || !PyUnicode_Check(_address)) return NULL;

  // message
  char* msg = NULL;

  // address
  char* address = NULL;


  // get the message
  msg = PyUnicode_AsUTF8(_msg);

  // get the address
  address = PyUnicode_AsUTF8(_address);


  udpsend(sock, msg, address, port);

  return PyLong_FromLong(1);
}

static PyObject* _receive(PyObject* self, PyObject* args)
{
  PyObject* _address; PyObject* sock;

  if(args == NULL) return NULL;

  // Parse argumentss
  if(!PyArg_ParseTuple(args, "U|i", &sock)) return NULL;

  // check if argument is even a string
  if(!PyUnicode_Check(_address)) return NULL;

  // address
  char* address = NULL;

  // get the address
  address = PyUnicode_AsUTF8(_address);


  char msg[4096];
  bzero(msg, sizeof(msg));

  udpreceive(sock, msg, address);

  if(msg) return PyUnicode_FromString(msg);
  else return NULL;
}


static PyObject* _close(PyObject* self, PyObject* args)
{
  PyObject* sock;

  if(args == NULL) return NULL;

  // Parse argumentss
  if(!PyArg_ParseTuple(args, "i", &sock)) return NULL;

  return PyBool_FromLong(udpclose(sock));
}

static PyObject* _open(PyObject* self, PyObject* args)
{
  // make socket
  int sock = udpopen();

  // return the socket
  return PyLong_FromLong(sock);
}

// Method definition
static struct PyMethodDef methods[] = {
    {"open", (PyCFunction)_open, METH_VARARGS},
    {"send", (PyCFunction)_send, METH_VARARGS},
    {"receive", (PyCFunction)_receive, METH_VARARGS},
    {"close", (PyCFunction)_close, METH_VARARGS},
    {NULL, NULL, NULL}
};

// Module definition
static struct PyModuleDef module = {
    PyModuleDef_HEAD_INIT,
    "udp_client",
    NULL,
    -1,
    methods
};

// Initialize module
PyMODINIT_FUNC PyInit_udp_client(void) {
  return PyModule_Create(&module);
}