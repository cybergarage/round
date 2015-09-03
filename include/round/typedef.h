/******************************************************************
 *
 * Round SDK for C
 *
 * Copyright (C) Satoshi Konno 2015
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _ROUNDC_TYPEDEF_H_
#define _ROUNDC_TYPEDEF_H_

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

/****************************************
 * Compiler
****************************************/

#if __STDC_VERSION__ >= 199901L
#define C99
#endif

/****************************************
* Data Type
****************************************/

#if defined(C99) || defined(HAVE_STDBOOL_H)
#include <stdbool.h>
#else
#if !defined(bool)
#define bool int
#endif
#if !defined(true)
#define true 1
#endif
#if !defined(false)
#define false 0
#endif
#endif

typedef unsigned char byte;

#ifdef  __cplusplus
}
#endif

#endif
