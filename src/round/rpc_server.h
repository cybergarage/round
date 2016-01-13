/******************************************************************
 *
 * Round for C
 *
 * Copyright (C) Satoshi Konno 2015
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _ROUND_RPC_SERVER_H_
#define _ROUND_RPC_SERVER_H_

#include <round/typedef.h>
#include <round/impl/upnp_server.h>

#ifdef  __cplusplus
extern "C" {
#endif

/****************************************
 * Data Type
 ****************************************/

typedef struct {
  RoundUpnpServer *upnpServer;
  void *localNode;
} RoundRpcServer;

/****************************************
 * Function
 ****************************************/
  
RoundRpcServer *round_rpc_server_new(void);
bool round_rpc_server_delete(RoundRpcServer *server);

bool round_rpc_server_start(RoundRpcServer *server);
bool round_rpc_server_stop(RoundRpcServer *server);
bool round_rpc_server_isrunning(RoundRpcServer *server);

#define round_rpc_server_setbindaddress(server,addr) round_upnp_server_setbindaddress(server->upnpServer, addr)
#define round_rpc_server_setbindport(server,port) round_upnp_server_setbindport(server->upnpServer, port)

#define round_rpc_server_getbindaddress(server) round_upnp_server_getbindaddress(server->upnpServer)
#define round_rpc_server_getbindport(server) round_upnp_server_getbindport(server->upnpServer)

#define round_rpc_server_setlocalnode(server,node) (server->localNode = node)
#define round_rpc_server_getlocalnode(server) ((RoundLocalNode *)(server->localNode))
  
#ifdef  __cplusplus
} /* extern C */
#endif

#endif
