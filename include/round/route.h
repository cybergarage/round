/******************************************************************
 *
 * Round for C
 *
 * Copyright (C) Satoshi Konno 2015
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _ROUND_ROUTE_H_
#define _ROUND_ROUTE_H_

#ifdef HAVE_CONFIG_H
#  include "config.h"
#endif

#ifdef  __cplusplus
extern "C" {
#endif

/****************************************
 * Constants
 ****************************************/

typedef enum {
  RoundRouteObjectNone = 0x00,
  RoundRouteTriggerObject = 0x01,
  RoundRouteMethodObject = 0x02,
} RoundRouteObjectType;

/****************************************
 * Data Type
 ****************************************/
  
#if !defined(_ROUND_ROUTE_INTERNAL_H_)
typedef void RoundRouteObject;
typedef void RoundRoute;
typedef void RoundRouteManager;
#endif

#ifdef  __cplusplus
}
#endif

#endif
