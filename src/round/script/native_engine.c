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
#include <round/util/json.h>

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

bool round_native_engine_run(RoundNativeEngine *engine, RoundMethod *method, const char *param, RoundString *result, RoundError *err) {
  return false;
}

/****************************************
 * round_native_engine_run
 ****************************************/

bool round_native_engine_setmethod(RoundNativeEngine *engine, RoundMethod *method, const char *param, RoundString *result, RoundError *err) {
  RoundJSON *json;
  const char *name, *lang, *code;
/*
bool Round::set_method::exec(LocalNode *node, const NodeRequest *nodeReq, NodeResponse *nodeRes) const {
*/
  json = round_json_new();

  if (round_json_parse(json, param, err)) {
    round_json_delete(json);
    return false;
  }
/*
#define ROUNDC_SYSTEM_METHOD_PARAM_NAME "name"
#define ROUNDC_SYSTEM_METHOD_PARAM_LANGUAGE "language"
#define ROUNDC_SYSTEM_METHOD_PARAM_CODE "code"
#define ROUNDC_SYSTEM_METHOD_PARAM_ENCODE "encode"
#define ROUNDC_SYSTEM_METHOD_PARAM_BASE64 "base64"
*/
  
  if (!round_json_getstringforpath(json, ROUNDC_SYSTEM_METHOD_PARAM_NAME, &name)) {
    round_json_delete(json);
    return false;
  }

  /*
  // Couldn't override static methods
  if (node->isStaticMethod(scriptMethod))
    return false;
  */
  
  if (!round_json_getstringforpath(json, ROUNDC_SYSTEM_METHOD_PARAM_LANGUAGE, &lang)) {
    round_json_delete(json);
    return false;
  }

  if (!round_json_getstringforpath(json, ROUNDC_SYSTEM_METHOD_PARAM_CODE, &code)) {
    round_json_delete(json);
    return false;
  }
  

  /*
  // Encode
  int encodeType = Script::ENCODING_NONE;
  std::string encodeTypeStr;
  if (jsonDict->get(METHOD_ENCODE, &encodeTypeStr)) {
    if (encodeTypeStr.compare(METHOD_ENCODE_BASE64)) {
      encodeType = Script::ENCODING_BASE64;
    }
  }
   
   return node->setScript(scriptMethod, scriptLang, scriptCode, encodeType, &err);
   */
  
  return true;
}
 
