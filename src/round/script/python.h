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

#include <round/script.h>
#include <round/method.h>
#include <round/platform.h>

#ifdef  __cplusplus
extern "C" {
#endif

#if defined(ROUND_SUPPORT_PYTHON)
#include <Python.h>
#endif

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
  
#ifdef  __cplusplus
}
#endif

#endif