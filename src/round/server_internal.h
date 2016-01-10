/******************************************************************
 *
 * Round for C
 *
 * Copyright (C) Satoshi Konno 2015
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _ROUND_SERVER_INTERNAL_H_
#define _ROUND_SERVER_INTERNAL_H_

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
  bool deamonMode;
  void *userData;
} RoundServer;

/****************************************
 * Public Header
 ****************************************/
  
#include <round/server.h>

/****************************************
 * Function
 ****************************************/

bool round_server_init(RoundServer *server);

#define round_server_getfinder(server) (server->finder)
#define round_server_getrpcserver(server) (server->rpcServer)
  
void round_server_nodeaddedlistener(RoundFinder *finder, RoundNode *node);
void round_server_noderemovedlistener(RoundFinder *finder, RoundNode *node);

#define round_server_setdeamonmode(server, flag) (server->deamonMode = flag)

#ifdef  __cplusplus
} /* extern C */
#endif

#endif
