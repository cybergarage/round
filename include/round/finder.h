/******************************************************************
 *
 * Round for C
 *
 * Copyright (C) Satoshi Konno 2015
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _ROUND_FINDER__H_
#define _ROUND_FINDER__H_

#include <round/typedef.h>
#include <round/const.h>

#include <mupnp/controlpoint.h>

#ifdef  __cplusplus
extern "C" {
#endif

/****************************************
 * Data Type
 ****************************************/
  
#if !defined(_ROUND_FINDER_INTERNAL_H_)
typedef void RoundFinder;
#endif
  
/****************************************
 * Function
 ****************************************/
  
RoundFinder *round_finder_new(void);
bool round_finder_delete(RoundFinder *finder);

bool round_finder_start(RoundFinder *finder);
bool round_finder_stop(RoundFinder *finder);

bool round_finder_search(RoundFinder *finder);

#ifdef  __cplusplus
} /* extern C */
#endif

#endif /* _ROUND_FINDER__H_ */
