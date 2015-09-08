/******************************************************************
 *
 * Round for C
 *
 * Copyright (C) Satoshi Konno 2015
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _ROUNDC_ERROR_H_
#define _ROUNDC_ERROR_H_

#include <round/typedef.h>

#ifdef  __cplusplus
extern "C" {
#endif

/****************************************
* Data Type
****************************************/

#if !defined(_ROUNDC_ERROR_INTERNAL_H_)
typedef void RoundError;
#endif
  
/****************************************
* Function
****************************************/

RoundError *round_error_new();
bool round_error_delete(RoundError *err);

bool round_error_clear(RoundError *err);

bool round_error_setcode(RoundError *err, int code);
int round_error_getcode(RoundError *err);

bool round_error_setmessage(RoundError *err, const char *msg);
const char *round_error_getmessage(RoundError *err);

bool round_error_setdetailcode(RoundError *err, int code);
int round_error_getdetailcode(RoundError *err);

bool round_error_setdetailmessage(RoundError *err, const char *msg);
const char *round_error_getdetailmessage(RoundError *err);

#ifdef  __cplusplus
}
#endif

#endif
