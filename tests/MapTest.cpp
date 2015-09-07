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
  
  BOOST_CHECK(round_map_delete(map));
}
