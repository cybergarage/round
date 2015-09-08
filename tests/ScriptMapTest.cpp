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
  
  RoundScript *script[ROUND_TEST_MAP_SIZE];
  char name[32];

  // Add scripts
  
  for (int n=0; n<ROUND_TEST_MAP_SIZE; n++) {
    script[n] = round_script_new();
    BOOST_CHECK(!round_script_map_set(map, script[n]));
    snprintf(name, sizeof(name), "%d", n);
    round_script_setname(script[n], name);
    BOOST_CHECK(round_script_map_set(map, script[n]));
    BOOST_CHECK_EQUAL((n+1), round_script_map_size(map));
  }
  
  BOOST_CHECK_EQUAL(ROUND_TEST_MAP_SIZE, round_script_map_size(map));

  // Get scripts
  
  for (int n=0; n<ROUND_TEST_MAP_SIZE; n++) {
    snprintf(name, sizeof(name), "%d", n);
    BOOST_CHECK_EQUAL(script[n], round_script_map_get(map, name));
  }
  
  BOOST_CHECK_EQUAL(ROUND_TEST_MAP_SIZE, round_script_map_size(map));

  // Remove scripts
  
  for (int n=0; n<ROUND_TEST_MAP_SIZE; n++) {
    snprintf(name, sizeof(name), "%d", n);
    BOOST_CHECK(round_script_map_remove(map, name));
    BOOST_CHECK(!round_script_map_get(map, name));
    BOOST_CHECK_EQUAL((ROUND_TEST_MAP_SIZE-(n+1)), round_script_map_size(map));
  }
  
  BOOST_CHECK_EQUAL(0, round_script_map_size(map));
  
  BOOST_CHECK(round_script_map_delete(map));
}
