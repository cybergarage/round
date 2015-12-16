/******************************************************************
 *
 * Round for C
 *
 * Copyright (C) Satoshi Konno 2015
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <round/error_internal.h>
#include <round/util/json_rpc.h>

/****************************************
 * round_json_rpc_object_new
 ****************************************/

RoundJSONObject* round_json_rpc_object_new()
{
  RoundJSONObject* rpcObj = round_json_map_new();
  if (!rpcObj)
    return NULL;

  round_json_rpc_setversion(rpcObj, ROUND_JSON_RPC_VERSION);

  return rpcObj;
}

/****************************************
 * round_json_rpc_setrequestid
 ****************************************/

bool round_json_rpc_setrequestid(RoundJSONObject* resObj, RoundJSONObject* reqObj)
{
  if (!round_json_object_ismap(resObj) || !round_json_object_ismap(reqObj))
    return false;

  const char* reqId;
  if (!round_json_rpc_getid(reqObj, &reqId))
    return false;

  return round_json_rpc_setid(resObj, reqId);
}

/****************************************
 * round_json_rpc_setrequestid
 ****************************************/

bool round_json_rpc_settimestamp(RoundJSONObject* obj, long ts)
{
  if (!round_json_object_ismap(obj)) {
    round_json_map_setinteger(obj, ROUND_JSON_RPC_TS, ts);
    return true;
  }

  if (!round_json_object_isarray(obj)) {
    size_t childObjCnt = round_json_array_size(obj);
    for (size_t n = 0; n < childObjCnt; n++) {
      RoundJSONObject* childObj = round_json_array_get(obj, n);
      if (!round_json_object_ismap(childObj)) {
        round_json_map_setinteger(childObj, ROUND_JSON_RPC_TS, ts);
        return true;
      }
    }
    return true;
  }

  return false;
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

RoundJSONObject* round_json_rpc_error2object(RoundError* err)
{
  RoundJSONObject* resObj = round_json_map_new();
  if (!resObj)
    return NULL;

  round_json_rpc_seterror(resObj, err);

  return resObj;
}

/****************************************
 * round_json_rpc_seterror
 ****************************************/

RoundJSONObject* round_json_rpc_error2response(RoundError* err)
{
  RoundJSONObject* resObj = round_json_rpc_request_new();
  if (!resObj)
    return NULL;

  RoundJSONObject* errObj = round_json_rpc_error2object(err);
  if (errObj) {
    round_json_rpc_seterror(resObj, errObj);
  }
  round_json_delete(errObj);

  return resObj;
}

/****************************************
 * round_error_setjsonrpcerror
 ****************************************/

bool round_error_setjsonrpcerror(RoundError *err, RoundJSONObject *errObj)
{
  if (!err || !errObj)
    return false;
  
  if (!round_json_object_ismap(errObj))
    return false;

  long errCode;
  if (round_json_rpc_geterrorcode(errObj, &errCode)) {
    round_error_setjsonrpcerrorcode(err, (int)errCode);
    round_error_setdetailcode(err, (int)errCode);
  }

  const char *errMsg;
  if (round_json_rpc_geterrormessage(errObj, &errMsg)) {
    round_error_setdetailmessage(err, errMsg);
  }
  
  return true;
}

