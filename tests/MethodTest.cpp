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

#include <round/method.h>

BOOST_AUTO_TEST_CASE(MethodNew)
{
  RoundMethod *method = round_method_new();
  BOOST_CHECK(method);
  
  BOOST_CHECK_EQUAL(round_method_isvalid(method), false);
  
  BOOST_CHECK(round_method_delete(method));
}
