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

static RoundJavaScriptEngine* gCurrentJsEngine;

static JSFunctionSpec JS_SM_FUNCTIONS[] = {
  JS_FN(ROUND_SCRIPT_PRINT_METHOD, round_js_sm_print, 0, 0),
  //JS_FN(ROUND_SYSTEM_METHOD_GET_NETWORK_STATE, round_js_sm_getnetworkstate, 0, 0),
  //JS_FN(ROUND_SYSTEM_METHOD_GET_CLUSTER_STATE, round_js_sm_getclusterstate, 0, 0),
  //JS_FN(ROUND_SYSTEM_METHOD_GET_NODE_STATE, round_js_sm_getnodestate, 0, 0),
  //JS_FN(ROUND_SCRIPT_POST_METHOD, round_js_sm_postmethod, 0, 0),
  JS_FN(ROUND_SYSTEM_METHOD_SET_REGISTRY, round_js_sm_setregistry, 0, 0),
  JS_FN(ROUND_SYSTEM_METHOD_GET_REGISTRY, round_js_sm_getregistry, 0, 0),
  JS_FN(ROUND_SYSTEM_METHOD_REMOVE_REGISTRY, round_js_sm_removeregistry, 0, 0),
  JS_FS_END
};

static void RoundJSReportError(JSContext* cx, const char* message, JSErrorReport* report)
{
  static char errmsg[1024];

  snprintf(errmsg, sizeof(errmsg), "%s:%u:%s", report->filename ? report->filename : "<no filename>", (unsigned int)report->lineno, message);

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

bool round_js_sm_engine_init(RoundJavaScriptEngine* engine)
{
  if (!engine)
    return NULL;

  JS_SetCStringsAreUTF8();

  engine->cx = NULL;
  engine->rt = NULL;
  engine->obj = NULL;

  engine->rt = JS_NewRuntime(8L * 1024L * 1024L);
  if (!engine->rt)
    return false;

  engine->cx = JS_NewContext(engine->rt, 8192);
  if (!engine->cx)
    return false;

  JS_SetErrorReporter(engine->cx, RoundJSReportError);

  // Obsolete since JSAPI 16
  engine->obj = JS_NewCompartmentAndGlobalObject(engine->cx, &RoundJSGlobalClass, NULL);
  if (!engine->obj)
    return false;

  JS_InitStandardClasses(engine->cx, engine->obj);
  JS_DefineFunctions(engine->cx, engine->obj, JS_SM_FUNCTIONS);

  return true;
}

/****************************************
 * round_js_engine_delete
 ****************************************/

bool round_js_sm_engine_destroy(RoundJavaScriptEngine* engine)
{
  if (!engine)
    return false;

  if (engine->cx) {
    JS_DestroyContext(engine->cx);
  }

  if (engine->rt) {
    JS_DestroyRuntime(engine->rt);
  }

  JS_ShutDown();

  return true;
}

/****************************************
 * round_js_sm_engine_setfunctions
 ****************************************/

bool round_js_sm_engine_setfunctions(RoundJavaScriptEngine* engine, JSFunctionSpec* funcs)
{
  if (!engine)
    return false;

  JS_DefineFunctions(engine->cx, engine->obj, funcs);

  return true;
}

/****************************************
 * round_js_sm_engine_setfunction
 ****************************************/

bool round_js_sm_engine_setfunction(RoundJavaScriptEngine* engine, const char* name, JSNative func)
{
  if (!engine)
    return false;

  JSFunctionSpec funcs[] = {
    JS_FN(name, func, 0, 0),
    JS_FS_END
  };

  round_js_sm_engine_setfunctions(engine, funcs);

  return true;
}

/****************************************
 * round_js_engine_run
 ****************************************/

bool round_js_sm_engine_run(RoundJavaScriptEngine* engine, const char* source, size_t sourceLen, RoundString* result, RoundError* err)
{
  if (!engine)
    return false;

  if (!engine->rt || !engine->cx)
    return false;

  gCurrentJsEngine = engine;

  jsval rval;
  JSBool ok = JS_EvaluateScript(engine->cx, engine->obj, source, (uintN)sourceLen, "", 0, &rval);
  gCurrentJsEngine = NULL;

  if (ok) {
    JSString* rstr = JS_ValueToString(engine->cx, rval);
    if (rstr) {
      if (result) {
        round_string_setvalue(result, JS_EncodeString(engine->cx, rstr));
      }
    }
  }

  return ok;
}

#endif
