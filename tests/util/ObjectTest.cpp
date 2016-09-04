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

#include <round/util/object.h>

BOOST_AUTO_TEST_SUITE(object)

BOOST_AUTO_TEST_CASE(ObjectNew)
{
  RoundObject* obj = round_object_new();

  BOOST_CHECK(obj);

  BOOST_CHECK(round_object_delete(obj));
}

BOOST_AUTO_TEST_SUITE_END()
