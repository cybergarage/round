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

#if defined(ROUND_SUPPORT_PYTHON)

BOOST_AUTO_TEST_SUITE(script)

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

BOOST_AUTO_TEST_SUITE_END()

#endif
