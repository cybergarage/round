/******************************************************************
 *
 * Round for C
 *
 * Copyright (C) Satoshi Konno 2015
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <stdlib.h>
#include <round/script/python.h>

#if defined(ROUND_SUPPORT_PYTHON)

/****************************************
* round_python_engine_new
****************************************/

RoundPythonEngine* round_python_engine_new()
{
  RoundPythonEngine* engine;

  engine = (RoundPythonEngine*)calloc(1, sizeof(RoundPythonEngine));
  if (!engine)
    return NULL;

  if (!round_python_engine_init(engine)) {
    round_python_engine_delete(engine);
    return NULL;
  }

  return engine;
}

/****************************************
 * round_python_engine_init
 ****************************************/

bool round_python_engine_init(RoundPythonEngine* engine)
{
  if (!engine)
    return false;

  if (!round_script_engine_init((RoundScriptEngine*)engine))
    return false;

  round_script_engine_setlanguage(engine, RoundPythonEngineLanguage);
  round_script_engine_setexecutefunc(engine, round_python_engine_run);
  round_oo_setdescendantdestoroyfunc(engine, round_python_engine_destory);

  Py_Initialize();

#if PY_MAJOR_VERSION >= 3
  PyModule_Create(round_python_getsystemmodule());
#else
  Py_InitModule(ROUND_PRODUCT_NAME, round_python_getsystemmethods());
#endif

  return true;
}

/****************************************
 * round_python_engine_destory
 ****************************************/

bool round_python_engine_destory(RoundPythonEngine* engine)
{
  if (!engine)
    return false;

  Py_Finalize();

  return true;
}

/****************************************
 * round_python_engine_delete
 ****************************************/

bool round_python_engine_delete(RoundPythonEngine* engine)
{
  if (!engine)
    return false;

  if (!round_python_engine_destory(engine))
    return false;

  if (!round_script_engine_destory((RoundScriptEngine*)engine))
    return false;

  free(engine);

  return true;
}

/****************************************
 * round_python_engine_fetcherrormessage
 ****************************************/

bool round_python_engine_fetcherrormessage(RoundPythonEngine* engine, RoundError* err)
{
  PyObject *ptype, *pvalue, *ptraceback;
  PyErr_Fetch(&ptype, &pvalue, &ptraceback);
  round_error_setmessage(err, PyString_AsString(pvalue));
  return true;
}

/****************************************
 * round_python_engine_compile
 ****************************************/

bool round_python_engine_compile(RoundPythonEngine* engine, const char *name, const char *source, RoundError* err, PyObject** pModule)
{
  char moduleName[64];
  snprintf(moduleName, sizeof(moduleName), "%s-%s", ROUND_PYTHON_MODULE_NAME, name);
  
  PyObject *pSource = Py_CompileString(source, moduleName, Py_file_input);
  if (!pSource) {
    round_error_setcode(err, ROUND_RPC_ERROR_CODE_INVALID_REQUEST);
    round_python_engine_fetcherrormessage(engine, err);
    return false;
  }

  *pModule = PyImport_ExecCodeModule((char *)moduleName, pSource);
  Py_DECREF(pSource);
  if (!(*pModule)) {
    round_error_setcode(err, ROUND_RPC_ERROR_CODE_INVALID_REQUEST);
    round_python_engine_fetcherrormessage(engine, err);
    return false;
  }
  return true;
}

/****************************************
 * round_python_engine_getfunctionbyname
 ****************************************/

bool round_python_engine_getfunctionbyname(RoundPythonEngine* engine, PyObject* pModule, const char* funcName, RoundError* err, PyObject** pFunc)
{
  *pFunc = PyObject_GetAttrString(pModule, funcName);
  if (!(*pFunc) || !PyCallable_Check(*pFunc)) {
    round_error_setcode(err, ROUND_RPC_ERROR_CODE_INVALID_REQUEST);
    round_python_engine_fetcherrormessage(engine, err);
    return false;
  }
  return true;
}

/****************************************
 * round_python_engine_run
 ****************************************/

bool round_python_engine_run(RoundPythonEngine* engine, RoundMethod* method, const char* param, RoundString* result, RoundError* err)
{
  if (!engine)
    return false;

  // See :
  // 5. Embedding Python in Another Application¶
  // https://docs.python.org/2.7/extending/embedding.html#embedding-python-in-another-application

  const char* source = round_method_getstringcode(method);
  if (!source)
    return false;

  const char* name = round_method_getname(method);
  if (!name)
    return false;
  
  PyObject* pModule;
  if (!round_python_engine_compile(engine, name, source, err, &pModule))
    return false;

  PyObject* pFunc;
  if (!round_python_engine_getfunctionbyname(engine, pModule, name, err, &pFunc)) {
    Py_DECREF(pModule);
    return false;
  }

  PyObject* pArgs = PyTuple_New(1);
  if (!pArgs) {
    Py_DECREF(pFunc);

    Py_DECREF(pModule);
    return false;
  }

  PyObject* pParam = PyString_FromString(param ? param : "");
  if (!pParam) {
    round_error_setcode(err, ROUND_RPC_ERROR_CODE_INVALID_REQUEST);
    round_python_engine_fetcherrormessage(engine, err);
    Py_DECREF(pModule);
    Py_DECREF(pArgs);
    return false;
  }
  PyTuple_SetItem(pArgs, 0, pParam);

  // TODO : Remove the mutex locak
  round_python_engine_lock(engine);
  
  round_python_setlocalnode(round_script_engine_getlocalnode(engine));
  
  PyObject* pValue = PyObject_CallObject(pFunc, pArgs);
  Py_DECREF(pArgs);
  if (pValue != NULL) {
    const char* cStr = PyString_AsString(pValue);
    if (cStr) {
      round_string_setvalue(result, cStr);
    }
    Py_DECREF(pValue);
  }
  else {
    round_error_setcode(err, ROUND_RPC_ERROR_CODE_INVALID_REQUEST);
    round_python_engine_fetcherrormessage(engine, err);
  }

  // TODO : Remove the mutex locak
  round_python_engine_unlock(engine);
  
  Py_DECREF(pFunc);
  Py_DECREF(pModule);

  return true;
}

#endif
