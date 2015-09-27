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
 * round_system_method_removemethod
 ****************************************/

bool round_system_method_removeregistry(RoundLocalNode *node, RoundJSONObject *params, RoundJSONObject **result, RoundError *err)
{
  const char *key;
  
  if (!round_json_object_ismap(params)) {
    round_error_setjsonrpcerrorcode(err, ROUNDC_RPC_ERROR_CODE_INVALID_PARAMS);
    return false;
  }
  
  if (!round_json_map_getstring(params, ROUNDC_SYSTEM_METHOD_PARAM_KEY, &key)) {
    round_error_setjsonrpcerrorcode(err, ROUNDC_RPC_ERROR_CODE_INVALID_PARAMS);
    return false;
  }
  
  if (!round_local_node_removeregistry(node, key)) {
    round_error_setjsonrpcerrorcode(err, ROUNDC_RPC_ERROR_CODE_INTERNAL_ERROR);
    return false;
  }
  
  return true;
}
