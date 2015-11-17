/******************************************************************
 *
 * Round for C
 *
 * Copyright (C) Satoshi Konno 2015
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <round/rpc_server.h>

/****************************************
* round_rpc_server_new
****************************************/

RoundRpcServer *round_rpc_server_new(void)
{
  RoundRpcServer *server;

  server = (RoundRpcServer *)malloc(sizeof(RoundRpcServer));

  if (!server)
    return NULL;

  server->upnpDev = round_upnp_server_new();
  
  if (!server->upnpDev) {
    round_rpc_server_delete(server);
    return NULL;
  }

  return server;
}

/****************************************
* round_rpc_server_delete
****************************************/

bool round_rpc_server_delete(RoundRpcServer *server)
{
  if (!server)
    return false;

  if (!round_rpc_server_stop(server))
    return false;
  
  mupnp_device_delete(server->upnpDev);
  
  free(server);
  
  return true;
}

/****************************************
 * round_rpc_server_start
 ****************************************/

bool round_rpc_server_start(RoundRpcServer *server)
{
  bool isSuccess = true;
  
  if (!server)
    return false;

  isSuccess &= mupnp_device_start(server->upnpDev);
  
  if (!isSuccess) {
    round_rpc_server_stop(server);
    return false;
  }
  
  return true;
}

/****************************************
 * round_rpc_server_stop
 ****************************************/

bool round_rpc_server_stop(RoundRpcServer *server)
{
  bool isSuccess = true;

  if (!server)
    return false;
  
  isSuccess &= mupnp_device_stop(server->upnpDev);
  
  return true;
}

/****************************************
 * round_rpc_server_isrunning
 ****************************************/

bool round_rpc_server_isrunning(RoundRpcServer *server)
{
  if (!server)
    return false;
  
  if (!mupnp_device_isrunning(server->upnpDev))
    return false;

  return true;
}
