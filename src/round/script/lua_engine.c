/******************************************************************
 *
 * Round for C
 *
 * Copyright (C) Satoshi Konno 2015
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <stdlib.h>
#include <round/script/lua.h>

/****************************************
* round_lua_engine_new
****************************************/

RoundLuaEngine *round_lua_engine_new() {
  RoundLuaEngine *luaEngine;
  
  luaEngine = (RoundLuaEngine *)calloc(1, sizeof(RoundLuaEngine));
  if (!luaEngine)
    return NULL;

  if (!round_script_engine_init((RoundScriptEngine *)luaEngine)) {
    round_lua_engine_delete(luaEngine);
    return NULL;
  }

#if defined(ROUND_SUPPORT_LUA)
  luaEngine->luaState = luaL_newstate();
  luaL_openlibs(luaEngine->luaState);
#endif
  
  return luaEngine;
}

/****************************************
 * round_lua_engine_delete
 ****************************************/

bool round_lua_engine_delete(RoundLuaEngine *luaEngine) {
  if (!luaEngine)
    return false;
  
  return round_script_engine_delete((RoundScriptEngine *)luaEngine);
}

/****************************************
 * round_lua_engine_setresult
 ****************************************/

bool round_lua_engine_setresult(RoundLuaEngine *luaEngine, const char *value) {
  return round_script_engine_setresult((RoundScriptEngine *)luaEngine, value);
}

/****************************************
 * round_lua_engine_getresult
 ****************************************/

const char *round_lua_engine_getresult(RoundLuaEngine *luaEngine) {
  return round_script_engine_getresult((RoundScriptEngine *)luaEngine);
}

/****************************************
 * round_lua_engine_seterror
 ****************************************/

bool round_lua_engine_seterror(RoundLuaEngine *luaEngine, const char *value) {
  return round_script_engine_seterror((RoundScriptEngine *)luaEngine, value);
}

/****************************************
 * round_lua_engine_geterror
 ****************************************/

const char *round_lua_engine_geterror(RoundLuaEngine *luaEngine) {
  return round_script_engine_geterror((RoundScriptEngine *)luaEngine);
}

/****************************************
 * round_lua_engine_lock
 ****************************************/

bool round_lua_engine_lock(RoundLuaEngine *luaEngine) {
  return round_script_engine_lock((RoundScriptEngine *)luaEngine);
}

/****************************************
 * round_lua_engine_unlock
 ****************************************/

bool round_lua_engine_unlock(RoundLuaEngine *luaEngine) {
  return round_script_engine_unlock((RoundScriptEngine *)luaEngine);
}

/****************************************
 * round_lua_engine_register
 ****************************************/

#if defined(ROUND_SUPPORT_LUA)

bool round_lua_engine_register(RoundLuaEngine *luaEngine, const char *name, lua_CFunction func) {

  lua_register(luaEngine->luaState, name, func);
  
  return true;
}

#endif

/****************************************
 * round_lua_engine_popresult
 ****************************************/

#if defined(ROUND_SUPPORT_LUA)

bool round_lua_engine_popresult(RoundLuaEngine *luaEngine) {
  char strbuf[128];
  
  int nStack = lua_gettop(luaEngine->luaState);
  if (nStack <= 0)
    return false;
  
  if (lua_isstring(luaEngine->luaState, -1)) {
    round_lua_engine_setresult(luaEngine, lua_tostring(luaEngine->luaState, -1));
    lua_pop(luaEngine->luaState, 1);
    return true;
  }
  
  if (lua_isboolean(luaEngine->luaState, -1)) {
    round_lua_engine_setresult(luaEngine, lua_toboolean(luaEngine->luaState, -1) ? "true" : "false");
    lua_pop(luaEngine->luaState, 1);
    return true;
  }
  
  if (lua_isnumber(luaEngine->luaState, -1)) {
    double dresult = lua_tonumber(luaEngine->luaState, -1);
    sprintf(strbuf,"%lf", dresult);
    round_lua_engine_setresult(luaEngine, strbuf);
    lua_pop(luaEngine->luaState, 1);
    return true;
  }
  
  return false;
}

#endif

/****************************************
 * round_lua_engine_poperror
 ****************************************/

#if defined(ROUND_SUPPORT_LUA)

bool round_lua_engine_poperror(RoundLuaEngine *luaEngine) {
  int nStack = lua_gettop(luaEngine->luaState);
  if (nStack <= 0)
    return false;
  
  round_lua_engine_seterror(luaEngine, lua_tostring(luaEngine->luaState, -1));
  lua_pop(luaEngine->luaState, 1);
  
  return true;
}

#endif

/****************************************
 * round_lua_engine_run
 ****************************************/

bool round_lua_engine_run(RoundLuaEngine *luaEngine, const char *source, const char *func, const char *param) {
  if (!luaEngine)
    return false;
  
  if (!round_script_engine_clear((RoundScriptEngine *)luaEngine))
    return false;

#if defined(ROUND_SUPPORT_LUA)
  int nStack = lua_gettop(luaEngine->luaState);
  
  if (luaL_loadstring(luaEngine->luaState, source) != 0) {
    round_lua_engine_poperror(luaEngine);
    return false;
  }
  
  nStack = lua_gettop(luaEngine->luaState);
  
  if(lua_pcall(luaEngine->luaState, 0, 0, 0) != 0) {
    round_lua_engine_poperror(luaEngine);
    return false;
  }
  
  nStack = lua_gettop(luaEngine->luaState);
  
  lua_getglobal(luaEngine->luaState, func);
  lua_pushstring(luaEngine->luaState, param);
  
  nStack = lua_gettop(luaEngine->luaState);
  
  int callResult = lua_pcall(luaEngine->luaState, 1, 1, 0);
  nStack = lua_gettop(luaEngine->luaState);
  if (callResult == 0) {
    round_lua_engine_popresult(luaEngine);
  }
  else {
    round_lua_engine_poperror(luaEngine);
  }
  
  nStack = lua_gettop(luaEngine->luaState);
  
  return (callResult == 0) ? true : false;

#else
  
  return false;

#endif
}
