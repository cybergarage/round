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

#if defined(ROUND_SUPPORT_JS_SM)

BOOST_AUTO_TEST_CASE(JavaScriptEngineTest) {
  #define SCRIPT_ECHO_LOOP 10
  #define SCRIPT_ECHO_EXPR "1 + 2 + 3"
  #define SCRIPT_ECHO_RESULT "6"
  static const std::string SCRIPT_ECHO_SCRIPT = "var result = " SCRIPT_ECHO_EXPR ";\nresult;";
  
  RoundJavaScriptEngine *jsEngine;
  
  jsEngine = round_js_engine_new();
  BOOST_CHECK(jsEngine);
  
  for (int n=0; n<SCRIPT_ECHO_LOOP; n++) {
    BOOST_CHECK(round_js_engine_lock(jsEngine));
    BOOST_CHECK(round_js_engine_run(jsEngine, SCRIPT_ECHO_SCRIPT.c_str()));
    BOOST_CHECK(round_streq(SCRIPT_ECHO_RESULT, round_js_engine_getresult(jsEngine)));
    BOOST_CHECK(round_js_engine_unlock(jsEngine));
  }
  
  BOOST_CHECK(round_js_engine_delete(jsEngine));
}

#endif
