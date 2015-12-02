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

RoundJavaScriptEngine* round_js_engine_new()
{
  RoundJavaScriptEngine* engine;

  engine = (RoundJavaScriptEngine*)calloc(1, sizeof(RoundJavaScriptEngine));
  if (!engine)
    return NULL;

  if (!round_script_engine_init((RoundScriptEngine*)engine)) {
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
  round_oo_setdescendantdestoroyfunc(engine, round_js_engine_destroy);

  return engine;
}

/****************************************
 * round_js_engine_destroy
 ****************************************/

bool round_js_engine_destroy(RoundJavaScriptEngine* engine)
{
  if (!engine)
    return false;

#if defined(ROUND_SUPPORT_JS_SM)
  round_js_sm_engine_destroy(engine);
#endif

  return true;
}

/****************************************
 * round_js_engine_delete
 ****************************************/

bool round_js_engine_delete(RoundJavaScriptEngine* engine)
{
  if (!engine)
    return false;

  if (!round_js_engine_destroy(engine))
    return false;

  if (!round_script_engine_destory((RoundScriptEngine*)engine))
    return false;

  free(engine);

  return true;
}

/****************************************
 * round_js_engine_run
 ****************************************/

bool round_js_engine_getsoucecode(RoundJavaScriptEngine* engine,
                                  RoundMethod* method, const char* param,
                                  RoundString* jsSource)
{
  if (!method || !jsSource)
    return false;

  round_string_addvalue(jsSource, round_method_getstringcode(method));
  round_string_addvalue(jsSource, ROUND_ENDL);

  char* jsonParams = round_strreplace(param, "\"", "\\\"");
  round_string_addvalue(jsSource, "var jsonParams = \"");
  round_string_addvalue(jsSource, jsonParams ? jsonParams : "\"\"");
  round_string_addvalue(jsSource, "\";" ROUND_ENDL);
  free(jsonParams);

  round_string_addvalue(jsSource, "var params = jsonParams;" ROUND_ENDL);
  round_string_addvalue(jsSource, "if (0 < jsonParams.length) {" ROUND_ENDL);
  round_string_addvalue(jsSource, "  try {" ROUND_ENDL);
  round_string_addvalue(jsSource,
                        "    params = JSON.parse(jsonParams);" ROUND_ENDL);
  round_string_addvalue(jsSource, "  } catch (e) {" ROUND_ENDL);
  round_string_addvalue(jsSource, "    params = jsonParams;" ROUND_ENDL);
  round_string_addvalue(jsSource, "  }" ROUND_ENDL);
  round_string_addvalue(jsSource, "}" ROUND_ENDL);

  round_string_addvalue(jsSource, "var results = ");
  round_string_addvalue(jsSource, round_method_getname(method));
  round_string_addvalue(jsSource, "(params);" ROUND_ENDL);

  round_string_addvalue(
      jsSource, "var jsonResults = JSON.stringify(results);" ROUND_ENDL);
  round_string_addvalue(jsSource, "jsonResults;");

  return true;
}

/****************************************
 * round_js_engine_run
 ****************************************/

bool round_js_engine_run(RoundJavaScriptEngine* engine, RoundMethod* method,
                         const char* param, RoundJSONObject** jsonResult,
                         RoundError* err)
{
  RoundString *jsSource, *strResult;
  RoundJSON* json;
  bool isSuccess;

  if (!engine)
    return false;

  jsSource = round_string_new();
  strResult = round_string_new();

  if (round_js_engine_getsoucecode(engine, method, param, jsSource)) {
#if defined(ROUND_SUPPORT_JS_SM)
    isSuccess = round_js_sm_engine_run(engine, round_string_getvalue(jsSource),
                                       round_string_length(jsSource), strResult, err);
#endif
  }

  *jsonResult = NULL;
  if (isSuccess) {
    json = round_json_new();
    if (json) {
      isSuccess = round_json_parse(json, round_string_getvalue(strResult), err);
      if (isSuccess) {
        *jsonResult = round_json_poprootobject(json);
      }
      round_json_delete(json);
    }

    if (!(*jsonResult)) {
      if (0 < round_string_length(strResult)) {
        isSuccess = true;
        *jsonResult = round_json_string_new(round_string_getvalue(strResult));
      }
    }
  }

  if (jsSource) {
    round_string_delete(jsSource);
  }

  if (strResult) {
    round_string_delete(strResult);
  }

  return isSuccess;
}
