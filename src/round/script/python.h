/******************************************************************
 *
 * Round for C
 *
 * Copyright (C) Satoshi Konno 2015
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _ROUND_PYTHON_ENGINE_H_
#define _ROUND_PYTHON_ENGINE_H_

#include <round/platform.h>
#include <round/node_internal.h>
#include <round/script_internal.h>
#include <round/method.h>

#ifdef  __cplusplus
extern "C" {
#endif

#if defined(ROUND_SUPPORT_PYTHON)
#if defined(HAVE_PYTHON_PYTHON_H)
#include <Python/Python.h>
#else
#include <Python.h>
#endif
#endif

#define ROUND_PYTHON_MODULE_NAME "round"
#define RoundPythonEngineLanguage "python"
  
typedef struct {
  ROUND_SCRIPT_ENGINE_STRUCT_MEMBERS

#if defined(ROUND_SUPPORT_PYTHON)
#endif
} RoundPythonEngine;

RoundPythonEngine *round_python_engine_new();
bool round_python_engine_init(RoundPythonEngine* engine);
bool round_python_engine_destory(RoundPythonEngine *engine);
bool round_python_engine_delete(RoundPythonEngine *engine);

bool round_python_engine_run(RoundPythonEngine *engine, RoundMethod *method, const char *param, RoundString *result, RoundError *err);

#define round_python_engine_lock(engine) round_script_engine_lock((RoundScriptEngine *)engine)
#define round_python_engine_unlock(engine) round_script_engine_unlock((RoundScriptEngine *)engine)
  
void round_python_setlocalnode(RoundLocalNode* node);
  
#if defined(ROUND_SUPPORT_PYTHON)
PyMethodDef *round_python_getsystemmethods();
bool round_python_engine_compile(RoundPythonEngine* engine, const char *name, const char *source, RoundError* err, PyObject** pModule);
bool round_python_engine_getfunctionbyname(RoundPythonEngine* engine, PyObject* pModule, const char* name, RoundError* err, PyObject** pFunc);
#if PY_MAJOR_VERSION >= 3
PyModuleDef *round_python_getsystemmodule();
#endif
#endif

#ifdef  __cplusplus
}
#endif

#endif
