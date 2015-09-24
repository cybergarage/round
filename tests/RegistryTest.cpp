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
#include <round/registry.h>

BOOST_AUTO_TEST_CASE(RegistryMap)
{
  RoundMap *map = round_registry_map_new();
  
  BOOST_CHECK(map);
  BOOST_CHECK_EQUAL(0, round_registry_map_size(map));
  
  RoundRegistry *reg[ROUND_TEST_MAP_SIZE];
  char key[32];
  char val[32];

  // Add regs
  
  for (int n=0; n<ROUND_TEST_MAP_SIZE; n++) {
    reg[n] = round_registry_new();
    BOOST_CHECK(reg[n]);
    BOOST_CHECK(!round_registry_map_set(map, reg[n]));

    snprintf(key, sizeof(key), "key%d", n);
    round_registry_setkey(reg[n], key);
    
    snprintf(val, sizeof(key), "val%d", n);
    round_registry_setvalue(reg[n], key);
    
    BOOST_CHECK(round_registry_map_set(map, reg[n]));
    BOOST_CHECK_EQUAL((n+1), round_registry_map_size(map));
  }
  
  BOOST_CHECK_EQUAL(ROUND_TEST_MAP_SIZE, round_registry_map_size(map));

  // Get regs
  
  for (int n=0; n<ROUND_TEST_MAP_SIZE; n++) {
    snprintf(key, sizeof(key), "key%d", n);
    BOOST_CHECK_EQUAL(reg[n], round_registry_map_get(map, key));
    BOOST_CHECK_EQUAL(round_registry_getvalue(reg[n]), round_registry_getvalue(round_registry_map_get(map, key)));
  }
  
  BOOST_CHECK_EQUAL(ROUND_TEST_MAP_SIZE, round_registry_map_size(map));

  // Remove regs
  
  for (int n=0; n<ROUND_TEST_MAP_SIZE; n++) {
    snprintf(key, sizeof(key), "key%d", n);
    BOOST_CHECK(round_registry_map_remove(map, key));
    BOOST_CHECK(!round_registry_map_get(map, key));
    BOOST_CHECK_EQUAL((ROUND_TEST_MAP_SIZE-(n+1)), round_registry_map_size(map));
  }
  
  BOOST_CHECK_EQUAL(0, round_registry_map_size(map));
  
  BOOST_CHECK(round_registry_map_delete(map));
}
