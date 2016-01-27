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

#include "ScriptTestController.h"

#if defined(ROUND_SUPPORT_LUA)

BOOST_AUTO_TEST_SUITE(script)
BOOST_AUTO_TEST_SUITE(lua)

static const char *LUA_ECHO_CODE = "function " RPC_HELLO_METHOD_NAME "(params)\n"
  "return params\n"
  "end";

static const char* LUA_SETKEY_CODE = \
  "json = require(\"json\") -- JSON4Lua\n" \
  "function " RPC_SET_KEY_METHOD_NAME "(jsonParams)" \
  "  params = json.decode(jsonParams)\n" \
  "  return " ROUND_SYSTEM_METHOD_SET_REGISTRY "(params[\"" ROUND_SYSTEM_METHOD_PARAM_KEY "\"], params[\"" ROUND_SYSTEM_METHOD_PARAM_VALUE "\"])\n" \
  "end\n";
static const char* LUA_GETKEY_CODE = \
  "json = require(\"json\") -- JSON4Lua\n" \
  "function " RPC_GET_KEY_METHOD_NAME "(jsonParams)" \
  "  params = json.decode(jsonParams)\n" \
  "  return " ROUND_SYSTEM_METHOD_REMOVE_REGISTRY "(params[\"" ROUND_SYSTEM_METHOD_PARAM_KEY "\"])\n" \
  "end\n";
static const char* LUA_REMOVEKEY_CODE = \
  "json = require(\"json\") -- JSON4Lua\n" \
  "function " RPC_REMOVE_KEY_METHOD_NAME "(jsonParams):\n" \
  "  params = json.decode(jsonParams)\n" \
  "  return " ROUND_SYSTEM_METHOD_REMOVE_REGISTRY "(params[\"" ROUND_SYSTEM_METHOD_PARAM_KEY "\"])\n" \
  "end\n";

BOOST_AUTO_TEST_CASE(LuaEngineTest)
{
#define SCRIPT_ECHO_LOOP 10
#define LUA_ECHO_PARAM "hello"

  RoundLuaEngine* luaEngine = round_lua_engine_new();

  RoundMethod* method = round_method_new();
  round_method_setname(method, RPC_HELLO_METHOD_NAME);
  round_method_setstringcode(method, LUA_ECHO_CODE);

  RoundJSONObject* resObj;
  const char *resStr;
  RoundError* err = round_error_new();

  BOOST_CHECK(luaEngine);

  for (int n = 0; n < SCRIPT_ECHO_LOOP; n++) {
    BOOST_CHECK(round_lua_engine_run(luaEngine, method, LUA_ECHO_PARAM, &resObj, err));
    BOOST_CHECK(resObj);
    BOOST_CHECK(round_json_object_tostring(resObj, &resStr));
    BOOST_CHECK(round_streq(LUA_ECHO_PARAM, resStr));
    if (resObj) {
      round_json_object_delete(resObj);
    }
  }

  BOOST_CHECK(round_method_delete(method));
  BOOST_CHECK(round_error_delete(err));
  BOOST_CHECK(round_lua_engine_delete(luaEngine));
}

BOOST_AUTO_TEST_CASE(LuaRegistryMethods)
{
  RoundLocalNode* node = round_local_node_new();
  BOOST_CHECK(round_local_node_start(node));
  
  RoundError* err = round_error_new();
  
  // Post Node Message (Set 'hello' method)
  
  BOOST_CHECK(round_node_setmethod((RoundNode*)node, ROUND_SCRIPT_LANGUAGE_LUA, RPC_HELLO_METHOD_NAME, LUA_ECHO_CODE, err));
  
  // Post Node Message (Set '*_key' method)
  
  BOOST_CHECK(round_node_setmethod((RoundNode*)node, ROUND_SCRIPT_LANGUAGE_LUA, RPC_SET_KEY_METHOD_NAME, LUA_SETKEY_CODE, err));
  BOOST_CHECK(round_node_setmethod((RoundNode*)node, ROUND_SCRIPT_LANGUAGE_LUA, RPC_GET_KEY_METHOD_NAME, LUA_GETKEY_CODE, err));
  BOOST_CHECK(round_node_setmethod((RoundNode*)node, ROUND_SCRIPT_LANGUAGE_LUA, RPC_REMOVE_KEY_METHOD_NAME, LUA_REMOVEKEY_CODE, err));
  
  // Run Methods
  
  Round::Test::ScriptTestController scriptTestCtrl;
  scriptTestCtrl.runScriptMethodTest(node);
  
  // Clean up
  
  BOOST_CHECK(round_error_delete(err));
  
  BOOST_CHECK(round_local_node_stop(node));
  BOOST_CHECK(round_local_node_delete(node));
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()

#endif
