/******************************************************************
 *
 * Round for C
 *
 * Copyright (C) Satoshi Konno 2015
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _ROUND_UPNP_SERVER_H_
#define _ROUND_UPNP_SERVER_H_

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
  void *rpcServer;
} RoundUpnpServer;
  
/****************************************
 * Function
 ****************************************/
  
RoundUpnpServer *round_upnp_server_new(void);
bool round_upnp_server_delete(RoundUpnpServer *server);

const char *round_upnp_server_getaddress(RoundUpnpServer *server);
int round_upnp_server_getport(RoundUpnpServer *server);

#define round_upnp_server_setrpcserver(server,rpcSrv) mupnp_device_setuserdata(server->dev, rpcSrv)
#define round_upnp_device_getrpcserver(dev) ((RoundRpcServer *)mupnp_device_getuserdata(dev))
  
#define round_upnp_server_setrpcrequestlistener(server,func) (server->rpcReqListener = func)
#define round_upnp_server_postrpcrequest(server,httpReq) server->rpcReqListener(httpReq)

#define round_upnp_server_start(server) mupnp_device_start(server->dev)
#define round_upnp_server_stop(server) mupnp_device_stop(server->dev)
#define round_upnp_server_isrunning(server) mupnp_device_isrunning(server->dev)

#ifdef  __cplusplus
} /* extern C */
#endif

#endif
