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
#include <round/script/native.h>
#include <round/util/json_internal.h>
#include <round/node_internal.h>

#if defined(ROUND_SUPPORT_MRUBY)
#include "mnative/compile.h"
#endif

/****************************************
* round_native_engine_new
****************************************/

RoundNativeEngine *round_native_engine_new()
{
  RoundNativeEngine *engine;
  
  engine = (RoundNativeEngine *)calloc(1, sizeof(RoundNativeEngine));
  if (!engine)
    return NULL;

  if (!round_script_engine_init((RoundScriptEngine *)engine)) {
    round_native_engine_delete(engine);
    return NULL;
  }
 
  round_script_engine_setlanguage(engine, RoundNativeEngineLanguage);
  round_script_engine_setexecutefunc(engine, round_native_engine_run);
  round_oo_setdescendantdestoroyfunc(engine, round_native_engine_destory);
  
  return engine;
}

/****************************************
 * round_native_engine_destory
 ****************************************/

bool round_native_engine_destory(RoundNativeEngine *engine)
{
  if (!engine)
    return false;
  
  return true;
}

/****************************************
 * round_native_engine_delete
 ****************************************/

bool round_native_engine_delete(RoundNativeEngine *engine) {
  if (!engine)
    return false;

  if (!round_native_engine_destory(engine))
    return false;
  
  if (!round_script_engine_destory((RoundScriptEngine *)engine))
    return false;
  
  free(engine);
  
  return true;
}

/****************************************
 * round_native_engine_run
 ****************************************/

bool round_native_engine_run(RoundNativeEngine *engine, RoundMethod *method, const char *param, RoundString *result, RoundError *err)
{
  ROUND_SCRIPT_NATIVE_ENGINE_FUNC nativeFunc;
  
  //nativeFunc = round_method_getnativefunc(method);
  
  nativeFunc(NULL, param, result, err);
  
  return false;
}
