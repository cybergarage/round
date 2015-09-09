/******************************************************************
 *
 * Round for C
 *
 * Copyright (C) Satoshi Konno 2015
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _ROUNDC_JAVSCRIPT_ENGINE_H_
#define _ROUNDC_JAVSCRIPT_ENGINE_H_

#include <round/script_internal.h>
#include <round/method_internal.h>

#if defined(ROUND_SUPPORT_JS_SM)
#include <js/jsapi.h>
#endif

#ifdef  __cplusplus
extern "C" {
#endif

typedef struct _RoundJavaScriptEngine {
  RoundMutex *mutex;
  char *lang;
  ROUND_SCRIPT_ENGINE_EXECFUNC execFunc;
  ROUND_SCRIPT_ENGINE_DESTRUCTOR destFunc;

#if defined(ROUND_SUPPORT_JS_SM)
  JSRuntime *rt;
  JSContext *cx;
  JSObject  *obj;
#endif
} RoundJavaScriptEngine;

RoundJavaScriptEngine *round_js_engine_new();
bool round_js_engine_delete(RoundJavaScriptEngine *engine);

bool round_js_engine_lock(RoundJavaScriptEngine *engine);
bool round_js_engine_unlock(RoundJavaScriptEngine *engine);
  
bool round_js_engine_setresult(RoundJavaScriptEngine *engine, const char *value);
const char *round_js_engine_getresult(RoundJavaScriptEngine *engine);

bool round_js_engine_seterror(RoundJavaScriptEngine *engine, const char *value);
const char *round_js_engine_geterror(RoundJavaScriptEngine *engine);

#if defined(ROUND_SUPPORT_JS_SM)
bool round_js_sm_engine_init(RoundJavaScriptEngine *engine);
bool round_js_sm_engine_destroy(RoundJavaScriptEngine *engine);
bool round_js_sm_engine_setfunctions(RoundJavaScriptEngine *engine, JSFunctionSpec *funcs);
  bool round_js_sm_engine_run(RoundJavaScriptEngine *engine, const char *source, size_t sourceLen, RoundString *result, RoundError *err);
#endif

bool round_js_engine_run(RoundJavaScriptEngine *engine, RoundMethod *method, const char *param, RoundString *result, RoundError *err);
  
#ifdef  __cplusplus
}
#endif

#endif