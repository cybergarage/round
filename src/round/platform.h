/******************************************************************
 *
 * Round for C
 *
 * Copyright (C) Satoshi Konno 2015
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _ROUNDC_PLATFORM_H_
#define _ROUNDC_PLATFORM_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#ifdef HAVE_CONFIG_H
#  include "config.h"
#endif

#ifdef  __cplusplus
extern "C" {
#endif

#if defined(__APPLE__)

#define ROUND_SUPPORT_JS_SM
#define ROUND_SUPPORT_LUA
//#define ROUND_SUPPORT_RUBY
#define ROUND_USE_JSON_PARSER_JANSSON

#endif

#ifdef  __cplusplus
}
#endif

#endif
