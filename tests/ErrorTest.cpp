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

#include <round/error.h>

BOOST_AUTO_TEST_CASE(ErrortNew)
{
  RoundError *err = round_error_new();
  BOOST_CHECK(err);
  
  BOOST_CHECK(round_error_delete(err));
}
