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

#define ROUND_PYTHON_MODULE_NAME "round"

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
  Py_InitModule3(ROUND_PRODUCT_NAME, round_python_getsystemmethods(), ROUND_PRODUCT_NAME);
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

  PyObject* pSource = Py_CompileString(source, ROUND_PYTHON_MODULE_NAME, Py_single_input);
  if (!pSource)
    return false;

  PyObject* pModule = PyImport_ExecCodeModule(ROUND_PYTHON_MODULE_NAME, pSource);
  Py_DECREF(pSource);
  if (!pModule)
    return false;

  const char* name = round_method_getname(method);
  PyObject* pFunc = PyObject_GetAttrString(pModule, name);
  if (!pFunc || !PyCallable_Check(pFunc)) {
    Py_DECREF(pModule);
    return false;
  }

  PyObject* pArgs = PyTuple_New(1);
  if (!pArgs) {
    Py_DECREF(pModule);
    return false;
  }

  PyObject* pParam = PyString_FromString(param ? param : "");
  if (!pParam) {
    Py_DECREF(pModule);
    Py_DECREF(pArgs);
    return false;
  }
  PyTuple_SetItem(pArgs, 0, pParam);

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
    PyObject *ptype, *pvalue, *ptraceback;
    PyErr_Fetch(&ptype, &pvalue, &ptraceback);
    round_error_setmessage(err, PyString_AsString(pvalue));
  }

  Py_DECREF(pFunc);
  Py_DECREF(pModule);

  return true;
}

#endif
