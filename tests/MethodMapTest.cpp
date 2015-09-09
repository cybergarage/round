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
#include <round/method_internal.h>

BOOST_AUTO_TEST_CASE(MethodMap)
{
  RoundMap *map = round_method_map_new();
  
  BOOST_CHECK(map);
  BOOST_CHECK_EQUAL(0, round_method_map_size(map));
  
  RoundMethod *method[ROUND_TEST_MAP_SIZE];
  char name[32];

  // Add methods
  
  for (int n=0; n<ROUND_TEST_MAP_SIZE; n++) {
    method[n] = round_method_new();
    BOOST_CHECK(method[n]);
    BOOST_CHECK(!round_method_map_set(map, method[n]));
    snprintf(name, sizeof(name), "%d", n);
    round_method_setname(method[n], name);
    BOOST_CHECK(round_method_map_set(map, method[n]));
    BOOST_CHECK_EQUAL((n+1), round_method_map_size(map));
  }
  
  BOOST_CHECK_EQUAL(ROUND_TEST_MAP_SIZE, round_method_map_size(map));

  // Get methods
  
  for (int n=0; n<ROUND_TEST_MAP_SIZE; n++) {
    snprintf(name, sizeof(name), "%d", n);
    BOOST_CHECK_EQUAL(method[n], round_method_map_get(map, name));
  }
  
  BOOST_CHECK_EQUAL(ROUND_TEST_MAP_SIZE, round_method_map_size(map));

  // Remove methods
  
  for (int n=0; n<ROUND_TEST_MAP_SIZE; n++) {
    snprintf(name, sizeof(name), "%d", n);
    BOOST_CHECK(round_method_map_remove(map, name));
    BOOST_CHECK(!round_method_map_get(map, name));
    BOOST_CHECK_EQUAL((ROUND_TEST_MAP_SIZE-(n+1)), round_method_map_size(map));
  }
  
  BOOST_CHECK_EQUAL(0, round_method_map_size(map));
  
  BOOST_CHECK(round_method_map_delete(map));
}
