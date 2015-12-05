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
 * round_json_rpc_object_new
 ****************************************/

RoundJSONObject *round_json_rpc_object_new()
{
  RoundJSONObject *rpcObj = round_json_map_new();
  if (!rpcObj)
    return NULL;

  round_json_rpc_setversion(rpcObj, ROUND_JSON_RPC_VERSION);
  
  return rpcObj;
}

/****************************************
 * round_json_rpc_seterror
 ****************************************/

bool round_json_rpc_seterror(RoundJSONObject* mapObj, RoundError* err)
{
  if (!round_json_object_ismap(mapObj))
    return false;

  RoundJSONObject* errMap = round_json_map_new();
  if (!errMap)
    return false;

  round_json_map_setinteger(errMap, ROUND_JSON_RPC_CODE, round_error_getdetailcode(err));
  round_json_map_setstring(errMap, ROUND_JSON_RPC_MESSAGE, round_error_getdetailmessage(err));
  
  round_json_map_setobject(mapObj, ROUND_JSON_RPC_ERROR, errMap);

  round_json_object_delete(errMap);

  return false;
}

/****************************************
 * round_json_rpc_error2object
 ****************************************/

RoundJSONObject *round_json_rpc_error2object(RoundError* err)
{
  RoundJSONObject *resObj = round_json_map_new();
  if (!resObj)
    return NULL;
  
  round_json_rpc_seterror(resObj, err);
  
  return resObj;
}

/****************************************
 * round_json_rpc_seterror
 ****************************************/

RoundJSONObject *round_json_rpc_error2response(RoundError* err)
{
  RoundJSONObject *resObj = round_json_rpc_request_new();
  if (!resObj)
    return NULL;
  
  RoundJSONObject *errObj = round_json_rpc_error2object(err);
  if (errObj) {
    round_json_rpc_seterror(resObj, errObj);
  }

  return resObj;
}
