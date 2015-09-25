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

bool round_system_method_removemethod(RoundLocalNode *node, RoundJSONObject *param, RoundJSONObject **result, RoundError *err)
{
  const char *name;
  
  if (!round_json_object_ismap(param)) {
    round_error_setjsonrpcerrorcode(err, ROUNDC_RPC_ERROR_CODE_INVALID_PARAMS);
    return false;
  }
  
  if (!round_json_map_getstring(param, ROUNDC_SYSTEM_METHOD_PARAM_NAME, &name)) {
    round_error_setjsonrpcerrorcode(err, ROUNDC_RPC_ERROR_CODE_INVALID_PARAMS);
    return false;
  }

  if (round_local_node_isfinalmethod(node, name)) {
    round_error_setjsonrpcerrorcode(err, ROUNDC_RPC_ERROR_CODE_INVALID_PARAMS);
    return false;
  }

  if (!round_local_node_removemethod(node, name)) {
    round_error_setjsonrpcerrorcode(err, ROUNDC_RPC_ERROR_CODE_INTERNAL_ERROR);
    return false;
  }

  return true;
}
