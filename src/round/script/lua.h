/******************************************************************
 *
 * Round for C
 *
 * Copyright (C) Satoshi Konno 2015
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _ROUND_LUA_ENGINE_H_
#define _ROUND_LUA_ENGINE_H_

#include <round/node_internal.h>
#include <round/script_internal.h>
#include <round/method.h>
#include <round/platform.h>

#ifdef  __cplusplus
extern "C" {
#endif

#if defined(ROUND_SUPPORT_LUA)
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#endif

#define RoundLuaEngineLanguage "lua"
  
typedef struct {
  ROUND_SCRIPT_ENGINE_STRUCT_MEMBERS

#if defined(ROUND_SUPPORT_LUA)
  lua_State *luaState;
#endif
} RoundLuaEngine;

RoundLuaEngine *round_lua_engine_new();
bool round_lua_engine_init(RoundLuaEngine *engine);
bool round_lua_engine_destory(RoundLuaEngine *engine);
bool round_lua_engine_delete(RoundLuaEngine *engine);

bool round_lua_engine_run(RoundLuaEngine *engine, RoundMethod *method, const char *param, RoundJSONObject** resObj, RoundError *err);

#define round_lua_engine_lock(engine) round_script_engine_lock((RoundScriptEngine *)engine)
#define round_lua_engine_unlock(engine) round_script_engine_unlock((RoundScriptEngine *)engine)
  
#if defined(ROUND_SUPPORT_LUA)
bool round_lua_engine_register(RoundLuaEngine *engine, const char *name, lua_CFunction func);
#endif

/****************************************
 * Function
 ****************************************/

#if defined(ROUND_SUPPORT_LUA)

void round_lua_setlocalnode(RoundLocalNode *);
  
int round_lua_getnetworkstate(lua_State* L);
int round_lua_getclusterstate(lua_State* L);
int round_lua_getlocalnodestate(lua_State* L);
int round_lua_setregistry(lua_State* L);
int round_lua_getregistry(lua_State* L);
int round_lua_removeregistry(lua_State* L);
int round_lua_postmethod(lua_State* L);

#endif

#ifdef  __cplusplus
}
#endif

#endif