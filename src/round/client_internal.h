/******************************************************************
 *
 * Round for C
 *
 * Copyright (C) Satoshi Konno 2015
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _ROUND_CLIENT_INTERNAL_H_
#define _ROUND_CLIENT_INTERNAL_H_

#include <round/finder.h>

#ifdef  __cplusplus
extern "C" {
#endif

/****************************************
 * Data Type
 ****************************************/
  
typedef struct {
  RoundFinder *finder;
} RoundClient;
  
#ifdef  __cplusplus
} /* extern C */
#endif

#endif /* _ROUND_CLIENT_INTERNAL_H_ */

#include <round/client.h>
