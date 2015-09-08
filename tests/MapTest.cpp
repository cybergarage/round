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
  
  size_t tableSize = round_map_gettablesize(map);
  
  RoundMapObject *mapObj;
  char key[64];
  
  // Add key objects
  
  for (size_t n=0; n<tableSize; n++) {
    snprintf(key, sizeof(key), "%ld", n);
    mapObj = round_map_object_new();
    round_map_object_setkey(mapObj, key);
    BOOST_CHECK(round_map_addmapobject(map, mapObj));
    BOOST_CHECK_EQUAL(round_map_size(map), (n+1));
  }

  BOOST_CHECK_EQUAL(round_map_size(map), tableSize);

  // Check map distribution

  double mapDist = round_map_getefficiency(map);
  BOOST_WARN(0.5f < mapDist);
#ifdef DEBUG
  //round_map_printdistribution(map);
#endif
  
  // Get key objects
  
  for (size_t n=0; n<tableSize; n++) {
    snprintf(key, sizeof(key), "%ld", n);
    mapObj = round_map_getmapobjectbykey(map, key);
    BOOST_CHECK(mapObj);
  }
  
  BOOST_CHECK_EQUAL(round_map_size(map), tableSize);
  
  // Add same key objects
  
  for (size_t n=0; n<tableSize; n++) {
    snprintf(key, sizeof(key), "%ld", n);
    mapObj = round_map_object_new();
    round_map_object_setkey(mapObj, key);
    BOOST_CHECK(round_map_addmapobject(map, mapObj));
    BOOST_CHECK_EQUAL(round_map_size(map), tableSize);
  }
  
  BOOST_CHECK_EQUAL(round_map_size(map), tableSize);
  
  // Remove key objects
  
  for (size_t n=0; n<tableSize; n++) {
    snprintf(key, sizeof(key), "%ld", n);
    BOOST_CHECK(round_map_removeobjectbykey(map, key));
    BOOST_CHECK_EQUAL(round_map_size(map), (tableSize-(n+1)));
  }

  BOOST_CHECK_EQUAL(round_map_size(map), 0);
  
  BOOST_CHECK(round_map_delete(map));
}
