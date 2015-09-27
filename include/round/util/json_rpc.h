/******************************************************************
 *
 * Round for C
 *
 * Copyright (C) Satoshi Konno 2015
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _ROUNDC_JSON_RPC_H_
#define _ROUNDC_JSON_RPC_H_

#include <round/util/json.h>

#ifdef  __cplusplus
extern "C" {
#endif

/****************************************
 * Function
 ****************************************/

#define round_json_rpc_setversion(obj, value) round_json_map_setstring(obj, ROUNDC_JSON_RPC_VERSION, value)
#define round_json_rpc_setmethod(obj, value) round_json_map_setstring(obj, ROUNDC_JSON_RPC_METHOD, value)
#define round_json_rpc_setid(obj, value) round_json_map_setstring(obj, ROUNDC_JSON_RPC_ID, value)
#define round_json_rpc_setparams(obj, value) round_json_map_setstring(obj, ROUNDC_JSON_RPC_PARAMS, value)
#define round_json_rpc_settimestamp(obj, value) round_json_map_setinteger(obj, ROUNDC_JSON_RPC_TS, value)

#define round_json_rpc_getversion(obj, value) round_json_map_getstring(obj, ROUNDC_JSON_RPC_VERSION, value)
#define round_json_rpc_getmethod(obj, value) round_json_map_getstring(obj, ROUNDC_JSON_RPC_METHOD, value)
#define round_json_rpc_getid(obj, value) round_json_map_getstring(obj, ROUNDC_JSON_RPC_ID, value)
#define round_json_rpc_getparams(obj, value) round_json_map_getstring(obj, ROUNDC_JSON_RPC_PARAMS, value)
#define round_json_rpc_gettimestamp(obj, value) round_json_map_getinteger(obj, ROUNDC_JSON_RPC_TS, value)

#ifdef  __cplusplus
} /* extern "C" */
#endif

#endif
