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

#include "RoundTest.h"
#include "ScriptTestController.h"

#if defined(ROUND_SUPPORT_PYTHON)

BOOST_AUTO_TEST_SUITE(script)
BOOST_AUTO_TEST_SUITE(python)

#define PY_ECHO_PARAM "hello"

static const char *PY_ECHO_CODE = \
  "def " RPC_METHOD_HELLO_NAME "(params):\n" \
  "  return params\n";

static const char* PY_SETKEY_CODE = \
  "import round\n" \
  "import json\n" \
  "def " RPC_METHOD_SET_KEY_NAME "(jsonParams):\n" \
  "  try:\n" \
  "    params = json.loads(jsonParams)\n" \
  "    return " ROUND_MODULE_NAME "." ROUND_SYSTEM_METHOD_SET_REGISTRY "(params[\"" ROUND_SYSTEM_METHOD_PARAM_KEY "\"], params[\"" ROUND_SYSTEM_METHOD_PARAM_VALUE "\"])\n" \
  "  except:\n" \
  "    return False\n";

static const char* PY_GETKEY_CODE = \
  "import round\n" \
  "import json\n" \
  "def " RPC_METHOD_GET_KEY_NAME "(jsonParams):\n" \
  "  try:\n" \
  "    params = json.loads(jsonParams)\n" \
  "    return " ROUND_MODULE_NAME "." ROUND_SYSTEM_METHOD_GET_REGISTRY "(params[\"" ROUND_SYSTEM_METHOD_PARAM_KEY "\"])\n" \
  "  except:\n" \
  "    return \"\"\n";

static const char* PY_REMOVEKEY_CODE = \
  "import round\n" \
  "import json\n" \
  "def " RPC_METHOD_REMOVE_KEY_NAME "(jsonParams):\n" \
  "  try:\n" \
  "    params = json.loads(jsonParams)\n" \
  "    return " ROUND_MODULE_NAME "." ROUND_SYSTEM_METHOD_REMOVE_REGISTRY "(params[\"" ROUND_SYSTEM_METHOD_PARAM_KEY "\"])\n" \
  "  except:\n" \
  "    return False\n";

static const char* PY_GETNODEID_CODE = \
"import round\n" \
"def " RPC_METHOD_GET_NODE_ID "(jsonParams):\n" \
"  try:\n" \
"    node = " ROUND_MODULE_NAME "." ROUND_SYSTEM_METHOD_GET_NODE_STATE "()\n" \
"    return node[\"" ROUND_SYSTEM_METHOD_PARAM_ID "\"]\n" \
"  except:\n" \
"    return False\n";

static const char* PY_GETCLUSTERNODESIZE_CODE = \
"import round\n" \
"def " RPC_METHOD_GET_CLUSTER_NODE_SIZE "(jsonParams):\n" \
"  try:\n" \
"    clusters = " ROUND_MODULE_NAME "." ROUND_SYSTEM_METHOD_GET_CLUSTER_STATE "()\n" \
"    return len(clusters)\n" \
"  except:\n" \
"    return False\n";

BOOST_AUTO_TEST_CASE(PythonCompileHello)
{
  RoundPythonEngine* pyEngine = round_python_engine_new();
  BOOST_CHECK(pyEngine);
  
  RoundError* err = round_error_new();
  
  PyObject* pModule;
  BOOST_CHECK(round_python_engine_compile(pyEngine, RPC_METHOD_HELLO_NAME, PY_ECHO_CODE, err, &pModule));
  
  PyObject* pFunc;
  BOOST_CHECK(round_python_engine_getfunctionbyname(pyEngine, pModule, RPC_METHOD_HELLO_NAME, err, &pFunc));
  
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
    
    BOOST_CHECK(round_python_engine_compile(pyEngine, RPC_METHOD_SET_KEY_NAME, PY_SETKEY_CODE, err, &pModule));
    BOOST_CHECK(round_python_engine_getfunctionbyname(pyEngine, pModule, RPC_METHOD_SET_KEY_NAME, err, &pFunc));

    BOOST_CHECK(round_python_engine_compile(pyEngine, RPC_METHOD_GET_KEY_NAME, PY_GETKEY_CODE, err, &pModule));
    BOOST_CHECK(round_python_engine_getfunctionbyname(pyEngine, pModule, RPC_METHOD_GET_KEY_NAME, err, &pFunc));

    BOOST_CHECK(round_python_engine_compile(pyEngine, RPC_METHOD_REMOVE_KEY_NAME, PY_REMOVEKEY_CODE, err, &pModule));
    BOOST_CHECK(round_python_engine_getfunctionbyname(pyEngine, pModule, RPC_METHOD_REMOVE_KEY_NAME, err, &pFunc));
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
  round_method_setname(method, RPC_METHOD_HELLO_NAME);
  round_method_setstringcode(method, PY_ECHO_CODE);

  RoundJSONObject* resObj;
  const char *resStr;
  RoundError* err = round_error_new();

  for (int n = 0; n < SCRIPT_ECHO_LOOP; n++) {
    BOOST_CHECK(round_python_engine_run(pyEngine, method, PY_ECHO_PARAM, &resObj, err));
    BOOST_CHECK(resObj);
    BOOST_CHECK(round_json_object_tostring(resObj, &resStr));
    BOOST_CHECK(round_streq(PY_ECHO_PARAM, resStr));
    if (resObj) {
      round_json_object_delete(resObj);
    }
  }

  BOOST_CHECK(round_method_delete(method));
  BOOST_CHECK(round_error_delete(err));
  BOOST_CHECK(round_python_engine_delete(pyEngine));
}

BOOST_AUTO_TEST_CASE(PythonRegistryMethods)
{
  RoundLocalNode* node = round_local_node_new();
  BOOST_CHECK(round_local_node_start(node));
  
  RoundError* err = round_error_new();
  
  // Post Node Message (Set '*_key' method)
  
  BOOST_CHECK(round_node_setmethod((RoundNode*)node, ROUND_SCRIPT_LANGUAGE_PYTHON, RPC_METHOD_SET_KEY_NAME, PY_SETKEY_CODE, err));
  BOOST_CHECK(round_node_setmethod((RoundNode*)node, ROUND_SCRIPT_LANGUAGE_PYTHON, RPC_METHOD_GET_KEY_NAME, PY_GETKEY_CODE, err));
  BOOST_CHECK(round_node_setmethod((RoundNode*)node, ROUND_SCRIPT_LANGUAGE_PYTHON, RPC_METHOD_REMOVE_KEY_NAME, PY_REMOVEKEY_CODE, err));
  
  // Run Methods
  
  Round::Test::ScriptTestController scriptTestCtrl;
  scriptTestCtrl.runScriptRegistryMethodTest(node);
  
  // Clean up
  
  BOOST_CHECK(round_error_delete(err));
  
  BOOST_CHECK(round_local_node_stop(node));
  BOOST_CHECK(round_local_node_delete(node));
}

BOOST_AUTO_TEST_CASE(PythonGetNodeStatus)
{
  RoundLocalNode* node = round_local_node_new();
  round_local_node_setaddress(node, ROUND_TEST_ADDR);
  round_local_node_setport(node, ROUND_TEST_PORT);
  
  BOOST_CHECK(round_local_node_start(node));
  
  RoundError* err = round_error_new();
  
  // Post Node Message (Set '*_key' method)
  
  BOOST_CHECK(round_node_setmethod((RoundNode*)node, ROUND_SCRIPT_LANGUAGE_PYTHON, RPC_METHOD_GET_NODE_ID, PY_GETNODEID_CODE, err));
  BOOST_CHECK(round_node_setmethod((RoundNode*)node, ROUND_SCRIPT_LANGUAGE_PYTHON, PY_GETCLUSTERNODESIZE_CODE, PY_GETNODEID_CODE, err));
  
  // Run Methods
  
  Round::Test::ScriptTestController scriptTestCtrl;
  scriptTestCtrl.runScriptStatusTest(node);
  
  // Clean up
  
  BOOST_CHECK(round_error_delete(err));
  
  BOOST_CHECK(round_local_node_stop(node));
  BOOST_CHECK(round_local_node_delete(node));
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()

#endif
