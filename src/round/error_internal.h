/******************************************************************
 *
 * Round for C
 *
 * Copyright (C) Satoshi Konno 2015
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _ROUNDC_ERROR_INTERNAL_H_
#define _ROUNDC_ERROR_INTERNAL_H_

#include <round/typedef.h>
#include <round/util/strings.h>

#ifdef  __cplusplus
extern "C" {
#endif

/****************************************
* Data Type
****************************************/

typedef struct {
  RoundString *msg;
  RoundString *detailMsg;
  int code;
  int detailCode;
} RoundError;

/****************************************
 * Public Header
 ****************************************/
  
#include <round/error.h>
  
/****************************************
* Function
****************************************/
  
#ifdef  __cplusplus
}
#endif

#endif
