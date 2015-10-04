/******************************************************************
 *
 * Round for C
 *
 * Copyright (C) Satoshi Konno 2015
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _ROUNDC_NODE_INTERNAL_H_
#define _ROUNDC_NODE_INTERNAL_H_

#include <round/typedef.h>
#include <round/util/oo.h>
#include <round/util/list.h>
#include <round/util/json_internal.h>
#include <round/util/strings.h>
#include <round/util/thread.h>
#include <round/server.h>
#include <round/script.h>
#include <round/clock.h>
#include <round/registry.h>
#include <round/message.h>

#include <round/method.h>

#ifdef  __cplusplus
extern "C" {
#endif

/****************************************
 * Data Type
 ****************************************/

#define ROUND_NODE_STRUCT_MEMBERS \
  ROUND_LIST_STRUCT_MEMBERS \
  ROUND_OO_STRUCT_MEMBERS \
  RoundString *addr; \
  int port; \
  RoundString *cluster; \
  RoundClock *clock;

typedef struct {
  ROUND_NODE_STRUCT_MEMBERS
} RoundNode, RoundNodeList;

typedef struct {
  ROUND_NODE_STRUCT_MEMBERS
} RoundRemoteNode;

typedef struct {
  ROUND_NODE_STRUCT_MEMBERS
  
  RoundMethodManager *methodMgr;
  RoundRegistryManager *regMgr;
  RoundMessageManager *msgMgr;
  RoundThreadManager *threadMgr;
  RoundServer *server;
} RoundLocalNode;

/****************************************
 * Public Header
 ****************************************/
  
#include <round/node.h>
  
/****************************************
 * Function (Node)
 ****************************************/

bool round_node_init(RoundNode *node);
bool round_node_destroy(RoundNode *node);

#define round_node_remove(node) round_list_remove((RoundList *)node)

bool round_node_setaddress(RoundNode *node, const char *addr);
bool round_node_setport(RoundNode *node, int port);
bool round_node_setcluster(RoundNode *node, const char *cluster);

#define round_node_setclockvalue(node, value) round_clock_setvalue(node->clock, value)
#define round_node_setremoteclockvalue(node, value) round_clock_setremotevalue(node->clock, value)
#define round_node_incrementclock(node) round_clock_increment(node->clock)
#define round_node_getclockvalue(node) round_clock_getvalue(node->clock)
  
/****************************************
 * Function (LocalNode)
 ****************************************/
  
RoundLocalNode *round_local_node_new(void);

bool round_local_node_init(RoundLocalNode *node);
bool round_local_node_initsystemmethods(RoundLocalNode *node);
bool round_local_node_initscriptengines(RoundLocalNode *node);
bool round_local_node_initthreads(RoundLocalNode *node);

bool round_local_node_destory(RoundLocalNode *node);
bool round_local_node_delete(RoundLocalNode *node);

bool round_local_node_start(RoundLocalNode *node);
bool round_local_node_stop(RoundLocalNode *node);
bool round_local_node_isrunning(RoundLocalNode *node);

bool round_local_node_setmethod(RoundLocalNode *node, RoundMethod *method);
bool round_local_node_removemethod(RoundLocalNode *node, const char *name);
bool round_local_node_isfinalmethod(RoundLocalNode *node, const char *name);

bool round_local_node_addengine(RoundLocalNode *node, RoundScriptEngine *engine);

bool round_local_node_execmethod(RoundLocalNode *node, RoundJSONObject *reqObj, RoundJSONObject *resObj, RoundError *err);
bool round_local_node_execmessage(RoundLocalNode *node, RoundMessage *msg, RoundJSONObject **resObj, RoundError *err);

bool round_local_node_setregistry(RoundLocalNode *node, const char *key, const char *val);
RoundRegistry *round_local_node_getregistry(RoundLocalNode *node, const char *key);
bool round_local_node_removeregistry(RoundLocalNode *node, const char *key);

bool round_local_node_postmessage(RoundLocalNode *node, RoundJSONObject *reqObj, RoundJSONObject **resObj, RoundError *err);

void local_node_message_thread(RoundThread *thread);
  
#define round_local_node_getclockvalue(node) round_clock_getvalue(node->clock)

/****************************************
 * Function (RemoteNode)
 ****************************************/
  
RoundRemoteNode *round_remote_node_new(void);
bool round_remote_node_destory(RoundRemoteNode *node);
bool round_remote_node_delete(RoundRemoteNode *node);

/****************************************
 * Function (Node List)
 ****************************************/
  
RoundNodeList *round_nodelist_new(void);
bool round_nodelist_delete(RoundNodeList *nodes);
  
#define round_nodelist_clear(nodes) round_list_clear((RoundList *)nodes, (ROUND_LIST_DESTRUCTORFUNC)round_node_delete)
#define round_nodelist_size(nodes) round_list_size((RoundList *)nodes)
#define round_nodelist_gets(nodes) (RoundNode *)round_list_next((RoundList *)nodes)
#define round_nodelist_add(nodes,node) round_list_add((RoundList *)nodes, (RoundList *)node)

#ifdef  __cplusplus
} /* extern C */
#endif

#endif /* _ROUNDC_NODE_INTERNAL_H_ */
