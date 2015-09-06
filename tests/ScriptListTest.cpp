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

BOOST_AUTO_TEST_CASE(ScriptListNew)
{
  RoundScriptList *scripts = round_scriptlist_new();
  BOOST_CHECK(scripts);
  BOOST_CHECK(round_scriptlist_delete(scripts));
}
