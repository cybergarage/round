/******************************************************************
 *
 * Round for C
 *
 * Copyright (C) Satoshi Konno 2015
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <round/script/js.h>

/****************************************
* round_js_engine_new
****************************************/

RoundJavaScriptEngine *round_js_engine_new()
{
  RoundJavaScriptEngine *engine;
  
  engine = (RoundJavaScriptEngine *)calloc(1, sizeof(RoundJavaScriptEngine));
  if (!engine)
    return NULL;

  if (!round_script_engine_init((RoundScriptEngine *)engine)) {
    round_js_engine_delete(engine);
    return NULL;
  }
  
#if defined(ROUND_SUPPORT_JS_SM)
  if (!round_js_sm_engine_init(engine)) {
    round_js_engine_delete(engine);
    return NULL;
  }
#endif

  round_script_engine_setlanguage(engine, RoundJavaScriptEngineLanguage);
  round_script_engine_setexecutefunc(engine, round_js_engine_run);
  round_script_engine_setdestructor(engine, round_js_engine_delete);

  return engine;
}

/****************************************
 * round_js_engine_delete
 ****************************************/

bool round_js_engine_delete(RoundJavaScriptEngine *engine) {
  if (!engine)
    return false;
  
#if defined(ROUND_SUPPORT_JS_SM)
  round_js_sm_engine_destroy(engine);
#endif

  if (!round_script_engine_destory((RoundScriptEngine *)engine))
    return false;
  
  free(engine);
  
  return true;
}

/****************************************
 * round_js_engine_run
 ****************************************/

bool round_js_engine_run(RoundJavaScriptEngine *engine, RoundMethod *method, const char *param, RoundString *result, RoundError *err)
{
  if (!engine)
    return false;
  
  // TODO : Create source code
  
#if defined(ROUND_SUPPORT_JS_SM)
  return round_js_sm_engine_run(engine, "", 0, result, err);
#endif
  
  return false;
}
