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

#include <round/typedef.h>
#include <round/util/mutex.h>
#include <round/util/strings.h>
#include <round/util/list.h>

#ifdef  __cplusplus
extern "C" {
#endif

/****************************************
 * Data Type
 ****************************************/

typedef struct {
  bool headFlag;
  struct _RoundNode *prev;
  struct _RoundNode *next;
} RoundScript, RoundScriptList;

typedef struct {
  RoundMutex *mutex;
  char *result;
  char *error;
} RoundScriptEngine;

typedef struct {
  RoundMutex *mutex;
  RoundScriptList *scripts;
} RoundScriptManager;

/****************************************
 * Function (Script)
 ****************************************/
  
RoundScript *round_script_new();
bool round_script_delete(RoundScript *script);

#define round_script_remove(script) round_list_remove((RoundList *)script)
  
/****************************************
 * Function (Script List)
 ****************************************/

RoundScriptList *round_scriptlist_new(void);
bool round_scriptlist_delete(RoundScriptList *scripts);

#define round_scriptlist_clear(scripts) round_list_clear((RoundList *)scripts, (ROUND_LIST_DESTRUCTORFUNC)round_script_delete)
#define round_scriptlist_size(scripts) round_list_size((RoundList *)scripts)
#define round_scriptlist_gets(scripts) (RoundNode *)round_list_next((RoundList *)scripts)
#define round_scriptlist_add(scripts,script) round_list_add((RoundList *)scripts, (RoundList *)script)
  
/****************************************
 * Function (Script Engine)
 ****************************************/
  
bool round_script_engine_init(RoundScriptEngine *engine);
bool round_script_engine_clear(RoundScriptEngine *engine);
bool round_script_engine_delete(RoundScriptEngine *engine);
bool round_script_engine_lock(RoundScriptEngine *engine);
bool round_script_engine_unlock(RoundScriptEngine *engine);
  
bool round_script_engine_setresult(RoundScriptEngine *engine, const char *value);
const char *round_script_engine_getresult(RoundScriptEngine *engine);
  
bool round_script_engine_seterror(RoundScriptEngine *engine, const char *value);
const char *round_script_engine_geterror(RoundScriptEngine *engine);
  
/****************************************
 * Function (Script Manager)
 ****************************************/
  
RoundScriptManager *round_script_manager_new();
bool round_script_manager_delete(RoundScriptManager *mgr);
  
#ifdef  __cplusplus
}
#endif

#endif