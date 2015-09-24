/******************************************************************
 *
 * Round for C
 *
 * Copyright (C) Satoshi Konno 2015
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _ROUNDC_UTIL_OPTION_H_
#define _ROUNDC_UTIL_OPTION_H_

#include <round/typedef.h>

#ifdef  __cplusplus
extern "C" {
#endif

/****************************************
 * Data Type
 ****************************************/

typedef int RoundOption;
  
/****************************************
 * Macros
 ****************************************/

#define round_option_set(opt, value) (opt = value)
#define round_option_get(opt) (opt)
#define round_option_setflag(opt, flag, value) (value ? (opt |= flag) : (opt ^= flag))
#define round_option_isenabled(opt, flag) (opt & flag)

#ifdef  __cplusplus

} /* extern "C" */

#endif

#endif
