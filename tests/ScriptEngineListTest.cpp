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

BOOST_AUTO_TEST_CASE(ScriptEngineListAdd)
{
  RoundScriptEngineList *engines = round_script_enginelist_new();

  BOOST_CHECK(engines);
  BOOST_CHECK_EQUAL(0, round_script_enginelist_size(engines));
  
  RoundScriptEngine *engine[ROUND_TEST_LIST_CNT];
  for (int n=0; n<ROUND_TEST_LIST_CNT; n++) {
    engine[n] = round_script_engine_new();
    BOOST_CHECK(round_script_enginelist_add(engines, engine[n]));
    BOOST_CHECK_EQUAL((n+1), round_script_enginelist_size(engines));
  }

  BOOST_CHECK_EQUAL(ROUND_TEST_LIST_CNT, round_script_enginelist_size(engines));
  
  BOOST_CHECK(round_script_enginelist_delete(engines));
}
