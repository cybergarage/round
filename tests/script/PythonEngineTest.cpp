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
#include <round/script/python.h>
#include "ScriptTestController.h"

#if defined(ROUND_SUPPORT_PYTHON)

BOOST_AUTO_TEST_SUITE(script)
BOOST_AUTO_TEST_SUITE(python)

BOOST_AUTO_TEST_CASE(PythonEngineEcho)
{
#define SCRIPT_ECHO_LOOP 1
#define PY_ECHO_FUNC "echo"
#define PY_ECHO_PARAM "hello"

  const std::string PY_ECHO_CODE = "def " PY_ECHO_FUNC "(params):\n"
                                   "  return params\n";

  RoundPythonEngine* pyEngine = round_python_engine_new();

  RoundMethod* method = round_method_new();
  round_method_setname(method, PY_ECHO_FUNC);
  round_method_setcode(method, (byte*)PY_ECHO_CODE.c_str(), PY_ECHO_CODE.size());

  RoundString* result = round_string_new();
  RoundError* err = round_error_new();

  BOOST_CHECK(pyEngine);

  for (int n = 0; n < SCRIPT_ECHO_LOOP; n++) {
    BOOST_CHECK(round_python_engine_lock(pyEngine));
    BOOST_CHECK(round_python_engine_run(pyEngine, method, PY_ECHO_PARAM, result, err));
    BOOST_CHECK(round_streq(PY_ECHO_PARAM, round_string_getvalue(result)));
    BOOST_CHECK(round_python_engine_unlock(pyEngine));
  }

  BOOST_CHECK(round_method_delete(method));
  BOOST_CHECK(round_string_delete(result));
  BOOST_CHECK(round_error_delete(err));
  BOOST_CHECK(round_python_engine_delete(pyEngine));
}

#define ROUND_SYSTEM_METHOD_PARAM_KEY "key"
#define ROUND_SYSTEM_METHOD_PARAM_VALUE "val"

BOOST_AUTO_TEST_CASE(PythonRegistryMethods)
{
  static const char* SETKEY_CODE = \
    "import json\n" \
    "def " SET_KEY_NAME "(jsonParams):\n" \
    "  params = json.loads(jsonParams)\n" \
    "  return " ROUND_SYSTEM_METHOD_SET_REGISTRY "(params[\"" ROUND_SYSTEM_METHOD_PARAM_KEY "\"], params[\"" ROUND_SYSTEM_METHOD_PARAM_VALUE "\"])\n";
  
  static const char* GETKEY_CODE = \
    "import json\n" \
    "def " SET_KEY_NAME "(jsonParams):\n" \
    "  params = json.loads(jsonParams)\n" \
    "  return " ROUND_SYSTEM_METHOD_GET_REGISTRY "(params[\"" ROUND_SYSTEM_METHOD_PARAM_KEY "\"])\n";
  static const char* REMOVEKEY_CODE = \
    "import json\n" \
    "def " SET_KEY_NAME "(jsonParams):\n" \
    "  params = json.loads(jsonParams)\n" \
    "  return " ROUND_SYSTEM_METHOD_REMOVE_REGISTRY "(params[\"" ROUND_SYSTEM_METHOD_PARAM_KEY "\"])\n";
  
  RoundLocalNode* node = round_local_node_new();
  BOOST_CHECK(round_local_node_start(node));
  
  RoundError* err = round_error_new();
  
  // Post Node Message (Set '*_key' method)
  
  BOOST_CHECK(round_node_setmethod((RoundNode*)node, ROUND_SCRIPT_LANGUAGE_PYTHON, SET_KEY_NAME, SETKEY_CODE, err));
  BOOST_CHECK(round_node_setmethod((RoundNode*)node, ROUND_SCRIPT_LANGUAGE_PYTHON, GET_KEY_NAME, GETKEY_CODE, err));
  BOOST_CHECK(round_node_setmethod((RoundNode*)node, ROUND_SCRIPT_LANGUAGE_PYTHON, REMOVE_KEY_NAME, REMOVEKEY_CODE, err));
  
  // Post Node Message (Run 'set_key' method)
  
  Round::Test::ScriptTestController scriptTestCtrl;
  scriptTestCtrl.runScriptRegistryMethodTest(node);
  
  // Clean up
  
  BOOST_CHECK(round_error_delete(err));
  
  BOOST_CHECK(round_local_node_stop(node));
  BOOST_CHECK(round_local_node_delete(node));
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()

#endif
