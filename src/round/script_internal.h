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
#include <round/util/map.h>

#ifdef  __cplusplus
extern "C" {
#endif

/****************************************
 * Data Type
 ****************************************/

typedef struct {
  char *lang;
  char *name;
  byte *code;
  size_t codeSize;
} RoundScript;

typedef RoundMap RoundScriptMap;

typedef struct {
  RoundMutex *mutex;
  char *lang;
  char *result;
  char *error;
} RoundScriptEngine;

typedef RoundMap RoundScriptEngineMap;

typedef struct {
  RoundMutex *mutex;
  RoundScriptMap *scriptMap;
  RoundScriptEngineMap *engineMap;
} RoundScriptManager;

/****************************************
 * Function (Script)
 ****************************************/
  
RoundScript *round_script_new();
bool round_script_delete(RoundScript *script);

#define round_script_next(script) ((RoundScript*)round_list_next((RoundList *)script))
#define round_script_remove(script) round_list_remove((RoundList *)script)

#define round_script_setlanguage(script, value) round_strloc(value, &script->lang)
#define round_script_getlanguage(script) (script->lang)

#define round_script_setname(script, value) round_strloc(value, &script->name)
#define round_script_getname(script) (script->name)

bool round_script_setcode(RoundScript *script, byte *code, size_t codeLen);
#define round_script_getcode(script) (script->code)
#define round_script_getcodeSize(script) (script->codeSize)

bool round_script_isvalid(RoundScript *script);
  
/****************************************
 * Function (Script Map)
 ****************************************/

RoundScriptMap *round_script_map_new();
#define round_script_map_delete(map) round_map_delete(map)
#define round_script_map_size(map) round_map_size(map)
#define round_script_map_set(map, script) round_map_setobject(map, script->name, script)
#define round_script_map_get(map, name) ((RoundScript*)round_map_getobjectbykey(map, name))
  
/****************************************
 * Function (Script Engine)
 ****************************************/
  
RoundScriptEngine *round_script_engine_new();
bool round_script_engine_init(RoundScriptEngine *engine);
bool round_script_engine_clear(RoundScriptEngine *engine);
bool round_script_engine_delete(RoundScriptEngine *engine);
bool round_script_engine_lock(RoundScriptEngine *engine);
bool round_script_engine_unlock(RoundScriptEngine *engine);
  
#define round_script_engine_setlanguage(engine, value) round_strloc(value, &engine->lang)
#define round_script_engine_getlanguage(engine) (engine->lang)

bool round_script_engine_setresult(RoundScriptEngine *engine, const char *value);
const char *round_script_engine_getresult(RoundScriptEngine *engine);
  
bool round_script_engine_seterror(RoundScriptEngine *engine, const char *value);
const char *round_script_engine_geterror(RoundScriptEngine *engine);
  
/****************************************
 * Function (Script Engine Map)
 ****************************************/
  
RoundScriptEngineMap *round_script_engine_map_new();
#define round_script_engine_map_delete(map) round_map_delete(map)
#define round_script_engine_map_size(map) round_map_size(map)
#define round_script_engine_map_set(map, eng) round_map_setobject(map, eng->lang, eng)
#define round_script_engine_map_get(map, name) ((RoundScriptEngine*)round_map_getobjectbykey(map, name))

/****************************************
 * Function (Script Manager)
 ****************************************/
  
RoundScriptManager *round_script_manager_new();
bool round_script_manager_delete(RoundScriptManager *mgr);

bool round_script_manager_addscript(RoundScriptManager *mgr, RoundScript *script);
RoundScript *round_script_manager_getscriptbyname(RoundScriptManager *mgr, const char *name);

#ifdef  __cplusplus
}
#endif

#endif