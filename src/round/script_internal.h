/******************************************************************
 *
 * Round for C
 *
 * Copyright (C) Satoshi Konno 2015
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _ROUNDC_SCRIPT_INTERNAL_H_
#define _ROUNDC_SCRIPT_INTERNAL_H_

#ifdef HAVE_CONFIG_H
#  include "config.h"
#endif

#include <round/util/mutex.h>
#include <round/util/strings.h>

#ifdef  __cplusplus
extern "C" {
#endif

/****************************************
 * Data Type
 ****************************************/

typedef struct _RoundScriptEngine {
  RoundMutex *mutex;
  char *result;
  char *error;
} RoundScriptEngine;

/****************************************
 * Function
 ****************************************/

bool round_script_engine_init(RoundScriptEngine *scriptEngine);
bool round_script_engine_clear(RoundScriptEngine *scriptEngine);
bool round_script_engine_delete(RoundScriptEngine *scriptEngine);
bool round_script_engine_lock(RoundScriptEngine *scriptEngine);
bool round_script_engine_unlock(RoundScriptEngine *scriptEngine);
  
bool round_script_engine_setresult(RoundScriptEngine *scriptEngine, const char *value);
const char *round_script_engine_getresult(RoundScriptEngine *scriptEngine);

bool round_script_engine_seterror(RoundScriptEngine *scriptEngine, const char *value);
const char *round_script_engine_geterror(RoundScriptEngine *scriptEngine);

#ifdef  __cplusplus
}
#endif

#endif