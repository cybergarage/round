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
 * round_python_getlocalnode
 ****************************************/

RoundLocalNode* round_python_getlocalnode()
{
  return gRoundPythonEngineLocalNode;
}

/****************************************
 * round_jsonobject2pythonobject
 ****************************************/

PyObject* round_jsonobject2pythonobject(RoundJSONObject* jsonObj)
{
  if (!jsonObj)
    return NULL;

  PyObject* pyObj = NULL;

  if (round_json_object_isarray(jsonObj)) {
  }

  if (round_json_object_ismap(jsonObj)) {
  }

  return pyObj;
}

/****************************************
 * round_python_haslocalnode
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
  const char *key, *val;

  if (!PyArg_ParseTuple(args, "ss", &key, &val))
    return NULL;

  RoundLocalNode* node = round_python_getlocalnode();
  if (node)
    return NULL;

  bool isSuccess = round_local_node_setregistry(node, key, val);

  return Py_BuildValue("i", isSuccess);
}

/****************************************
 * round_python_getregistry
 ****************************************/

PyObject* round_python_getregistry(PyObject* self, PyObject* args)
{
  const char* key;

  if (!PyArg_ParseTuple(args, "s", &key))
    return NULL;

  RoundLocalNode* node = round_python_getlocalnode();
  if (node)
    return NULL;

  RoundRegistry* reg = round_local_node_getregistry(node, key);

  return Py_BuildValue("s", (reg ? round_registry_getvalue(reg) : ""));
}

/****************************************
 * round_python_removeregistry
 ****************************************/

PyObject* round_python_removeregistry(PyObject* self, PyObject* args)
{
  const char* key;

  if (!PyArg_ParseTuple(args, "s", &key))
    return NULL;

  RoundLocalNode* node = round_python_getlocalnode();
  if (node)
    return NULL;

  bool isSuccess = round_local_node_removeregistry(node, key);

  return Py_BuildValue("i", isSuccess);
}

/****************************************
 * round_python_postmethod
 ****************************************/

PyObject* round_python_postmethod(PyObject* self, PyObject* args)
{
  const char *dest, *method, *params;

  if (!PyArg_ParseTuple(args, "sss", &dest, &method, &params))
    return NULL;

  RoundLocalNode* node = round_python_getlocalnode();
  if (node)
    return NULL;

  RoundError err;
  round_error_init(&err);

  RoundJSONObject* resObj;

  if (!round_local_node_execmethod(node, dest, method, params, &resObj, &err)) {
    round_error_destroy(&err);
    return NULL;
  }

  PyObject* retObj = round_jsonobject2pythonobject(resObj);

  round_error_destroy(&err);

  return retObj;
}

#endif