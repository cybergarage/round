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
#include <round/cluster_internal.h>
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
 * round_python_getnodestate
 ****************************************/

PyObject* round_python_getnodeobject(RoundNode* node)
{
  if (!node)
    return NULL;
  
  PyObject* obj = PyDict_New();
  if (!obj)
    return NULL;
  
  const char *addr;
  if (round_node_getaddress(node, &addr)) {
    PyDict_SetItemString(obj, ROUND_SYSTEM_METHOD_PARAM_ADDR, Py_BuildValue("s", addr));
  }
  
  int port;
  if (round_node_getport(node, &port)) {
    PyDict_SetItemString(obj, ROUND_SYSTEM_METHOD_PARAM_PORT, Py_BuildValue("i", port));
  }
  
  const char *id;
  if (round_node_getid(node, &id)) {
    PyDict_SetItemString(obj, ROUND_SYSTEM_METHOD_PARAM_ID,   Py_BuildValue("s", id));
  }
  
  return obj;
}

PyObject* round_python_getnodestate(PyObject* self, PyObject* args)
{
  return round_python_getnodeobject((RoundNode *)round_python_getlocalnode());
}

/****************************************
 * round_python_getclusterstate
 ****************************************/

PyObject* round_python_getclusterobject(RoundCluster *cluster)
{
  if (!cluster)
    return NULL;
  
  PyObject* obj = PyList_New(0);
  if (!obj)
    return NULL;
  
  size_t clusterNodeCnt = 0;
  RoundNode *clusterNode = round_cluster_getnodes(cluster);
  PyObject *clusterNodeObj;
  while (clusterNode) {
    clusterNode = round_cluster_getnodes(cluster);
    clusterNodeObj = round_python_getnodeobject(clusterNode);
    if (PyList_Insert(obj, clusterNodeCnt, clusterNodeObj) == 0)
      clusterNodeCnt++;
    clusterNode = round_node_next(clusterNode);
  }
  
  return obj;
}

PyObject* round_python_getclusterstate(PyObject* self, PyObject* args)
{
  RoundLocalNode* node = round_python_getlocalnode();
  if (!node)
    return NULL;
  
  return round_python_getclusterobject(round_local_node_getcluster(node));
}

/****************************************
 * round_python_getnetworkstate
 ****************************************/

PyObject* round_python_getnetworkstate(PyObject* self, PyObject* args)
{
  RoundLocalNode* node = round_python_getlocalnode();
  if (!node)
    return NULL;

  PyObject* obj = PyDict_New();
  if (!obj)
    return NULL;
  
  RoundCluster *cluster = round_local_node_getclusters(node);
  while (cluster) {
    PyObject *clusterObj = round_python_getclusterobject(cluster);
    const char *clusterName = round_cluster_getname(cluster);
    PyDict_SetItemString(obj, clusterName, clusterObj);
    
    cluster = round_cluster_next(cluster);
  }

  return obj;
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
  if (!node)
    return NULL;

  bool isSuccess = round_local_node_setregistry(node, key, val);

  return Py_BuildValue("i", isSuccess);
}

/****************************************
 * round_python_getregistry
 ****************************************/

PyObject* round_python_getregistry(PyObject* self, PyObject* args)
{
  const char* key, *val;

  if (!PyArg_ParseTuple(args, "s", &key))
    return NULL;

  RoundLocalNode* node = round_python_getlocalnode();
  if (!node)
    return NULL;

  RoundRegistry* reg = round_local_node_getregistry(node, key);
  if (!round_registry_getstring(reg, &val)) {
    reg = NULL;
  }
  
  return Py_BuildValue("s", (reg ? val : ""));
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
  if (!node)
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
  if (!node)
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

/****************************************
 * Python Modules
 ****************************************/

static PyMethodDef gRoundPythonMethods[] = {
  {ROUND_SYSTEM_METHOD_POST_METHOD, round_python_postmethod, METH_VARARGS, ""},
  {ROUND_SYSTEM_METHOD_SET_REGISTRY, round_python_setregistry, METH_VARARGS, ""},
  {ROUND_SYSTEM_METHOD_GET_REGISTRY, round_python_getregistry, METH_VARARGS, ""},
  {ROUND_SYSTEM_METHOD_REMOVE_REGISTRY, round_python_removeregistry, METH_VARARGS, ""},
  {ROUND_SYSTEM_METHOD_GET_NETWORK_STATE, round_python_getnetworkstate, METH_VARARGS, ""},
  {ROUND_SYSTEM_METHOD_GET_CLUSTER_STATE, round_python_getclusterstate, METH_VARARGS, ""},
  {ROUND_SYSTEM_METHOD_GET_NODE_STATE, round_python_getnodestate, METH_VARARGS, ""},
  {NULL, NULL, 0, NULL}
};


PyMethodDef *round_python_getsystemmethods() {
  return gRoundPythonMethods;
}

#if PY_MAJOR_VERSION >= 3
static struct PyModuleDef gRoundPythonModule = {
  PyModuleDef_HEAD_INIT,
  ROUND_PRODUCT_NAME,  /* m_name */
  ROUND_PRODUCT_NAME,  /* m_doc */
  -1,                  /* m_size */
  gRoundPythonMethods, /* m_methods */
  NULL,                /* m_reload */
  NULL,                /* m_traverse */
  NULL,                /* m_clear */
  NULL,                /* m_free */
};

PyModuleDef *round_python_getsystemmodule() {
  return &gRoundPythonModule;
}
#endif

#endif
