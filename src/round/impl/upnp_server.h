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
 * Data Type
 ****************************************/
  
typedef struct {
mUpnpDevice *dev;
} RoundUpnpServer;
  
/****************************************
 * Function
 ****************************************/
  
RoundUpnpServer *round_upnp_server_new(void);
bool round_upnp_server_delete(RoundUpnpServer *server);
  
#define round_upnp_server_start(server) mupnp_device_start(server->dev)
#define round_upnp_server_stop(server) mupnp_device_stop(server->dev)
#define round_upnp_server_isrunning(server) mupnp_device_isrunning(server->dev)

#ifdef  __cplusplus
} /* extern C */
#endif

#endif
