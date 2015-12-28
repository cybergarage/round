/******************************************************************
 *
 * Round for C
 *
 * Copyright (C) Satoshi Konno 2015
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _ROUND_CLASS_H_
#define _ROUND_CLASS_H_

#include <round/typedef.h>
#include <round/error.h>
#include <round/util/json.h>
#include <round/util/json_rpc.h>

#ifdef  __cplusplus
extern "C" {
#endif

/****************************************
 * Constant
 ****************************************/
  
enum {
  RoundNodeCodeMin = 0x0000,
  RoundNodeCodeMax = 0xFFFF,
};

enum {
  RoundNodeGroupDeviceMin = 0x00,
  RoundNodeGroupDeviceMax = 0x06,
  RoundNodeGroupProfile = 0x0E,
};
  
/****************************************
 * Data Type
 ****************************************/

typedef int RoundNodeCode;

#if !defined(_ROUND_NODE_INTERNAL_H_)
typedef void RoundNode;
typedef void RoundLocalNode;
#endif
  
typedef bool (*ROUND_SCRIPT_NATIVE_ENGINE_FUNC)(RoundLocalNode *, RoundJSONObject *, RoundJSONObject **, RoundError *);

/****************************************
 * Function (Node)
 ****************************************/

RoundNode *round_node_next(RoundNode *node);

bool round_node_getaddress(RoundNode *node, const char **addr);
bool round_node_getport(RoundNode *node, int *port);
clock_t round_node_getclock(RoundNode *node);

bool round_node_setclustername(RoundNode *node, const char *cluster);
bool round_node_getclustername(RoundNode *node, const char **cluster);

const char *round_node_getid(RoundNode *node);

bool round_node_setrequesttimeout(RoundNode *node, time_t value);
time_t round_node_getrequesttimeout(RoundNode *node);

bool round_node_postmessage(RoundNode *node, RoundJSONObject *reqObj, RoundJSONObject **resObj, RoundError *err);
bool round_node_poststringmessage(RoundNode *node, const char *reqStr, RoundJSONObject **resObj, RoundError *err);

bool round_node_equals(RoundNode *node1, RoundNode *node2);  

void round_node_setuserdata(RoundNode *node, void *data);
void *round_node_getuserdata(RoundNode *node);

/****************************************
 * Function (RPC)
 ****************************************/

bool round_node_setmethod(RoundNode* node, const char* lang, const char* name, const char* code, RoundError* err);
bool round_node_removemethod(RoundNode* node, const char* name, RoundError* err);

bool round_node_setregistry(RoundNode* node, const char *key, const char *value, RoundError *err);
bool round_node_getregistry(RoundNode* node, const char *key, char **value, RoundError *err);
bool round_node_removeregistry(RoundNode* node, const char *key, RoundError *err);

/****************************************
 * Function (Local)
 ****************************************/

#define round_local_node_setuserdata(node, data) round_node_setuserdata((RoundNode *)node, data)
#define round_local_node_getuserdata(node) round_node_getuserdata((RoundNode *)node)

#define round_local_node_getclustername(node,cluster) round_node_getclustername((RoundNode*)node,cluster)
#define round_local_node_getid(node) round_node_getid((RoundNode*)node)

bool round_local_node_setnativemethod(RoundLocalNode *node, const char *name, ROUND_SCRIPT_NATIVE_ENGINE_FUNC func);

#ifdef  __cplusplus
} /* extern C */
#endif

#endif /* _ROUND_CLASS_H_ */

