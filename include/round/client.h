/******************************************************************
 *
 * Round SDK for C
 *
 * Copyright (C) Satoshi Konno 2015
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _ROUNDC_CLIENT_H_
#define _ROUNDC_CLIENT_H_

#include <round/typedef.h>
#include <round/const.h>

#ifdef  __cplusplus
extern "C" {
#endif

/****************************************
 * Data Type
 ****************************************/
  
#if !defined(_ROUNDC_CLIENT_INTERNAL_H_)
typedef void RoundClient;
#endif

/****************************************
 * Function
 ****************************************/
  
RoundClient *round_client_new(void);
bool round_client_delete(RoundClient *c);
  
#ifdef  __cplusplus
} /* extern C */
#endif

#endif /* _ROUNDC_CLIENT_H_ */
