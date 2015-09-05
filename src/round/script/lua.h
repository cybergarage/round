/******************************************************************
 *
 * Round for C
 *
 * Copyright (C) Satoshi Konno 2015
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _ROUNDC_LUA_ENGINE_H_
#define _ROUNDC_LUA_ENGINE_H_

#include <round/script_internal.h>

#ifdef  __cplusplus
extern "C" {
#endif

#if defined(ROUND_SUPPORT_LUA)
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#endif

typedef struct _RoundLuaEngine {
  RoundMutex *mutex;
  char *result;
  char *error;
#if defined(ROUND_SUPPORT_LUA)
  lua_State *luaState;
#endif
} RoundLuaEngine;

RoundLuaEngine *round_lua_engine_new();
bool round_lua_engine_delete(RoundLuaEngine *luaEngine);

bool round_lua_engine_lock(RoundLuaEngine *luaEngine);
bool round_lua_engine_unlock(RoundLuaEngine *luaEngine);
  
bool round_lua_engine_setresult(RoundLuaEngine *luaEngine, const char *value);
const char *round_lua_engine_getresult(RoundLuaEngine *luaEngine);

bool round_lua_engine_seterror(RoundLuaEngine *luaEngine, const char *value);
const char *round_lua_engine_geterror(RoundLuaEngine *luaEngine);

bool round_lua_engine_run(RoundLuaEngine *luaEngine, const char *source, const char *func, const char *param);

#if defined(ROUND_SUPPORT_LUA)
bool round_lua_engine_register(RoundLuaEngine *luaEngine, const char *name, lua_CFunction func);
#endif

#ifdef  __cplusplus
}
#endif

#endif