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
#include <round/util/oo.h>
#include <round/util/mutex.h>
#include <round/util/strings.h>
#include <round/util/map.h>
#include <round/util/option.h>

#ifdef  __cplusplus
extern "C" {
#endif

/****************************************
 * Data Type
 ****************************************/

typedef bool (*ROUND_SCRIPT_ENGINE_EXECFUNC)(void *engine, void *method, const char *param, RoundString *result, RoundError *err);

#define ROUND_SCRIPT_ENGINE_STRUCT_MEMBERS \
  RoundMutex *mutex; \
  char *lang; \
  RoundOption opt; \
  ROUND_OO_STRUCT_MEMBERS \
  ROUND_SCRIPT_ENGINE_EXECFUNC execFunc; \
  void *node;

typedef struct {
  ROUND_SCRIPT_ENGINE_STRUCT_MEMBERS  
} RoundScriptEngine;

/****************************************
 * Function (Script Engine)
 ****************************************/
  
RoundScriptEngine *round_script_engine_new();
bool round_script_engine_init(RoundScriptEngine *engine);
bool round_script_engine_destory(RoundScriptEngine *engine);
bool round_script_engine_delete(RoundScriptEngine *engine);

bool round_script_engine_lock(RoundScriptEngine *engine);
bool round_script_engine_unlock(RoundScriptEngine *engine);
  
#define round_script_engine_setlanguage(engine, value) round_strloc(value, &engine->lang)
#define round_script_engine_getlanguage(engine) (engine->lang)

#define round_script_engine_setoption(engine, value) round_option_set(engine->opt, value)
#define round_script_engine_getoption(engine) round_option_get(engine->opt)
#define round_script_engine_setoptionflag(engine, value) round_option_setflag(engine->opt, value)
#define round_script_engine_isoptionflagenabled(engine, value) round_option_isenabled(engine->opt, value)

#define round_script_engine_setexecutefunc(engine, func) (engine->execFunc = (ROUND_SCRIPT_ENGINE_EXECFUNC)func)
#define round_script_engine_getexecutefunc(engine) (engine->execFunc)

#define round_script_engine_setlocalnode(engine, value) (engine->node = value)
#define round_script_engine_getlocalnode(engine) ((RoundLocalNode *)engine->node)

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