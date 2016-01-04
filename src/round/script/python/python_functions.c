/******************************************************************
 *
 * Round for C
 *
 * Copyright (C) Satoshi Konno 2015
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <round/node_internal.h>
#include <round/script/python.h>

#if defined(ROUND_SUPPORT_PYTHON)

// FIXME : Update not to use the global variable
static RoundLocalNode* gRoundPythonEngineLocalNode = NULL;

/****************************************
 * round_python_setlocalnode
 ****************************************/

void round_python_setlocalnode(RoundLocalNode* node)
{
  gRoundPythonEngineLocalNode = node;
}

/****************************************
 * round_script_result2json
 ****************************************/

RoundLocalNode* round_python_getlocalnode()
{
  return gRoundPythonEngineLocalNode;
}

/****************************************
 * round_script_result2json
 ****************************************/

bool round_python_haslocalnode()
{
  return (gRoundPythonEngineLocalNode != NULL) ? true : false;
}

/****************************************
 * round_python_getnetworkstate
 ****************************************/

PyObject* round_python_getnetworkstate(PyObject* self, PyObject* args)
{
  return NULL;
}

/****************************************
 * round_python_getclusterstate
 ****************************************/

PyObject* round_python_getclusterstate(PyObject* self, PyObject* args)
{
  return NULL;
}

/****************************************
 * round_python_getnodestate
 ****************************************/

PyObject* round_python_getnodestate(PyObject* self, PyObject* args)
{
  return NULL;
}

/****************************************
 * round_python_setregistry
 ****************************************/

PyObject* round_python_setregistry(PyObject* self, PyObject* args)
{
  return NULL;
}

/****************************************
 * round_python_getregistry
 ****************************************/

PyObject* round_python_getregistry(PyObject* self, PyObject* args)
{
  return NULL;
}

/****************************************
 * round_python_removeregistry
 ****************************************/

PyObject* round_python_removeregistry(PyObject* self, PyObject* args)
{
  return NULL;
}

/****************************************
 * round_python_postmethod
 ****************************************/

PyObject* round_python_postmethod(PyObject* self, PyObject* args)
{
  return NULL;
}

#endif
