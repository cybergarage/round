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
#endif
  
/****************************************
 * Function (Node)
 ****************************************/

RoundNode *round_node_local_new(void);
RoundNode *round_node_remote_new(void);

bool round_node_delete(RoundNode *node);
RoundNode *round_node_next(RoundNode *node);

bool round_node_getaddress(RoundNode *node, const char **addr);
bool round_node_getport(RoundNode *node, int *port);

bool round_node_setclustername(RoundNode *node, const char *cluster);
bool round_node_getclustername(RoundNode *node, const char **cluster);
  
bool round_node_setrequesttimeout(RoundNode *node, time_t value);
time_t round_node_getrequesttimeout(RoundNode *node);

bool round_node_postmessage(RoundNode *node, RoundJSONObject *reqObj, RoundJSONObject *resultObj, RoundError *err);
  
#ifdef  __cplusplus
} /* extern C */
#endif

#endif /* _ROUND_CLASS_H_ */

