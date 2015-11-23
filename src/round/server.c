/******************************************************************
 *
 * Round for C
 *
 * Copyright (C) Satoshi Konno 2015
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <round/server.h>

/****************************************
* round_server_new
****************************************/

RoundServer *round_server_new(void)
{
  RoundServer *server;

  server = (RoundServer *)malloc(sizeof(RoundServer));

  if (!server)
    return NULL;

  server->node = round_local_node_new();
  server->finder = round_finder_new();
  server->rpcServer = round_rpc_server_new();
  
  if (!server->node || !server->finder || !server->rpcServer) {
    round_server_delete(server);
    return NULL;
  }

  round_rpc_server_setlocalnode(server->rpcServer, server->node);
  
  return server;
}

/****************************************
* round_server_delete
****************************************/

bool round_server_delete(RoundServer *server)
{
  if (!server)
    return false;

  if (!round_server_stop(server))
    return false;
  
  round_local_node_delete(server->node);
  
  free(server);
  
  return true;
}

/****************************************
 * round_server_start
 ****************************************/

bool round_server_start(RoundServer *server)
{
  bool isSuccess = true;
  
  if (!server)
    return false;

  isSuccess &= round_local_node_start(server->node);
  isSuccess &= round_finder_start(server->finder);
  isSuccess &= round_rpc_server_start(server->rpcServer);
  
  if (!isSuccess) {
    round_server_stop(server);
    return false;
  }
  
  return true;
}

/****************************************
 * round_server_stop
 ****************************************/

bool round_server_stop(RoundServer *server)
{
  bool isSuccess = true;

  if (!server)
    return false;
  
  isSuccess &= round_local_node_stop(server->node);
  isSuccess &= round_finder_stop(server->finder);
  isSuccess &= round_rpc_server_stop(server->rpcServer);
  
  return isSuccess;
}

/****************************************
 * round_server_isrunning
 ****************************************/

bool round_server_isrunning(RoundServer *server)
{
  if (!server)
    return false;
  
  if (!round_local_node_isrunning(server->node))
    return false;

  return true;
}
