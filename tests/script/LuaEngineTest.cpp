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

#if defined(ROUND_SUPPORT_LUA)

BOOST_AUTO_TEST_CASE(LuaEngineTest) {
  #define SCRIPT_ECHO_LOOP 10
  #define LUA_ECHO_FUNC "echo"
  #define LUA_ECHO_PARAM "hello"
  
  const std::string LUA_ECHO_CODE = \
    "function " LUA_ECHO_FUNC "(params)\n"\
    "return params\n"\
    "end";

  RoundLuaEngine *luaEngine;
  
  luaEngine = round_lua_engine_new();
  BOOST_CHECK(luaEngine);
  
  for (int n=0; n<SCRIPT_ECHO_LOOP; n++) {
    BOOST_CHECK(round_lua_engine_lock(luaEngine));
    BOOST_CHECK(round_lua_engine_run(luaEngine, LUA_ECHO_CODE.c_str(), LUA_ECHO_FUNC, LUA_ECHO_PARAM));
    BOOST_CHECK(round_streq(LUA_ECHO_PARAM, round_lua_engine_getresult(luaEngine)));

    BOOST_CHECK(round_lua_engine_unlock(luaEngine));
  }
  
  BOOST_CHECK(round_lua_engine_delete(luaEngine));
}

#endif
