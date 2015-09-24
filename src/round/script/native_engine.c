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
  const char *methodName;
  
  methodName = round_method_getname(method);

  return false;
}

/****************************************
 * round_native_script_setmethod
 ****************************************/

bool round_native_script_setmethod(RoundLocalNode *node, RoundMethod *method, const char *param, RoundString *result, RoundError *err)
{
  RoundJSON *json;
  const char *name, *lang;
  byte *code;
  size_t codeLen;
  RoundMethod *newMethod;
  bool isAdded;
  

  json = round_json_new();

  if (round_json_parse(json, param, err)) {
    round_json_delete(json);
    return false;
  }
  
  if (!round_json_getstringforpath(json, ROUNDC_SYSTEM_METHOD_PARAM_NAME, &name)) {
    round_json_delete(json);
    return false;
  }

  if (!round_json_getstringforpath(json, ROUNDC_SYSTEM_METHOD_PARAM_LANGUAGE, &lang)) {
    round_json_delete(json);
    return false;
  }

  if (!round_json_getstringforpath(json, ROUNDC_SYSTEM_METHOD_PARAM_CODE, (const char **)&code)) {
    round_json_delete(json);
    return false;
  }
  
  codeLen = round_strlen((const char *)code);
  
  /* TODO : Support Base64
   #define ROUNDC_SYSTEM_METHOD_PARAM_ENCODE "encode"
   #define ROUNDC_SYSTEM_METHOD_PARAM_BASE64 "base64"
  // Encode
  int encodeType = Script::ENCODING_NONE;
  std::string encodeTypeStr;
  if (jsonDict->get(METHOD_ENCODE, &encodeTypeStr)) {
    if (encodeTypeStr.compare(METHOD_ENCODE_BASE64)) {
      encodeType = Script::ENCODING_BASE64;
    }
  }
   */
  
  newMethod = round_method_new();
  if (!newMethod)
    return false;
  round_method_setname(newMethod, name);
  round_method_setlanguage(newMethod, lang);
  round_method_setcode(newMethod, code, codeLen);
  
  isAdded = round_local_node_setmethod(node, newMethod);
  if (!isAdded) {
    round_method_delete(newMethod);
  }
  
  return isAdded;
}
