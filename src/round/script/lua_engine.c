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

RoundLuaEngine *round_lua_engine_new()
{
  RoundLuaEngine *engine;
  
  engine = (RoundLuaEngine *)calloc(1, sizeof(RoundLuaEngine));
  if (!engine)
    return NULL;

  if (!round_script_engine_init((RoundScriptEngine *)engine)) {
    round_lua_engine_delete(engine);
    return NULL;
  }

  round_script_engine_setexecutefunc(engine, round_lua_engine_run);
  round_script_engine_setdestructor(engine, round_lua_engine_delete);
  
#if defined(ROUND_SUPPORT_LUA)
  engine->luaState = luaL_newstate();
  luaL_openlibs(engine->luaState);
#endif
  
  return engine;
}

/****************************************
 * round_lua_engine_delete
 ****************************************/

bool round_lua_engine_delete(RoundLuaEngine *engine)
{
  if (!engine)
    return false;
  
  if (!round_script_engine_destory((RoundScriptEngine *)engine))
    return false;
  
  free(engine);
  
  return true;
}

/****************************************
 * round_lua_engine_register
 ****************************************/

#if defined(ROUND_SUPPORT_LUA)

bool round_lua_engine_register(RoundLuaEngine *engine, const char *name, lua_CFunction func)
{
  lua_register(engine->luaState, name, func);
  return true;
}

#endif

/****************************************
 * round_lua_engine_popresult
 ****************************************/

#if defined(ROUND_SUPPORT_LUA)

bool round_lua_engine_popresult(RoundLuaEngine *engine, RoundString *result)
{
  char strbuf[128];
  
  int nStack = lua_gettop(engine->luaState);
  if (nStack <= 0)
    return false;
  
  if (lua_isstring(engine->luaState, -1)) {
    round_string_setvalue(result, lua_tostring(engine->luaState, -1));
    lua_pop(engine->luaState, 1);
    return true;
  }
  
  if (lua_isboolean(engine->luaState, -1)) {
    round_string_setvalue(result, lua_toboolean(engine->luaState, -1) ? "true" : "false");
    lua_pop(engine->luaState, 1);
    return true;
  }
  
  if (lua_isnumber(engine->luaState, -1)) {
    double dresult = lua_tonumber(engine->luaState, -1);
    sprintf(strbuf,"%lf", dresult);
    round_string_setvalue(result, strbuf);
    lua_pop(engine->luaState, 1);
    return true;
  }
  
  return false;
}

#endif

/****************************************
 * round_lua_engine_poperror
 ****************************************/

#if defined(ROUND_SUPPORT_LUA)

bool round_lua_engine_poperror(RoundLuaEngine *engine, RoundError *err)
{
  int nStack = lua_gettop(engine->luaState);
  if (nStack <= 0)
    return false;
  
  round_error_setjsonrpcerrorcode(err, ROUNDC_RPC_ERROR_CODE_SCRIPT_RUNTIME_ERROR);
  round_error_setdetailmessage(err, lua_tostring(engine->luaState, -1));
  
  lua_pop(engine->luaState, 1);
  
  return true;
}

#endif

/****************************************
 * round_lua_engine_run
 ****************************************/

//bool round_lua_engine_run(RoundLuaEngine *engine, const char *source, const char *func, const char *param) {
bool round_lua_engine_run(RoundLuaEngine *engine, RoundScript *script, const char *param, RoundString *result, RoundError *err)
{
  const char *source;
  const char *method;
  
  if (!engine)
    return false;
  
  source = round_script_getsource(script);
  method = round_script_getname(script);
  
#if defined(ROUND_SUPPORT_LUA)
  int nStack = lua_gettop(engine->luaState);
  
  if (luaL_loadstring(engine->luaState, source) != 0) {
    round_lua_engine_poperror(engine, err);
    return false;
  }
  
  nStack = lua_gettop(engine->luaState);
  
  if(lua_pcall(engine->luaState, 0, 0, 0) != 0) {
    round_lua_engine_poperror(engine, err);
    return false;
  }
  
  nStack = lua_gettop(engine->luaState);
  
  lua_getglobal(engine->luaState, method);
  lua_pushstring(engine->luaState, param);
  
  nStack = lua_gettop(engine->luaState);
  
  int callResult = lua_pcall(engine->luaState, 1, 1, 0);
  nStack = lua_gettop(engine->luaState);
  if (callResult == 0) {
    round_lua_engine_popresult(engine, result);
  }
  else {
    round_lua_engine_poperror(engine, err);
  }
  
  nStack = lua_gettop(engine->luaState);
  
  return (callResult == 0) ? true : false;

#else
  
  return false;

#endif
}
