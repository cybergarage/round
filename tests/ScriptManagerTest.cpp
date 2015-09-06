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

BOOST_AUTO_TEST_CASE(ScriptManagerNew)
{
  RoundScriptManager *mgr = round_script_manager_new();
  BOOST_CHECK(mgr);
  BOOST_CHECK(round_script_manager_delete(mgr));
}
