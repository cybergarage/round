/******************************************************************
 *
 * Round for C
 *
 * Copyright (C) Satoshi Konno 2015
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _ROUND_JSON_RPC_H_
#define _ROUND_JSON_RPC_H_

#include <round/const.h>
#include <round/error.h>
#include <round/util/json.h>

#ifdef  __cplusplus
extern "C" {
#endif

/****************************************
 * Function
 ****************************************/

RoundJSONObject *round_json_rpc_object_new();

#define round_json_rpc_request_new() round_json_rpc_object_new()
#define round_json_rpc_response_new() round_json_rpc_object_new()

#define round_json_rpc_setversion(obj, value) round_json_map_setstring(obj, ROUND_JSON_RPC_JSONRPC, value)
#define round_json_rpc_setmethod(obj, value) round_json_map_setstring(obj, ROUND_JSON_RPC_METHOD, value)
#define round_json_rpc_setid(obj, value) round_json_map_setstring(obj, ROUND_JSON_RPC_ID, value)
#define round_json_rpc_setparams(obj, value) round_json_map_setstring(obj, ROUND_JSON_RPC_PARAMS, value)
#define round_json_rpc_setresult(obj, value) round_json_map_setreplicaobject(obj, ROUND_JSON_RPC_RESULT, value)

bool round_json_rpc_settimestamp(RoundJSONObject* obj, long ts);

bool round_json_rpc_seterror(RoundJSONObject *obj, RoundError *err);
RoundJSONObject *round_json_rpc_error2response(RoundError* err);

bool round_json_rpc_setrequestid(RoundJSONObject *resObj, RoundJSONObject *reqObj);
  
#define round_json_rpc_getversion(obj, value) round_json_map_getstring(obj, ROUND_JSON_RPC_JSONRPC, value)
#define round_json_rpc_getmethod(obj, value) round_json_map_getstring(obj, ROUND_JSON_RPC_METHOD, value)
#define round_json_rpc_getid(obj, value) round_json_map_getstring(obj, ROUND_JSON_RPC_ID, value)
#define round_json_rpc_getparams(obj, value) round_json_map_getstring(obj, ROUND_JSON_RPC_PARAMS, value)
#define round_json_rpc_getresult(obj, value) round_json_map_getstring(obj, ROUND_JSON_RPC_RESULT, value)
#define round_json_rpc_geterror(obj, value) round_json_map_getobject(obj, ROUND_JSON_RPC_ERROR, value)
#define round_json_rpc_gettimestamp(obj, value) round_json_map_getinteger(obj, ROUND_JSON_RPC_TS, value)

#ifdef  __cplusplus
} /* extern "C" */
#endif

#endif
