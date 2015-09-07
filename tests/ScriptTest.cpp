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

#include <round/script_internal.h>

BOOST_AUTO_TEST_CASE(ScriptNew)
{
  RoundScript *sc = round_script_new();
  BOOST_CHECK(sc);
  
  BOOST_CHECK_EQUAL(round_script_isvalid(sc), false);
  
  BOOST_CHECK(round_script_delete(sc));
}
