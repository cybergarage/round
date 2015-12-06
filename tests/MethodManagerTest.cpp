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

#include "RoundTest.h"
#include <round/method.h>

BOOST_AUTO_TEST_SUITE(method)

BOOST_AUTO_TEST_CASE(MethodManagerNew)
{
  RoundMethodManager* mgr = round_method_manager_new();
  BOOST_CHECK(mgr);

  BOOST_CHECK_EQUAL(0, round_method_manager_getmethodsize(mgr));
  BOOST_CHECK_EQUAL(0, round_method_manager_getenginsize(mgr));

  RoundMethod* method[ROUND_TEST_MAP_SIZE];
  char name[32];

  RoundScriptEngine* engine[ROUND_TEST_MAP_SIZE];
  char lang[32];

  // Add method & engines

  for (int n = 0; n < ROUND_TEST_MAP_SIZE; n++) {
    method[n] = round_method_new();
    BOOST_CHECK(method[n]);
    BOOST_CHECK(!round_method_manager_addmethod(mgr, method[n]));
    snprintf(name, sizeof(name), "%d", n);
    round_method_setname(method[n], name);
    round_method_setlanguage(method[n], name);
    round_method_setcode(method[n], (byte*)name, (n + 1));
    BOOST_CHECK(round_method_manager_addmethod(mgr, method[n]));
    BOOST_CHECK_EQUAL((n + 1), round_method_manager_getmethodsize(mgr));

    engine[n] = round_script_engine_new();
    BOOST_CHECK(engine[n]);
    BOOST_CHECK(!round_method_manager_addengine(mgr, engine[n]));
    snprintf(lang, sizeof(lang), "%d", n);
    round_script_engine_setlanguage(engine[n], lang);
    BOOST_CHECK(round_method_manager_addengine(mgr, engine[n]));
    BOOST_CHECK_EQUAL((n + 1), round_method_manager_getenginsize(mgr));
  }

  BOOST_CHECK_EQUAL(ROUND_TEST_MAP_SIZE,
                    round_method_manager_getmethodsize(mgr));
  BOOST_CHECK_EQUAL(ROUND_TEST_MAP_SIZE,
                    round_method_manager_getenginsize(mgr));

  // Get method & engines

  for (int n = 0; n < ROUND_TEST_MAP_SIZE; n++) {
    snprintf(name, sizeof(name), "%d", n);
    BOOST_CHECK_EQUAL(method[n], round_method_manager_getmethod(mgr, name));

    snprintf(lang, sizeof(lang), "%d", n);
    BOOST_CHECK_EQUAL(engine[n], round_method_manager_getengine(mgr, lang));
  }

  BOOST_CHECK_EQUAL(ROUND_TEST_MAP_SIZE,
                    round_method_manager_getmethodsize(mgr));
  BOOST_CHECK_EQUAL(ROUND_TEST_MAP_SIZE,
                    round_method_manager_getenginsize(mgr));

  // Remove method & engines

  for (int n = 0; n < ROUND_TEST_MAP_SIZE; n++) {
    snprintf(name, sizeof(name), "%d", n);
    BOOST_CHECK(round_method_manager_removemethod(mgr, name));
    BOOST_CHECK(!round_method_manager_getmethod(mgr, name));
    BOOST_CHECK_EQUAL((ROUND_TEST_MAP_SIZE - (n + 1)), round_method_manager_getmethodsize(mgr));

    snprintf(lang, sizeof(lang), "%d", n);
    BOOST_CHECK(round_method_manager_removeengine(mgr, lang));
    BOOST_CHECK(!round_method_manager_getengine(mgr, lang));
    BOOST_CHECK_EQUAL((ROUND_TEST_MAP_SIZE - (n + 1)), round_method_manager_getenginsize(mgr));
  }

  BOOST_CHECK_EQUAL(0, round_method_manager_getmethodsize(mgr));
  BOOST_CHECK_EQUAL(0, round_method_manager_getenginsize(mgr));

  BOOST_CHECK(round_method_manager_delete(mgr));
}

BOOST_AUTO_TEST_SUITE_END()
