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

#include <round/script.h>

#if defined(ROUND_SUPPORT_JS_SM)
#include <js/jsapi.h>
#endif

#ifdef  __cplusplus
extern "C" {
#endif

typedef struct _RoundJavaScriptEngine {
  RoundMutex *mutex;
  char *result;
  char *error;
#if defined(ROUND_SUPPORT_JS_SM)
  JSRuntime *rt;
  JSContext *cx;
  JSObject  *obj;
#endif
} RoundJavaScriptEngine;

RoundJavaScriptEngine *round_js_engine_new();
bool round_js_engine_delete(RoundJavaScriptEngine *jsEngine);

bool round_js_engine_lock(RoundJavaScriptEngine *jsEngine);
bool round_js_engine_unlock(RoundJavaScriptEngine *jsEngine);
  
bool round_js_engine_setresult(RoundJavaScriptEngine *jsEngine, const char *value);
const char *round_js_engine_getresult(RoundJavaScriptEngine *jsEngine);

bool round_js_engine_seterror(RoundJavaScriptEngine *jsEngine, const char *value);
const char *round_js_engine_geterror(RoundJavaScriptEngine *jsEngine);

#if defined(ROUND_SUPPORT_JS_SM)
bool round_js_sm_engine_init(RoundJavaScriptEngine *jsEngine);
bool round_js_sm_engine_destroy(RoundJavaScriptEngine *jsEngine);
bool round_js_sm_engine_setfunctions(RoundJavaScriptEngine *jsEngine, JSFunctionSpec *funcs);
bool round_js_sm_engine_run(RoundJavaScriptEngine *jsEngine, const char *source, size_t sourceLen, char **result);
#endif

bool round_js_engine_run(RoundJavaScriptEngine *jsEngine, const char *source);
  
#ifdef  __cplusplus
}
#endif

#endif