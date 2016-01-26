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

#define PY_ECHO_PARAM "hello"

static const char *PY_ECHO_CODE = \
  "def " RPC_HELLO_METHOD_NAME "(params):\n" \
  "  return params\n";

static const char* PY_SETKEY_CODE = \
  "import round\n" \
  "import json\n" \
  "def " RPC_SET_KEY_METHOD_NAME "(jsonParams):\n" \
  "  params = json.loads(jsonParams)\n" \
  "  return round." ROUND_SYSTEM_METHOD_SET_REGISTRY "(params[\"" ROUND_SYSTEM_METHOD_PARAM_KEY "\"], params[\"" ROUND_SYSTEM_METHOD_PARAM_VALUE "\"])\n";
static const char* PY_GETKEY_CODE = \
  "import round\n" \
  "import json\n" \
  "def " RPC_GET_KEY_METHOD_NAME "(jsonParams):\n" \
  "  params = json.loads(jsonParams)\n" \
  "  return round." ROUND_SYSTEM_METHOD_REMOVE_REGISTRY "(params[\"" ROUND_SYSTEM_METHOD_PARAM_KEY "\"])\n";
static const char* PY_REMOVEKEY_CODE = \
  "import round\n" \
  "import json\n" \
  "def " RPC_REMOVE_KEY_METHOD_NAME "(jsonParams):\n" \
  "  params = json.loads(jsonParams)\n" \
  "  return round." ROUND_SYSTEM_METHOD_REMOVE_REGISTRY "(params[\"" ROUND_SYSTEM_METHOD_PARAM_KEY "\"])\n";

BOOST_AUTO_TEST_CASE(PythonCompileHello)
{
  RoundPythonEngine* pyEngine = round_python_engine_new();
  BOOST_CHECK(pyEngine);
  
  RoundError* err = round_error_new();
  
  PyObject* pModule;
  BOOST_CHECK(round_python_engine_compile(pyEngine, RPC_HELLO_METHOD_NAME, PY_ECHO_CODE, err, &pModule));
  
  PyObject* pFunc;
  BOOST_CHECK(round_python_engine_getfunctionbyname(pyEngine, pModule, RPC_HELLO_METHOD_NAME, err, &pFunc));
  
  BOOST_CHECK(round_error_delete(err));
  BOOST_CHECK(round_python_engine_delete(pyEngine));
}

BOOST_AUTO_TEST_CASE(PythonCompileSetKey)
{
#define SCRIPT_COMPILE_LOOP 10
  
  RoundPythonEngine* pyEngine = round_python_engine_new();
  BOOST_CHECK(pyEngine);
  
  RoundError* err = round_error_new();
  
  for (int n = 0; n < SCRIPT_COMPILE_LOOP; n++) {
    PyObject* pModule, *pFunc;
    
    BOOST_CHECK(round_python_engine_compile(pyEngine, RPC_SET_KEY_METHOD_NAME, PY_SETKEY_CODE, err, &pModule));
    BOOST_CHECK(round_python_engine_getfunctionbyname(pyEngine, pModule, RPC_SET_KEY_METHOD_NAME, err, &pFunc));

    BOOST_CHECK(round_python_engine_compile(pyEngine, RPC_GET_KEY_METHOD_NAME, PY_GETKEY_CODE, err, &pModule));
    BOOST_CHECK(round_python_engine_getfunctionbyname(pyEngine, pModule, RPC_GET_KEY_METHOD_NAME, err, &pFunc));

    BOOST_CHECK(round_python_engine_compile(pyEngine, RPC_REMOVE_KEY_METHOD_NAME, PY_REMOVEKEY_CODE, err, &pModule));
    BOOST_CHECK(round_python_engine_getfunctionbyname(pyEngine, pModule, RPC_REMOVE_KEY_METHOD_NAME, err, &pFunc));
}
  
  BOOST_CHECK(round_error_delete(err));
  BOOST_CHECK(round_python_engine_delete(pyEngine));
}

BOOST_AUTO_TEST_CASE(PythonEngineEcho)
{
#define SCRIPT_ECHO_LOOP 10

  RoundPythonEngine* pyEngine = round_python_engine_new();
  BOOST_CHECK(pyEngine);

  RoundMethod* method = round_method_new();
  round_method_setname(method, RPC_HELLO_METHOD_NAME);
  round_method_setstringcode(method, PY_ECHO_CODE);

  RoundString* result = round_string_new();
  RoundError* err = round_error_new();

  for (int n = 0; n < SCRIPT_ECHO_LOOP; n++) {
    BOOST_CHECK(round_python_engine_run(pyEngine, method, PY_ECHO_PARAM, result, err));
    BOOST_CHECK(round_streq(PY_ECHO_PARAM, round_string_getvalue(result)));
  }

  BOOST_CHECK(round_method_delete(method));
  BOOST_CHECK(round_string_delete(result));
  BOOST_CHECK(round_error_delete(err));
  BOOST_CHECK(round_python_engine_delete(pyEngine));
}

BOOST_AUTO_TEST_CASE(PythonRegistryMethods)
{
  RoundLocalNode* node = round_local_node_new();
  BOOST_CHECK(round_local_node_start(node));
  
  RoundError* err = round_error_new();
  
  // Post Node Message (Set '*_key' method)
  
  BOOST_CHECK(round_node_setmethod((RoundNode*)node, ROUND_SCRIPT_LANGUAGE_PYTHON, RPC_SET_KEY_METHOD_NAME, PY_SETKEY_CODE, err));
  BOOST_CHECK(round_node_setmethod((RoundNode*)node, ROUND_SCRIPT_LANGUAGE_PYTHON, RPC_GET_KEY_METHOD_NAME, PY_GETKEY_CODE, err));
  BOOST_CHECK(round_node_setmethod((RoundNode*)node, ROUND_SCRIPT_LANGUAGE_PYTHON, RPC_REMOVE_KEY_METHOD_NAME, PY_REMOVEKEY_CODE, err));
  
  // Run Methods
  
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
