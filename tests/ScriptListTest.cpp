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

BOOST_AUTO_TEST_CASE(ScriptListAdd)
{
  RoundScriptList *scripts = round_scriptlist_new();
  
  BOOST_CHECK(scripts);
  BOOST_CHECK_EQUAL(0, round_scriptlist_size(scripts));
  
  RoundScript *script[ROUND_TEST_LIST_CNT];
  for (int n=0; n<ROUND_TEST_LIST_CNT; n++) {
    script[n] = round_script_new();
    BOOST_CHECK(round_scriptlist_add(scripts, script[n]));
    BOOST_CHECK_EQUAL((n+1), round_scriptlist_size(scripts));
  }
  
  BOOST_CHECK_EQUAL(ROUND_TEST_LIST_CNT, round_scriptlist_size(scripts));
  
  BOOST_CHECK(round_scriptlist_delete(scripts));
}
