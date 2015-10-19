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

#include <round/util/strings.h>

BOOST_AUTO_TEST_CASE(IsNumeric)
{
  BOOST_CHECK_EQUAL(round_isnumeric(NULL), false);
  BOOST_CHECK_EQUAL(round_isnumeric(""), false);
  BOOST_CHECK_EQUAL(round_isnumeric("a"), false);
  BOOST_CHECK_EQUAL(round_isnumeric("abc"), false);
  BOOST_CHECK_EQUAL(round_isnumeric("#"), false);
  BOOST_CHECK_EQUAL(round_isnumeric("#$%"), false);
  BOOST_CHECK_EQUAL(round_isnumeric("1234567890a"), false);
  BOOST_CHECK_EQUAL(round_isnumeric("1234567890#"), false);

  BOOST_CHECK_EQUAL(round_isnumeric("0"), true);
  BOOST_CHECK_EQUAL(round_isnumeric("1"), true);
  BOOST_CHECK_EQUAL(round_isnumeric("12"), true);
  BOOST_CHECK_EQUAL(round_isnumeric("1234567890"), true);
}
