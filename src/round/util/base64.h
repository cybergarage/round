/******************************************************************
 *
 * Round for C
 *
 * Copyright (C) Satoshi Konno 2015
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _ROUND_UTIL_BASE64_H_
#define _ROUND_UTIL_BASE64_H_

#include <round/typedef.h>

#ifdef  __cplusplus
extern "C" {
#endif
  
/****************************************
 * Function
 ****************************************/

ssize_t round_base64_encode(const byte *rawBytes, size_t rawByteLen, char **encodedStr);
ssize_t round_base64_decode(const char *encodedStr, byte **decordedBytes);

#ifdef  __cplusplus
}
#endif

#endif
