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

RoundJavaScriptEngine *round_js_engine_new() {
  RoundJavaScriptEngine *jsEngine;
  
  jsEngine = (RoundJavaScriptEngine *)calloc(1, sizeof(RoundJavaScriptEngine));
  if (!jsEngine)
    return NULL;

  if (!round_script_engine_init((RoundScriptEngine *)jsEngine)) {
    round_js_engine_delete(jsEngine);
    return NULL;
  }
  
#if defined(ROUND_SUPPORT_JS_SM)
  if (!round_js_sm_engine_init(jsEngine)) {
    round_js_engine_delete(jsEngine);
    return NULL;
  }
#endif
      
  return jsEngine;
}

/****************************************
 * round_js_engine_delete
 ****************************************/

bool round_js_engine_delete(RoundJavaScriptEngine *jsEngine) {
  if (!jsEngine)
    return false;
  
#if defined(ROUND_SUPPORT_JS_SM)
  round_js_sm_engine_destroy(jsEngine);
#endif

  return round_script_engine_delete((RoundScriptEngine *)jsEngine);
}

/****************************************
 * round_js_engine_setresult
 ****************************************/

bool round_js_engine_setresult(RoundJavaScriptEngine *jsEngine, const char *value) {
  return round_script_engine_setresult((RoundScriptEngine *)jsEngine, value);
}

/****************************************
 * round_js_engine_getresult
 ****************************************/

const char *round_js_engine_getresult(RoundJavaScriptEngine *jsEngine) {
  return round_script_engine_getresult((RoundScriptEngine *)jsEngine);
}

/****************************************
 * round_js_engine_seterror
 ****************************************/

bool round_js_engine_seterror(RoundJavaScriptEngine *jsEngine, const char *value) {
  return round_script_engine_seterror((RoundScriptEngine *)jsEngine, value);
}

/****************************************
 * round_js_engine_geterror
 ****************************************/

const char *round_js_engine_geterror(RoundJavaScriptEngine *jsEngine) {
  return round_script_engine_geterror((RoundScriptEngine *)jsEngine);
}

/****************************************
 * round_js_engine_lock
 ****************************************/

bool round_js_engine_lock(RoundJavaScriptEngine *jsEngine) {
  return round_script_engine_lock((RoundScriptEngine *)jsEngine);
}

/****************************************
 * round_js_engine_unlock
 ****************************************/

bool round_js_engine_unlock(RoundJavaScriptEngine *jsEngine) {
  return round_script_engine_unlock((RoundScriptEngine *)jsEngine);
}

/****************************************
 * round_js_engine_run
 ****************************************/

bool round_js_engine_run(RoundJavaScriptEngine *jsEngine, const char *source) {
  if (!jsEngine)
    return false;
  
  if (!round_script_engine_clear((RoundScriptEngine *)jsEngine))
    return false;
  
#if defined(ROUND_SUPPORT_JS_SM)
  return round_js_sm_engine_run(jsEngine, source, round_strlen(source), &jsEngine->result);
#endif
  
  return false;
}
