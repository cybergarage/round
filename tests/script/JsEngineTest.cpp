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
#include <round/script/js.h>

#include "ScriptTestController.h"

#if defined(ROUND_SUPPORT_JS_SM)

BOOST_AUTO_TEST_CASE(JavaScriptEngineTest) {
  #define SCRIPT_ECHO_LOOP 10
  #define SCRIPT_ECHO_EXPR "1 + 2 + 3"
  #define SCRIPT_ECHO_RESULT "6"
  static const std::string SCRIPT_ECHO_SCRIPT = "var result = " SCRIPT_ECHO_EXPR ";\nresult;";
  
  RoundJavaScriptEngine *jsEngine;
  
  jsEngine = round_js_engine_new();
  BOOST_CHECK(jsEngine);
  
  RoundMethod *method = round_method_new();
  /*
  round_method_setname(method, LUA_ECHO_FUNC);
  round_method_setcode(method, (byte *)LUA_ECHO_CODE.c_str(), LUA_ECHO_CODE.size());
   */
  
  RoundString *result = round_string_new();
  RoundError *err = round_error_new();
  
  for (int n=0; n<SCRIPT_ECHO_LOOP; n++) {
    BOOST_CHECK(round_js_engine_lock(jsEngine));
   /*
    BOOST_CHECK(round_js_engine_run(jsEngine, SCRIPT_ECHO_SCRIPT.c_str()));
    BOOST_CHECK(round_streq(SCRIPT_ECHO_RESULT, round_js_engine_getresult(jsEngine)));
   */
    BOOST_CHECK(round_js_engine_unlock(jsEngine));
  }
  
  BOOST_CHECK(round_method_delete(method));
  BOOST_CHECK(round_string_delete(result));
  BOOST_CHECK(round_error_delete(err));
  BOOST_CHECK(round_js_engine_delete(jsEngine));
}

BOOST_AUTO_TEST_CASE(JavaScriptEngineEchoTest)
{
  RoundMethodManager *methodMgr = round_method_manager_new();
  BOOST_CHECK(methodMgr);
  
  RoundJavaScriptEngine *jsEngine = round_js_engine_new();
  BOOST_CHECK(jsEngine);

  BOOST_CHECK(round_method_manager_addengine(methodMgr, (RoundScriptEngine *)jsEngine));
    
  //BOOST_CHECK(scriptMgr.setScript(Test::SCRIPT_ECHO_NAME, JavaScriptEngine::LANGUAGE, Round::Test::JS_ECHO_CODE, Script::ENCODING_NONE, &err));
  //BOOST_CHECK(scriptMgr.hasScript(Test::SCRIPT_ECHO_NAME));
  
  Round::Test::ScriptTestController scriptTestController;
  scriptTestController.runEchoMethodTest(methodMgr);

  BOOST_CHECK(round_js_engine_delete(jsEngine));
  BOOST_CHECK(round_method_manager_delete(methodMgr));
}

BOOST_AUTO_TEST_CASE(JavaScriptEngineSumTest)
{
  RoundMethodManager *methodMgr = round_method_manager_new();
  BOOST_CHECK(methodMgr);
  
  RoundJavaScriptEngine *jsEngine = round_js_engine_new();
  BOOST_CHECK(jsEngine);
  
  BOOST_CHECK(round_method_manager_addengine(methodMgr, (RoundScriptEngine *)jsEngine));
  
  //BOOST_CHECK(scriptMgr.setScript(new Script(JavaScriptEngine::LANGUAGE, Test::SCRIPT_SUM_NAME, Test::JS_SUM_CODE)));
  //BOOST_CHECK(scriptMgr.hasScript(Test::SCRIPT_SUM_NAME));
  
  Round::Test::ScriptTestController scriptTestController;
  scriptTestController.runSumMethodTest(methodMgr);
  
  BOOST_CHECK(round_js_engine_delete(jsEngine));
  BOOST_CHECK(round_method_manager_delete(methodMgr));
}

#endif
