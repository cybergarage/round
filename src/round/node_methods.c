/******************************************************************
 *
 * Round for C
 *
 * Copyright (C) Satoshi Konno 2015
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <round/node_internal.h>
#include <round/cluster_internal.h>

/****************************************
 * round_node_setmethod
 ****************************************/

bool round_node_setmethod(RoundNode* node, const char* lang, const char* name, const char* code, RoundEncodeType encType, RoundError* err)
{
  if (!node || !lang || !name || !code)
    return false;

  // Create request

  RoundJSONObject* reqObj = round_json_rpc_request_new();
  if (!reqObj) {
    round_error_setjsonrpcerrorcode(err, ROUND_RPC_ERROR_CODE_INTERNAL_ERROR);
    return false;
  }
  round_json_rpc_setmethod(reqObj, ROUND_SYSTEM_METHOD_SET_METHOD);

  // Set params

  RoundJSONObject* paramsObj = round_json_map_new();
  if (!paramsObj) {
    round_error_setjsonrpcerrorcode(err, ROUND_RPC_ERROR_CODE_INTERNAL_ERROR);
    round_json_object_delete(reqObj);
    return false;
  }
  round_json_map_setstring(paramsObj, ROUND_SYSTEM_METHOD_PARAM_LANGUAGE, lang);
  round_json_map_setstring(paramsObj, ROUND_SYSTEM_METHOD_PARAM_NAME, name);
  round_json_map_setstring(paramsObj, ROUND_SYSTEM_METHOD_PARAM_CODE, code);
  switch (encType) {
  case RoundEncodeBase64:
      round_json_map_setstring(paramsObj, ROUND_SYSTEM_METHOD_PARAM_ENCODE, ROUND_SYSTEM_METHOD_PARAM_BASE64);
      break;
  default:
      break;
  }
  round_json_rpc_setparamsobject(reqObj, paramsObj);

  // Request

  RoundJSONObject* resObj = NULL;
  bool isSuccess = round_node_postmessage(node, reqObj, &resObj, err);

  // Delete objects

  if (resObj) {
    round_json_object_delete(resObj);
  }
  round_json_object_delete(reqObj);

  return isSuccess;
}

/****************************************
 * round_node_removemethod
 ****************************************/

bool round_node_removemethod(RoundNode* node, const char* name, RoundError* err)
{
  if (!node || !name)
    return false;

  // Create request

  RoundJSONObject* reqObj = round_json_rpc_request_new();
  if (!reqObj) {
    round_error_setjsonrpcerrorcode(err, ROUND_RPC_ERROR_CODE_INTERNAL_ERROR);
    return false;
  }
  round_json_rpc_setmethod(reqObj, ROUND_SYSTEM_METHOD_REMOVE_METHOD);

  // Set params

  RoundJSONObject* paramsObj = round_json_map_new();
  if (!paramsObj) {
    round_error_setjsonrpcerrorcode(err, ROUND_RPC_ERROR_CODE_INTERNAL_ERROR);
    round_json_object_delete(reqObj);
    return false;
  }
  round_json_map_setstring(paramsObj, ROUND_SYSTEM_METHOD_PARAM_NAME, name);
  round_json_rpc_setparamsobject(reqObj, paramsObj);

  // Request

  RoundJSONObject* resObj = NULL;
  bool isSuccess = round_node_postmessage(node, reqObj, &resObj, err);

  // Delete objects

  if (resObj) {
    round_json_object_delete(resObj);
  }
  round_json_object_delete(reqObj);

  return isSuccess;
}

/****************************************
 * round_node_setregistry
 ****************************************/

bool round_node_setregistry(RoundNode* node, const char* key, const char* value, RoundError* err)
{
  if (!node || !key || !value)
    return false;

  // Create request

  RoundJSONObject* reqObj = round_json_rpc_request_new();
  if (!reqObj) {
    round_error_setjsonrpcerrorcode(err, ROUND_RPC_ERROR_CODE_INTERNAL_ERROR);
    return false;
  }
  round_json_rpc_setmethod(reqObj, ROUND_SYSTEM_METHOD_SET_REGISTRY);

  // Set params

  RoundJSONObject* paramsObj = round_json_map_new();
  if (!paramsObj) {
    round_error_setjsonrpcerrorcode(err, ROUND_RPC_ERROR_CODE_INTERNAL_ERROR);
    round_json_object_delete(reqObj);
    return false;
  }
  round_json_map_setstring(paramsObj, ROUND_SYSTEM_METHOD_PARAM_KEY, key);
  round_json_map_setstring(paramsObj, ROUND_SYSTEM_METHOD_PARAM_VALUE, value);
  round_json_rpc_setparamsobject(reqObj, paramsObj);

  // Request

  RoundJSONObject* resObj = NULL;
  bool isSuccess = round_node_postmessage(node, reqObj, &resObj, err);

  // Delete objects

  if (resObj) {
    round_json_object_delete(resObj);
  }
  round_json_object_delete(reqObj);

  return isSuccess;
}

/****************************************
 * round_node_getregistry
 ****************************************/

bool round_node_getregistry(RoundNode* node, const char* key, char** value, RoundError* err)
{
  if (!node || !key || !value)
    return false;

  // Create request

  RoundJSONObject* reqObj = round_json_rpc_request_new();
  if (!reqObj) {
    round_error_setjsonrpcerrorcode(err, ROUND_RPC_ERROR_CODE_INTERNAL_ERROR);
    return false;
  }
  round_json_rpc_setmethod(reqObj, ROUND_SYSTEM_METHOD_GET_REGISTRY);

  // Set params

  RoundJSONObject* paramsObj = round_json_map_new();
  if (!paramsObj) {
    round_error_setjsonrpcerrorcode(err, ROUND_RPC_ERROR_CODE_INTERNAL_ERROR);
    round_json_object_delete(reqObj);
    return false;
  }
  round_json_map_setstring(paramsObj, ROUND_SYSTEM_METHOD_PARAM_KEY, key);
  round_json_rpc_setparamsobject(reqObj, paramsObj);

  // Request

  RoundJSONObject* resObj = NULL;
  bool isSuccess = round_node_postmessage(node, reqObj, &resObj, err);

  // Get result

  if (isSuccess) {
    RoundJSONObject* resultObj;
    if (round_json_rpc_getparamsobject(reqObj, &resultObj)) {
      const char* keyValue;
      if (round_json_map_getstring(paramsObj, ROUND_SYSTEM_METHOD_PARAM_KEY, &keyValue)) {
        *value = round_strdup(keyValue);
      }
    }
  }

  // Delete objects

  if (resObj) {
    round_json_object_delete(resObj);
  }
  round_json_object_delete(reqObj);

  return isSuccess;
}

/****************************************
 * round_node_removeregistry
 ****************************************/

bool round_node_removeregistry(RoundNode* node, const char* key, RoundError* err)
{
  if (!node || !key)
    return false;

  // Create request

  RoundJSONObject* reqObj = round_json_rpc_request_new();
  if (!reqObj) {
    round_error_setjsonrpcerrorcode(err, ROUND_RPC_ERROR_CODE_INTERNAL_ERROR);
    return false;
  }
  round_json_rpc_setmethod(reqObj, ROUND_SYSTEM_METHOD_REMOVE_REGISTRY);

  // Set params

  RoundJSONObject* paramsObj = round_json_map_new();
  if (!paramsObj) {
    round_error_setjsonrpcerrorcode(err, ROUND_RPC_ERROR_CODE_INTERNAL_ERROR);
    round_json_object_delete(reqObj);
    return false;
  }
  round_json_map_setstring(paramsObj, ROUND_SYSTEM_METHOD_PARAM_KEY, key);
  round_json_rpc_setparamsobject(reqObj, paramsObj);

  // Request

  RoundJSONObject* resObj = NULL;
  bool isSuccess = round_node_postmessage(node, reqObj, &resObj, err);

  // Delete objects

  if (resObj) {
    round_json_object_delete(resObj);
  }
  round_json_object_delete(reqObj);

  return isSuccess;
}
