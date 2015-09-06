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

typedef struct {
  RoundMutex *mutex;
  char *result;
  char *error;
} RoundScript;

typedef struct {
  RoundMutex *mutex;
  char *result;
  char *error;
} RoundScriptEngine;

typedef struct {
  RoundMutex *mutex;
} RoundScriptManager;

/****************************************
 * Function (Script)
 ****************************************/
  
RoundScript *round_script_new();
bool round_script_delete(RoundScript *scr);
  
/****************************************
 * Function (Script Engine)
 ****************************************/
  
bool round_script_engine_init(RoundScriptEngine *eng);
bool round_script_engine_clear(RoundScriptEngine *eng);
bool round_script_engine_delete(RoundScriptEngine *eng);
bool round_script_engine_lock(RoundScriptEngine *eng);
bool round_script_engine_unlock(RoundScriptEngine *eng);
  
bool round_script_engine_setresult(RoundScriptEngine *engine, const char *value);
const char *round_script_engine_getresult(RoundScriptEngine *eng);
  
bool round_script_engine_seterror(RoundScriptEngine *engine, const char *value);
const char *round_script_engine_geterror(RoundScriptEngine *eng);
  
/****************************************
 * Function (Script Manager)
 ****************************************/
  
RoundScriptManager *round_script_manager_new();
bool round_script_manager_delete(RoundScriptManager *mgr);
  
#ifdef  __cplusplus
}
#endif

#endif