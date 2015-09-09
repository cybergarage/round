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

typedef bool (*ROUND_SCRIPT_ENGINE_EXECFUNC)(void *engine, void *script, const char *param, RoundString *result, RoundError *err);
typedef bool (*ROUND_SCRIPT_ENGINE_DESTRUCTOR)(void *engine);
  
typedef struct {
  RoundMutex *mutex;
  char *lang;
  int opt;
  ROUND_SCRIPT_ENGINE_EXECFUNC execFunc;
  ROUND_SCRIPT_ENGINE_DESTRUCTOR destFunc;
  
} RoundScriptEngine;

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

#define round_script_engine_setoption(engine, value) (engine->opt = value)
#define round_script_engine_getoption(engine) (engine->opt)
#define round_script_engine_enableoption(engine, value) (engine->opt & value)

#define round_script_engine_setexecutefunc(engine, func) (engine->execFunc = (ROUND_SCRIPT_ENGINE_EXECFUNC)func)
#define round_script_engine_setdestructor(engine, func) (engine->destFunc = (ROUND_SCRIPT_ENGINE_DESTRUCTOR)func)

bool round_script_engine_isvalid(RoundScriptEngine *engine);
  
/****************************************
 * Function (Script Engine Map)
 ****************************************/
  
RoundMap *round_script_engine_map_new();
#define round_script_engine_map_delete(map) round_map_delete(map)
#define round_script_engine_map_size(map) round_map_size(map)
#define round_script_engine_map_set(map, eng) round_map_setobject(map, eng->lang, eng)
#define round_script_engine_map_get(map, name) ((RoundScriptEngine*)round_map_getobjectbykey(map, name))
#define round_script_engine_map_remove(map, name) round_map_removeobjectbykey(map, name)
  
#ifdef  __cplusplus
}
#endif

#endif