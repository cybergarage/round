/******************************************************************
 *
 * Round for C
 *
 * Copyright (C) Satoshi Konno 2015
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _ROUND_UTIL_DIGEST_H_
#define _ROUND_UTIL_DIGEST_H_

#include <round/const.h>
#include <round/typedef.h>

#ifdef  __cplusplus
extern "C" {
#endif

#if defined(ROUND_SUPPORT_MD_5DIGEST)
bool round_md5_digest(const char *str, char **buf);
#endif

bool round_sha_digest(const char *str, char **buf);
bool round_sha256_digest(const char *str, char **buf);

#ifdef  __cplusplus
}
#endif

#endif
