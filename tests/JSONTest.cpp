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

#include <round/util/json.h>

BOOST_AUTO_TEST_CASE(JSONParse)
{
  RoundJSON *json = round_json_new();
  BOOST_CHECK(json);
  
  BOOST_CHECK(round_json_delete(json));
}
