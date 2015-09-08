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
#include <round/script_internal.h>

BOOST_AUTO_TEST_CASE(ScriptManagerNew)
{
  RoundScriptManager *mgr = round_script_manager_new();
  BOOST_CHECK(mgr);
  
  BOOST_CHECK_EQUAL(0, round_script_manager_getscriptsize(mgr));
  BOOST_CHECK_EQUAL(0, round_script_manager_getenginsize(mgr));
  
  RoundScript *script[ROUND_TEST_MAP_SIZE];
  char name[32];
  
  RoundScriptEngine *engine[ROUND_TEST_MAP_SIZE];
  char lang[32];
  
  // Add script & engines
  
  for (int n=0; n<ROUND_TEST_MAP_SIZE; n++) {
    script[n] = round_script_new();
    BOOST_CHECK(!round_script_manager_addscript(mgr, script[n]));
    snprintf(name, sizeof(name), "%d", n);
    round_script_setname(script[n], name);
    round_script_setlanguage(script[n], name);
    round_script_setcode(script[n], (byte *)name, (n+1));
    BOOST_CHECK(round_script_manager_addscript(mgr, script[n]));
    BOOST_CHECK_EQUAL((n+1), round_script_manager_getscriptsize(mgr));

    engine[n] = round_script_engine_new();
    BOOST_CHECK(!round_script_manager_addengine(mgr, engine[n]));
    snprintf(lang, sizeof(lang), "%d", n);
    round_script_engine_setlanguage(engine[n], lang);
    BOOST_CHECK(round_script_manager_addengine(mgr, engine[n]));
    BOOST_CHECK_EQUAL((n+1), round_script_manager_getenginsize(mgr));
  }
  
  BOOST_CHECK_EQUAL(ROUND_TEST_MAP_SIZE, round_script_manager_getscriptsize(mgr));
  BOOST_CHECK_EQUAL(ROUND_TEST_MAP_SIZE, round_script_manager_getenginsize(mgr));
  
  // Get script & engines
  
  for (int n=0; n<ROUND_TEST_MAP_SIZE; n++) {
    snprintf(name, sizeof(name), "%d", n);
    BOOST_CHECK_EQUAL(script[n], round_script_manager_getscript(mgr, name));

    snprintf(lang, sizeof(lang), "%d", n);
    BOOST_CHECK_EQUAL(engine[n], round_script_manager_getengine(mgr, lang));
  }
  
  BOOST_CHECK_EQUAL(ROUND_TEST_MAP_SIZE, round_script_manager_getscriptsize(mgr));
  BOOST_CHECK_EQUAL(ROUND_TEST_MAP_SIZE, round_script_manager_getenginsize(mgr));
  
  // Remove script & engines
  
  for (int n=0; n<ROUND_TEST_MAP_SIZE; n++) {
    snprintf(name, sizeof(name), "%d", n);
    BOOST_CHECK(round_script_manager_removescript(mgr, name));
    BOOST_CHECK(!round_script_manager_getscript(mgr, name));
    BOOST_CHECK_EQUAL((ROUND_TEST_MAP_SIZE-(n+1)), round_script_manager_getscriptsize(mgr));

    snprintf(lang, sizeof(lang), "%d", n);
    BOOST_CHECK(round_script_manager_removeengine(mgr, lang));
    BOOST_CHECK(!round_script_manager_getengine(mgr, lang));
    BOOST_CHECK_EQUAL((ROUND_TEST_MAP_SIZE-(n+1)), round_script_manager_getenginsize(mgr));
  }
  
  BOOST_CHECK_EQUAL(0, round_script_manager_getscriptsize(mgr));
  BOOST_CHECK_EQUAL(0, round_script_manager_getenginsize(mgr));
  
  BOOST_CHECK(round_script_manager_delete(mgr));
}
