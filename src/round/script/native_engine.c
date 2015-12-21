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

/****************************************
* round_native_engine_new
****************************************/

RoundNativeEngine* round_native_engine_new()
{
  RoundNativeEngine* engine;

  engine = (RoundNativeEngine*)calloc(1, sizeof(RoundNativeEngine));
  if (!engine)
    return NULL;

  if (!round_script_engine_init((RoundScriptEngine*)engine)) {
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

bool round_native_engine_destory(RoundNativeEngine* engine)
{
  if (!engine)
    return false;

  return true;
}

/****************************************
 * round_native_engine_delete
 ****************************************/

bool round_native_engine_delete(RoundNativeEngine* engine)
{
  if (!engine)
    return false;

  if (!round_native_engine_destory(engine))
    return false;

  if (!round_script_engine_destory((RoundScriptEngine*)engine))
    return false;

  free(engine);

  return true;
}

/****************************************
 * round_native_engine_run
 ****************************************/

bool round_native_engine_run(RoundNativeEngine* engine, RoundMethod* method, const char* params, RoundJSONObject** result, RoundError* err)
{
  RoundLocalNode* node;
  ROUND_SCRIPT_NATIVE_ENGINE_FUNC nativeFunc;
  RoundJSON* json;
  RoundJSONObject* jsonParams;
  bool isExecuted;

  node = round_script_engine_getlocalnode(engine);
  if (!node) {
    round_error_setjsonrpcerrorcode(err, ROUND_RPC_ERROR_CODE_INTERNAL_ERROR);
    return false;
  }

  nativeFunc = (ROUND_SCRIPT_NATIVE_ENGINE_FUNC)round_method_getuserdata(method);
  if (!nativeFunc) {
    round_error_setjsonrpcerrorcode(err, ROUND_RPC_ERROR_CODE_METHOD_NOT_FOUND);
    return false;
  }

  json = round_json_new();
  if (!json) {
    round_error_setjsonrpcerrorcode(err, ROUND_RPC_ERROR_CODE_INTERNAL_ERROR);
    return false;
  }

  if (!round_json_parse(json, params, err)) {
    round_error_setjsonrpcerrorcode(err, ROUND_RPC_ERROR_CODE_INVALID_PARAMS);
    round_json_delete(json);
    return false;
  }

  jsonParams = round_json_getrootobject(json);
  if (!jsonParams) {
    round_error_setjsonrpcerrorcode(err, ROUND_RPC_ERROR_CODE_INVALID_PARAMS);
    round_json_delete(json);
    return false;
  }

  isExecuted = nativeFunc(node, jsonParams, result, err);

  round_json_delete(json);

  return isExecuted;
}
