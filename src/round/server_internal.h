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
  ROUND_LIST_STRUCT_MEMBERS

  RoundLocalNode *node;
  RoundRpcServer *rpcServer;
  void *userData;
  
#if defined(ROUND_ENABLE_FINDER)
  RoundFinder *finder;
  bool finderEnabled;
#endif
  
} RoundServer, RoundServerList;

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
  
#define round_server_next(server) (RoundServer *)round_list_next((RoundList *)server)
#define round_server_remove(server) round_list_remove((RoundList *)server)

#define round_server_setfinderenabled(server, flag) (server->finderEnabled = flag)
#define round_server_isfinderenabled(server) (server->finderEnabled)

/****************************************
 * Function (Fineder)
 ****************************************/
  
#if defined(ROUND_ENABLE_FINDER)

void round_server_nodeaddedlistener(RoundFinder *finder, RoundNode *node);
void round_server_noderemovedlistener(RoundFinder *finder, RoundNode *node);

#endif
  
/****************************************
 * Function (Server List)
 ****************************************/
  
RoundServerList *round_server_list_new();
void round_server_list_delete(RoundServerList *servers);

#define round_server_list_clear(servers) round_list_clear((RoundList *)servers, (ROUND_LIST_DESTRUCTORFUNC)round_server_delete)
#define round_server_list_size(servers) round_list_size((RoundList *)servers)
#define round_server_list_gets(servers) (RoundServer *)round_list_next((RoundList *)servers)
#define round_server_list_remove(server) round_list_remove((RoundList *)server)

bool round_server_list_start(RoundServerList *servers);
bool round_server_list_stop(RoundServerList *servers);
bool round_server_list_isrunning(RoundServerList *servers);

#ifdef  __cplusplus
} /* extern C */
#endif

#endif
