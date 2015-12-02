/******************************************************************
 *
 * Round for C
 *
 * Copyright (C) Satoshi Konno 2015
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <round/util/json_rpc.h>

/****************************************
 * round_json_rpc_seterror
 ****************************************/

bool round_json_rpc_seterror(RoundJSONObject *obj, RoundError *err) {
  RoundJSONObject *errMap;

  if (!round_json_object_ismap(obj))
    return false;

  errMap = round_json_map_new();
  if (!errMap)
    return false;
  round_json_map_setinteger(errMap, ROUND_JSON_RPC_CODE,
                            round_error_getdetailcode(err));
  round_json_map_setstring(errMap, ROUND_JSON_RPC_MESSAGE,
                           round_error_getdetailmessage(err));
  round_json_map_setobject(obj, ROUND_JSON_RPC_ERROR, errMap);
  round_json_object_delete(errMap);

  return false;
}
