/******************************************************************
 *
 * Round SDK for C
 *
 * Copyright (C) Satoshi Konno 2015
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _ROUNDC_FINDER__H_
#define _ROUNDC_FINDER__H_

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
 * Function
 ****************************************/
  
RoundFinder *round_finder_new(void);
bool round_finder_delete(RoundFinder *finder);

#ifdef  __cplusplus
} /* extern C */
#endif

#endif /* _ROUNDC_FINDER__H_ */
