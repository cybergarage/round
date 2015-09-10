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

#include <round/script.h>
#include <round/method.h>

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
bool round_lua_engine_destory(RoundLuaEngine *engine);
bool round_lua_engine_delete(RoundLuaEngine *engine);

bool round_lua_engine_run(RoundLuaEngine *engine, RoundMethod *method, const char *param, RoundString *result, RoundError *err);

#if defined(ROUND_SUPPORT_LUA)
bool round_lua_engine_register(RoundLuaEngine *engine, const char *name, lua_CFunction func);
#endif

#ifdef  __cplusplus
}
#endif

#endif