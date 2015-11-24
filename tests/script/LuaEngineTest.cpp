/******************************************************************
 *
 * Round for C
 *
 * Copyright (C) Satoshi Konno 2015
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <boost/test/unit_test.hpp>
#include <string>
#include <round/script/lua.h>

BOOST_AUTO_TEST_CASE(LuaEngineTest)
{
  #define SCRIPT_ECHO_LOOP 10
  #define LUA_ECHO_FUNC "echo"
  #define LUA_ECHO_PARAM "hello"
  
  const std::string LUA_ECHO_CODE = \
    "function " LUA_ECHO_FUNC "(params)\n"\
    "return params\n"\
    "end";

  RoundLuaEngine *luaEngine = round_lua_engine_new();
  
  RoundMethod *method = round_method_new();
  round_method_setname(method, LUA_ECHO_FUNC);
  round_method_setcode(method, (byte *)LUA_ECHO_CODE.c_str(), LUA_ECHO_CODE.size());

  RoundString *result = round_string_new();
  RoundError *err = round_error_new();
  
  BOOST_CHECK(luaEngine);

  bool round_lua_engine_run(RoundLuaEngine *engine, RoundMethod *method, const char *param, RoundString *result, RoundError *err);

  for (int n=0; n<SCRIPT_ECHO_LOOP; n++) {
    BOOST_CHECK(round_lua_engine_lock(luaEngine));
    BOOST_CHECK(round_lua_engine_run(luaEngine, method, LUA_ECHO_PARAM, result, err));
    BOOST_CHECK(round_streq(LUA_ECHO_PARAM, round_string_getvalue(result)));
    BOOST_CHECK(round_lua_engine_unlock(luaEngine));
  }
  
  BOOST_CHECK(round_method_delete(method));
  BOOST_CHECK(round_string_delete(result));
  BOOST_CHECK(round_error_delete(err));
  BOOST_CHECK(round_lua_engine_delete(luaEngine));
}
