/******************************************************************
 *
 * Round for C
 *
 * Copyright (C) Satoshi Konno 2015
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _ROUND_UTIL_STATUS_H_
#define _ROUND_UTIL_STATUS_H_

#include <round/typedef.h>

#ifdef  __cplusplus
extern "C" {
#endif

/****************************************
 * Data Type
 ****************************************/

typedef int RoundStatus;
  
/****************************************
 * Macros
 ****************************************/

#define round_status_init(stat) (stat = 0)
#define round_status_set(stat, value) (stat = value)
#define round_status_get(stat) (stat)
#define round_status_setflag(stat, flag, value) (value ? (stat |= flag) : (stat ^= flag))
#define round_status_isenabled(stat, flag) ((stat & flag) ? true : false)
#define round_status_isdisabled(stat, flag) ((stat & flag) ? false : true)
#define round_status_clear(stat) round_status_init(stat)

#ifdef  __cplusplus

} /* extern "C" */

#endif

#endif
