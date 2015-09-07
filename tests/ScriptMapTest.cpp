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

BOOST_AUTO_TEST_CASE(ScriptListMap)
{
  RoundScriptMap *map = round_script_map_new();
  
  BOOST_CHECK(map);
  BOOST_CHECK_EQUAL(0, round_script_map_size(map));
  
  RoundScript *script[ROUND_TEST_LIST_CNT];
  for (int n=0; n<ROUND_TEST_LIST_CNT; n++) {
    script[n] = round_script_new();
    BOOST_CHECK(round_script_map_set(map, script[n]));
    BOOST_CHECK_EQUAL((n+1), round_script_map_size(map));
  }
  
  BOOST_CHECK_EQUAL(ROUND_TEST_LIST_CNT, round_script_map_size(map));
  
  BOOST_CHECK(round_script_map_delete(map));
}
