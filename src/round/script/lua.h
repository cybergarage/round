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
  char *lang;
  ROUND_SCRIPT_ENGINE_EXECFUNC execFunc;
  ROUND_SCRIPT_ENGINE_DESTRUCTOR destFunc;
#if defined(ROUND_SUPPORT_LUA)
  lua_State *luaState;
#endif
} RoundLuaEngine;

RoundLuaEngine *round_lua_engine_new();
bool round_lua_engine_delete(RoundLuaEngine *engine);

bool round_lua_engine_run(RoundLuaEngine *engine, RoundScript *script, const char *param, RoundString *result, RoundError *err);

#if defined(ROUND_SUPPORT_LUA)
bool round_lua_engine_register(RoundLuaEngine *engine, const char *name, lua_CFunction func);
#endif

#ifdef  __cplusplus
}
#endif

#endif