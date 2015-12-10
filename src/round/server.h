/******************************************************************
 *
 * Round for C
 *
 * Copyright (C) Satoshi Konno 2015
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _ROUND_SERVER_H_
#define _ROUND_SERVER_H_

#include <round/typedef.h>
#include <round/node_internal.h>
#include <round/cluster_internal.h>
#include <round/finder_internal.h>
#include <round/rpc_server.h>

#ifdef  __cplusplus
extern "C" {
#endif

/****************************************
 * Data Type
 ****************************************/

typedef struct {
  RoundLocalNode *node;
  RoundFinder *finder;
  RoundRpcServer *rpcServer;
} RoundServer;

/****************************************
 * Function
 ****************************************/
  
RoundServer *round_server_new(void);
bool round_server_delete(RoundServer *server);
bool round_server_clear(RoundServer *server);

bool round_server_start(RoundServer *server);
bool round_server_stop(RoundServer *server);
bool round_server_isrunning(RoundServer *server);

#define round_server_getlocalnode(server) (server->node)
#define round_server_getnode(server) ((RoundNode *)(server->node))
#define round_server_getfinder(server) (server->finder)
#define round_server_getrpcserver(server) (server->rpcServer)

void round_server_nodeaddedlistener(RoundFinder *finder, RoundNode *node);
void round_server_noderemovedlistener(RoundFinder *finder, RoundNode *node);

#ifdef  __cplusplus
} /* extern C */
#endif

#endif
