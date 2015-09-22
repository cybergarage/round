/******************************************************************
 *
 * Round for C
 *
 * Copyright (C) Satoshi Konno 2015
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _ROUNDC_CLASS_H_
#define _ROUNDC_CLASS_H_

#include <round/typedef.h>
#include <round/error.h>
#include <round/util/json.h>

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

#if !defined(_ROUNDC_NODE_INTERNAL_H_)
typedef void RoundNode;
#endif
  
/****************************************
 * Function (Node)
 ****************************************/

RoundNode *round_node_new(void);
bool round_node_delete(RoundNode *node);
RoundNode *round_node_next(RoundNode *node);

bool round_node_getaddress(RoundNode *node, const char **addr, RoundError *err);
bool round_node_getport(RoundNode *node, int *port, RoundError *err);
bool round_node_getcluster(RoundNode *node, const char **cluster, RoundError *err);
  
bool round_node_postmessage(RoundJSONObject *reqObj, RoundJSONObject *resObj, RoundError *err);
  
#ifdef  __cplusplus
} /* extern C */
#endif

#endif /* _ROUNDC_CLASS_H_ */
