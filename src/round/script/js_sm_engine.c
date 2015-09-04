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

#if defined(ROUND_SUPPORT_JS_SM)

static RoundJavaScriptEngine *gCurrentJsEngine;

static void RoundJSReportError(JSContext *cx, const char *message, JSErrorReport *report)
{
  static char errmsg[1024];

  snprintf(errmsg,
           sizeof(errmsg),
           "%s:%u:%s",
          report->filename ? report->filename : "<no filename>",
          (unsigned int) report->lineno,
          message);

  if (gCurrentJsEngine) {
    round_js_engine_seterror(gCurrentJsEngine, errmsg);
  }
  
  fprintf(stderr, "%s\n", errmsg);
}

static JSClass RoundJSGlobalClass = {
  "global",
  JSCLASS_NEW_RESOLVE | JSCLASS_GLOBAL_FLAGS | JSCLASS_HAS_PRIVATE,
  JS_PropertyStub,
  JS_PropertyStub,
  JS_PropertyStub,
  JS_StrictPropertyStub,
  JS_EnumerateStub,
  JS_ResolveStub,
  JS_ConvertStub,
  JS_FinalizeStub,
  JSCLASS_NO_OPTIONAL_MEMBERS
};

/****************************************
* round_js_sm_engine_new
****************************************/

bool round_js_sm_engine_init(RoundJavaScriptEngine *jsEngine) {
  if (!jsEngine)
    return NULL;

  JS_SetCStringsAreUTF8();
  
  jsEngine->cx = NULL;
  jsEngine->rt = NULL;
  jsEngine->obj = NULL;
  
  jsEngine->rt = JS_NewRuntime(8L * 1024L * 1024L);
  if (!jsEngine->rt)
    return false;
  
  jsEngine->cx = JS_NewContext(jsEngine->rt, 8192);
  if (!jsEngine->cx)
    return false;
  
  JS_SetErrorReporter(jsEngine->cx, RoundJSReportError);
  
  // Obsolete since JSAPI 16
  jsEngine->obj = JS_NewCompartmentAndGlobalObject(jsEngine->cx, &RoundJSGlobalClass, NULL);
  if (!jsEngine->obj)
    return false;
  
  JS_InitStandardClasses(jsEngine->cx, jsEngine->obj);
  
  return true;
}

/****************************************
 * round_js_engine_delete
 ****************************************/

bool round_js_sm_engine_destroy(RoundJavaScriptEngine *jsEngine) {
  if (!jsEngine)
    return false;
  
  if (jsEngine->cx) {
    JS_DestroyContext(jsEngine->cx);
  }
  
  if (jsEngine->rt) {
    JS_DestroyRuntime(jsEngine->rt);
  }
  
  JS_ShutDown();
  
  return true;
}

/****************************************
 * round_js_sm_engine_setfunctions
 ****************************************/

bool round_js_sm_engine_setfunctions(RoundJavaScriptEngine *jsEngine, JSFunctionSpec *funcs) {
  if (!jsEngine)
    return false;

  JS_DefineFunctions(jsEngine->cx, jsEngine->obj, funcs);
  
  return true;
}

/****************************************
 * round_js_engine_run
 ****************************************/

bool round_js_sm_engine_run(RoundJavaScriptEngine *jsEngine, const char *source, size_t sourceLen, char **result) {
  jsval rval;
  JSBool ok;
  
  if (!jsEngine)
    return false;
  
  if (!jsEngine->rt || !jsEngine->cx)
    return false;
  
  gCurrentJsEngine = jsEngine;
  ok = JS_EvaluateScript(jsEngine->cx, jsEngine->obj, source, (uintN)sourceLen, "", 0, &rval);
  gCurrentJsEngine = NULL;
  
  if (ok) {
    JSString *rstr = JS_ValueToString(jsEngine->cx, rval);
    if (rstr) {
      if (result) {
        round_strloc(JS_EncodeString(jsEngine->cx, rstr), result);
      }
    }
  }
  
  return ok;
}

#endif
