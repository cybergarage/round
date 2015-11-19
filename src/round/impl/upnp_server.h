/******************************************************************
 *
 * Round for C
 *
 * Copyright (C) Satoshi Konno 2015
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _ROUNDC_UPNP_SERVER_H_
#define _ROUNDC_UPNP_SERVER_H_

#include <round/typedef.h>
#include <mupnp/device.h>

#ifdef  __cplusplus
extern "C" {
#endif

/****************************************
 * Define
 ****************************************/
  
typedef void(*ROUND_UPNP_SERVER_JSON_RPC_REQUEST_LISTENER)(mUpnpHttpRequest *httpReq);

/****************************************
 * Data Type
 ****************************************/
  
typedef struct {
  mUpnpDevice *dev;
  ROUND_UPNP_SERVER_JSON_RPC_REQUEST_LISTENER rpcReqListener;
} RoundUpnpServer;
  
/****************************************
 * Function
 ****************************************/
  
RoundUpnpServer *round_upnp_server_new(void);
bool round_upnp_server_delete(RoundUpnpServer *server);

#define round_upnp_server_setrpcrequestlistener(server,func) (server->rpcReqListener = func)
#define round_upnp_server_hasrpcrequestlistener(server) ((server->rpcReqListener) ? true : false)
#define round_upnp_server_postrpcrequest(server,httpReq) server->rpcReqListener(httpReq)

#define round_upnp_server_start(server) mupnp_device_start(server->dev)
#define round_upnp_server_stop(server) mupnp_device_stop(server->dev)
#define round_upnp_server_isrunning(server) mupnp_device_isrunning(server->dev)

#ifdef  __cplusplus
} /* extern C */
#endif

#endif
