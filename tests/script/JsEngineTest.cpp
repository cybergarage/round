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
#include <round/node_internal.h>
#include <round/script/js.h>

#include "ScriptTestController.h"

#if defined(ROUND_SUPPORT_JS_SM)

BOOST_AUTO_TEST_SUITE(script)

#define SCRIPT_ECHO_LOOP 10
#define SCRIPT_ECHO_EXPR "1 + 2 + 3"
#define SCRIPT_ECHO_RESULT "6"

BOOST_AUTO_TEST_CASE(JavaScriptEngineTest)
{
  RoundJavaScriptEngine* jsEngine;

  jsEngine = round_js_engine_new();
  BOOST_CHECK(jsEngine);

  RoundMethod* method = round_method_new();
  round_method_setname(method, Round::Test::SCRIPT_ECHO_NAME);
  round_method_setstringcode(method, Round::Test::JS_ECHO_CODE);

  RoundString* result = round_string_new();
  RoundError* err = round_error_new();

  for (int n = 0; n < SCRIPT_ECHO_LOOP; n++) {
    BOOST_CHECK(round_js_engine_lock(jsEngine));

    char param[32];
    snprintf(param, sizeof(param), "hello(%d)", n);
    RoundJSONObject* jsonResult;
    BOOST_CHECK(round_js_engine_run(jsEngine, method, param, &jsonResult, err));
    BOOST_CHECK(jsonResult);
    const char* strResult;
    BOOST_CHECK(round_json_object_getstring(jsonResult, &strResult));
    // FIXME "hello(%d)"
    //BOOST_CHECK_EQUAL(strResult, param);

    BOOST_CHECK(round_js_engine_unlock(jsEngine));
  }

  BOOST_CHECK(round_method_delete(method));
  BOOST_CHECK(round_string_delete(result));
  BOOST_CHECK(round_error_delete(err));
  BOOST_CHECK(round_js_engine_delete(jsEngine));
}

BOOST_AUTO_TEST_CASE(JavaScriptEngineEchoTest)
{
  RoundMethodManager* methodMgr = round_method_manager_new();
  BOOST_CHECK(methodMgr);

  RoundJavaScriptEngine* jsEngine = round_js_engine_new();
  BOOST_CHECK(jsEngine);

  BOOST_CHECK(round_method_manager_addengine(methodMgr, (RoundScriptEngine*)jsEngine));

  BOOST_CHECK(round_method_manager_addmethod(methodMgr, Round::Test::CreateTestMethod(Round::Test::SCRIPT_ECHO_NAME, RoundJavaScriptEngineLanguage, Round::Test::JS_ECHO_CODE)));
  BOOST_CHECK(round_method_manager_hasmethod(methodMgr, Round::Test::SCRIPT_ECHO_NAME));

  Round::Test::ScriptTestController scriptTestController;
  scriptTestController.runEchoMethodTest(methodMgr);

  BOOST_CHECK(round_method_manager_delete(methodMgr));
}

BOOST_AUTO_TEST_CASE(JavaScriptEngineSumTest)
{
  RoundMethodManager* methodMgr = round_method_manager_new();
  BOOST_CHECK(methodMgr);

  RoundJavaScriptEngine* jsEngine = round_js_engine_new();
  BOOST_CHECK(jsEngine);

  BOOST_CHECK(round_method_manager_addengine(methodMgr, (RoundScriptEngine*)jsEngine));

  BOOST_CHECK(round_method_manager_addmethod(methodMgr, Round::Test::CreateTestMethod(Round::Test::SCRIPT_SUM_NAME, RoundJavaScriptEngineLanguage, Round::Test::JS_SUM_CODE)));
  BOOST_CHECK(round_method_manager_hasmethod(methodMgr, Round::Test::SCRIPT_SUM_NAME));

  Round::Test::ScriptTestController scriptTestController;
  scriptTestController.runSumMethodTest(methodMgr);

  BOOST_CHECK(round_method_manager_delete(methodMgr));
}

BOOST_AUTO_TEST_CASE(JavaScriptRegistryMethods)
{
  static const char* SETKEY_CODE = "function " RPC_SET_KEY_METHOD_NAME "(params) {return " ROUND_SYSTEM_METHOD_SET_REGISTRY "(params);}";
  static const char* GETKEY_CODE = "function " RPC_GET_KEY_METHOD_NAME "(params) {return " ROUND_SYSTEM_METHOD_GET_REGISTRY "(params);}";
  static const char* REMOVEKEY_CODE = "function " RPC_REMOVE_KEY_METHOD_NAME "(params) {return " ROUND_SYSTEM_METHOD_REMOVE_REGISTRY "(params);}";

  RoundLocalNode* node = round_local_node_new();
  BOOST_CHECK(round_local_node_start(node));

  RoundError* err = round_error_new();

  // Post Node Message (Set '*_key' method)

  BOOST_CHECK(round_node_setmethod((RoundNode*)node, ROUND_SCRIPT_LANGUAGE_JS, RPC_SET_KEY_METHOD_NAME, SETKEY_CODE, err));
  BOOST_CHECK(round_node_setmethod((RoundNode*)node, ROUND_SCRIPT_LANGUAGE_JS, RPC_GET_KEY_METHOD_NAME, GETKEY_CODE, err));
  BOOST_CHECK(round_node_setmethod((RoundNode*)node, ROUND_SCRIPT_LANGUAGE_JS, RPC_REMOVE_KEY_METHOD_NAME, REMOVEKEY_CODE, err));

  // Post Node Message (Run 'set_key' method)

  Round::Test::ScriptTestController scriptTestCtrl;
  scriptTestCtrl.runScriptRegistryMethodTest(node);

  // Clean up

  BOOST_CHECK(round_error_delete(err));

  BOOST_CHECK(round_local_node_stop(node));
  BOOST_CHECK(round_local_node_delete(node));
}

BOOST_AUTO_TEST_SUITE_END()

#endif
