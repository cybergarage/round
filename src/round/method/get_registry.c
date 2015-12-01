/******************************************************************
 *
 * Round for C
 *
 * Copyright (C) Satoshi Konno 2015
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <round/method/system_method.h>

/****************************************
 * round_system_method_setmethod
 ****************************************/

bool round_system_method_getregistry(RoundLocalNode *node,
RoundJSONObject *params, RoundJSONObject **resultMap, RoundError *err) {
  const char *key;
  RoundRegistry *reg;

  if (!round_json_object_ismap(params)) {
    round_error_setjsonrpcerrorcode(err, ROUND_RPC_ERROR_CODE_INVALID_PARAMS);
    return false;
  }

  if (!round_json_map_getstring(params, ROUND_SYSTEM_METHOD_PARAM_KEY, &key)) {
    round_error_setjsonrpcerrorcode(err, ROUND_RPC_ERROR_CODE_INVALID_PARAMS);
    return false;
  }

  reg = round_local_node_getregistry(node, key);
  if (!reg) {
    round_error_setjsonrpcerrorcode(err, ROUND_RPC_ERROR_CODE_INVALID_PARAMS);
    return false;
  }

  *resultMap = round_json_map_new();
  if (*resultMap) {
    round_error_setjsonrpcerrorcode(err, ROUND_RPC_ERROR_CODE_INTERNAL_ERROR);
    return false;
  }

  round_json_map_setstring((*resultMap), ROUND_SYSTEM_METHOD_PARAM_KEY, key);
  round_json_map_setstring(
  (*resultMap), ROUND_SYSTEM_METHOD_PARAM_VALUE, round_registry_getvalue(reg));
  round_json_map_setinteger(
  (*resultMap), ROUND_SYSTEM_METHOD_PARAM_TS, round_registry_getts(reg));
  round_json_map_setinteger(
  (*resultMap), ROUND_SYSTEM_METHOD_PARAM_LTS, round_registry_getlts(reg));

  return true;
}
