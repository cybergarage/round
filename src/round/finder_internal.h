/******************************************************************
 *
 * Round for C
 *
 * Copyright (C) Satoshi Konno 2015
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _ROUNDC_FINDER_INTERNAL_H_
#define _ROUNDC_FINDER_INTERNAL_H_

#include <round/typedef.h>
#include <round/const.h>

#include <mupnp/controlpoint.h>

#ifdef  __cplusplus
extern "C" {
#endif

/****************************************
 * Data Type
 ****************************************/
  
typedef struct {
  mUpnpControlPoint *cp;
} RoundFinder;

/****************************************
 * Public Header
 ****************************************/
  
#include <round/node.h>
  
/****************************************
 * Function
 ****************************************/
  
#ifdef  __cplusplus
} /* extern C */
#endif

#endif /* _ROUNDC_FINDER_INTERNAL_H_ */
