/******************************************************************
 *
 * Round for C
 *
 * Copyright (C) Satoshi Konno 2015
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _ROUNDC_RPC_SERVER_H_
#define _ROUNDC_RPC_SERVER_H_

#include <round/typedef.h>
#include <mupnp/device.h>

#ifdef  __cplusplus
extern "C" {
#endif

/****************************************
 * Data Type
 ****************************************/

typedef struct {
  mUpnpDevice *upnpDev;
} RoundRpcServer;

/****************************************
 * Function
 ****************************************/
  
RoundRpcServer *round_rpc_server_new(void);
bool round_rpc_server_delete(RoundRpcServer *server);

bool round_rpc_server_start(RoundRpcServer *server);
bool round_rpc_server_stop(RoundRpcServer *server);
bool round_rpc_server_isrunning(RoundRpcServer *server);

#ifdef  __cplusplus
} /* extern C */
#endif

#endif
