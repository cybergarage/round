/******************************************************************
 *
 * Round for C
 *
 * Copyright (C) Satoshi Konno 2015
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <round/server_internal.h>

/****************************************
* round_server_new
****************************************/

RoundServer* round_server_new(void)
{
  RoundServer* server;

  server = (RoundServer*)malloc(sizeof(RoundServer));

  if (!server)
    return NULL;

  if (!round_server_init(server)) {
    round_server_delete(server);
    return NULL;
  }

  return server;
}

/****************************************
 * round_server_init
 ****************************************/

bool round_server_init(RoundServer* server)
{
  if (!server)
    return false;

  round_list_node_init((RoundList*)server);

  server->node = round_local_node_new();
  server->finder = round_finder_new();
  server->rpcServer = round_rpc_server_new();

  if (!server->node || !server->finder || !server->rpcServer)
    return false;

  round_server_setuserdata(server, NULL);

  round_rpc_server_setlocalnode(server->rpcServer, server->node);

  round_finder_setuserdata(server->finder, server);
  round_finder_setnodeaddedlistener(server->finder, round_server_nodeaddedlistener);
  round_finder_setnoderemovedlistener(server->finder, round_server_noderemovedlistener);

  round_server_setfinderenabled(server, true);
  
  round_local_node_setaddress(server->node, "");
  round_local_node_setport(server->node, 0);
  
  return true;
}

/****************************************
* round_server_delete
****************************************/

bool round_server_delete(RoundServer* server)
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
 * round_server_setuserdata
 ****************************************/

void round_server_setuserdata(RoundServer* server, void* data)
{
  if (!server)
    return;

  server->userData = data;
}

/****************************************
 * round_server_getuserdata
 ****************************************/

void* round_server_getuserdata(RoundServer* server)
{
  if (!server)
    return NULL;

  return server->userData;
}

/****************************************
 * round_server_getlocalnode
 ****************************************/

RoundLocalNode* round_server_getlocalnode(RoundServer* server)
{
  if (!server)
    return NULL;

  return server->node;
}

/****************************************
 * round_server_start
 ****************************************/

bool round_server_start(RoundServer* server)
{
  if (!server)
    return false;

  bool isSuccess = true;

  isSuccess &= round_server_clear(server);

  isSuccess &= round_local_node_start(server->node);
  isSuccess &= round_rpc_server_start(server->rpcServer);
  if (round_server_isfinderenabled(server)) {
    isSuccess &= round_finder_start(server->finder);
  }
  
  if (!isSuccess) {
    round_server_stop(server);
    return false;
  }

  round_local_node_setaddress(server->node, round_rpc_server_getbindaddress(server->rpcServer));
  round_local_node_setport(server->node, round_rpc_server_getbindport(server->rpcServer));

  return true;
}

/****************************************
 * round_server_stop
 ****************************************/

bool round_server_stop(RoundServer* server)
{
  if (!server)
    return false;

  bool isSuccess = true;
  isSuccess &= round_local_node_stop(server->node);
  isSuccess &= round_finder_stop(server->finder);
  isSuccess &= round_rpc_server_stop(server->rpcServer);

  round_local_node_setaddress(server->node, "");
  round_local_node_setport(server->node, 0);
  
  return isSuccess;
}

/****************************************
 * round_server_restart
 ****************************************/

bool round_server_restart(RoundServer* server)
{
  if (!server)
    return false;
  
  if (!round_server_stop(server))
    return false;
  
  if (!round_server_start(server))
    return false;
  
  return true;
}

/****************************************
 * round_server_clear
 ****************************************/

bool round_server_clear(RoundServer* server)
{
  if (!server)
    return false;

  bool isSuccess = true;
  isSuccess &= round_local_node_clear(server->node);

  return isSuccess;
}

/****************************************
 * round_server_isrunning
 ****************************************/

bool round_server_isrunning(RoundServer* server)
{
  if (!server)
    return false;

  if (!round_local_node_isrunning(server->node))
    return false;

  return true;
}

/****************************************
 * round_server_nodeaddedlistener
 ****************************************/

void round_server_nodeaddedlistener(RoundFinder* finder, RoundNode* node)
{
  if (!finder || !node)
    return;

  RoundServer* server = round_finder_getuserdata(finder);
  if (!server)
    return;

  round_local_node_addclusternode(server->node, node);
}

/****************************************
 * round_server_noderemovedlistener
 ****************************************/

void round_server_noderemovedlistener(RoundFinder* finder, RoundNode* node)
{
  if (!finder || !node)
    return;

  RoundServer* server = round_finder_getuserdata(finder);
  if (!server)
    return;

  round_local_node_removeclusternode(server->node, node);
}

/****************************************
 * round_server_setbindaddress
 ****************************************/

bool round_server_setbindaddress(RoundServer* server, const char* addr)
{
  if (!server)
    return false;

  return round_rpc_server_setbindaddress(server->rpcServer, addr);
}

/****************************************
 * round_server_getbindaddress
 ****************************************/

const char *round_server_getbindaddress(RoundServer* server)
{
  if (!server)
    return false;
  
  return round_rpc_server_getbindaddress(server->rpcServer);
}

/****************************************
 * round_server_setbindport
 ****************************************/

bool round_server_setbindport(RoundServer* server, int port)
{
  if (!server)
    return false;

  return round_rpc_server_setbindport(server->rpcServer, port);
}
/****************************************
 * round_server_getbindport
 ****************************************/

int round_server_getbindport(RoundServer* server)
{
  if (!server)
    return false;
  
  return round_rpc_server_getbindport(server->rpcServer);
}
