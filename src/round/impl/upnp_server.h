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
 * Function
 ****************************************/

mUpnpDevice *round_upnp_server_new(void);

#ifdef  __cplusplus
} /* extern C */
#endif

#endif
