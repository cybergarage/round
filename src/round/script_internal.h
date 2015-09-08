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
#include <round/const.h>
#include <round/error_internal.h>
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

typedef bool (*ROUND_SCRIPT_ENGINE_EXECFUNC)(void *engine, RoundScript *script, const char *param, RoundString *result, RoundError *err);
typedef bool (*ROUND_SCRIPT_ENGINE_DESTRUCTOR)(void *engine);
  
typedef struct {
  RoundMutex *mutex;
  char *lang;
  ROUND_SCRIPT_ENGINE_EXECFUNC execFunc;
  ROUND_SCRIPT_ENGINE_DESTRUCTOR destFunc;
} RoundScriptEngine;

typedef struct {
  RoundMutex *mutex;
  RoundMap *scriptMap;
  RoundMap *engineMap;
} RoundScriptManager;

/****************************************
 * Function (Script)
 ****************************************/
  
RoundScript *round_script_new();
bool round_script_delete(RoundScript *script);

#define round_script_setlanguage(script, value) round_strloc(value, &script->lang)
#define round_script_getlanguage(script) (script->lang)

#define round_script_setname(script, value) round_strloc(value, &script->name)
#define round_script_getname(script) (script->name)

bool round_script_setcode(RoundScript *script, byte *code, size_t codeLen);
#define round_script_getcode(script) (script->code)
#define round_script_getsource(script) ((const char *)script->code)
#define round_script_getcodeSize(script) (script->codeSize)

bool round_script_isvalid(RoundScript *script);
  
/****************************************
 * Function (Script Map)
 ****************************************/

RoundMap *round_script_map_new();

#define round_script_map_delete(map) round_map_delete(map)
#define round_script_map_size(map) round_map_size(map)
#define round_script_map_set(map, script) round_map_setobject(map, script->name, script)
#define round_script_map_get(map, name) ((RoundScript*)round_map_getobjectbykey(map, name))
#define round_script_map_remove(map, name) round_map_removeobjectbykey(map, name)
  
/****************************************
 * Function (Script Engine)
 ****************************************/
  
RoundScriptEngine *round_script_engine_new();
bool round_script_engine_init(RoundScriptEngine *engine);
bool round_script_engine_destory(RoundScriptEngine *engine);
bool round_script_engine_delete(RoundScriptEngine *engine);

#define round_script_engine_lock(engine) round_mutex_lock(engine->mutex)
#define round_script_engine_unlock(engine) round_mutex_unlock(engine->mutex)
  
#define round_script_engine_setlanguage(engine, value) round_strloc(value, &engine->lang)
#define round_script_engine_getlanguage(engine) (engine->lang)

#define round_script_engine_setexecutefunc(engine, func) (engine->execFunc = (ROUND_SCRIPT_ENGINE_EXECFUNC)func)
#define round_script_engine_setdestructor(engine, func) (engine->destFunc = (ROUND_SCRIPT_ENGINE_DESTRUCTOR)func)

bool round_script_engine_isvalid(RoundScriptEngine *engine);
bool round_script_engine_execscript(RoundScriptEngine *engine, RoundScript *script, const char *param, RoundString *result, RoundError *err);
  
/****************************************
 * Function (Script Engine Map)
 ****************************************/
  
RoundMap *round_script_engine_map_new();
#define round_script_engine_map_delete(map) round_map_delete(map)
#define round_script_engine_map_size(map) round_map_size(map)
#define round_script_engine_map_set(map, eng) round_map_setobject(map, eng->lang, eng)
#define round_script_engine_map_get(map, name) ((RoundScriptEngine*)round_map_getobjectbykey(map, name))
#define round_script_engine_map_remove(map, name) round_map_removeobjectbykey(map, name)

/****************************************
 * Function (Script Manager)
 ****************************************/
  
RoundScriptManager *round_script_manager_new();
bool round_script_manager_delete(RoundScriptManager *mgr);

bool round_script_manager_addscript(RoundScriptManager *mgr, RoundScript *script);
RoundScript *round_script_manager_getscript(RoundScriptManager *mgr, const char *name);
bool round_script_manager_removescript(RoundScriptManager *mgr, const char *name);
#define round_script_manager_getscriptsize(mgr) round_map_size(mgr->scriptMap)

bool round_script_manager_addengine(RoundScriptManager *mgr, RoundScriptEngine *engine);
RoundScriptEngine *round_script_manager_getengine(RoundScriptManager *mgr, const char *name);
bool round_script_manager_removeengine(RoundScriptManager *mgr, const char *name);
#define round_script_manager_getenginsize(mgr) round_map_size(mgr->engineMap)
  
#ifdef  __cplusplus
}
#endif

#endif