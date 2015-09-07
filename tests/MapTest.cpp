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

#include <round/util/map.h>

BOOST_AUTO_TEST_CASE(MapNew)
{
  RoundMap *map = round_map_new();
  BOOST_CHECK(map);
  
  BOOST_CHECK_EQUAL(round_map_size(map), 0);
  
  RoundMapObject *mapObj;
  char key[64];
  
  // Add key objects
  
  for (int n=0; n<ROUND_UTIL_MAP_TABLE_SIZE; n++) {
    snprintf(key, sizeof(key), "%08X%08X", n, (ROUND_UTIL_MAP_TABLE_SIZE - n));
    mapObj = round_map_object_new();
    round_map_object_setkey(mapObj, key);
    BOOST_CHECK(round_map_addobject(map, mapObj));
    BOOST_CHECK_EQUAL(round_map_size(map), (n+1));
  }

  BOOST_CHECK_EQUAL(round_map_size(map), ROUND_UTIL_MAP_TABLE_SIZE);

  // Check map distribution

  double mapDist = round_map_getefficiency(map);
  BOOST_WARN(0.5f < mapDist);
  
  // Get key objects
  
  for (int n=0; n<ROUND_UTIL_MAP_TABLE_SIZE; n++) {
    snprintf(key, sizeof(key), "%08X%08X", n, (ROUND_UTIL_MAP_TABLE_SIZE - n));
    mapObj = round_map_getobjectbykey(map, key);
    BOOST_CHECK(mapObj);
  }
  
  BOOST_CHECK_EQUAL(round_map_size(map), ROUND_UTIL_MAP_TABLE_SIZE);
  
  // Add same key objects
  
  for (int n=0; n<ROUND_UTIL_MAP_TABLE_SIZE; n++) {
    snprintf(key, sizeof(key), "%08X%08X", n, (ROUND_UTIL_MAP_TABLE_SIZE - n));
    mapObj = round_map_object_new();
    round_map_object_setkey(mapObj, key);
    BOOST_CHECK(round_map_addobject(map, mapObj));
    BOOST_CHECK_EQUAL(round_map_size(map), ROUND_UTIL_MAP_TABLE_SIZE);
  }
  
  BOOST_CHECK_EQUAL(round_map_size(map), ROUND_UTIL_MAP_TABLE_SIZE);
  
  // Remove key objects
  
  for (int n=0; n<ROUND_UTIL_MAP_TABLE_SIZE; n++) {
    snprintf(key, sizeof(key), "%08X%08X", n, (ROUND_UTIL_MAP_TABLE_SIZE - n));
    BOOST_CHECK(round_map_removeobjectbykey(map, key));
    BOOST_CHECK_EQUAL(round_map_size(map), (ROUND_UTIL_MAP_TABLE_SIZE-(n+1)));
  }

  BOOST_CHECK_EQUAL(round_map_size(map), 0);
  
  BOOST_CHECK(round_map_delete(map));
}
