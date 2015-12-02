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

BOOST_AUTO_TEST_SUITE(method)

BOOST_AUTO_TEST_CASE(MethodNew)
{
  RoundMethod* method = round_method_new();
  BOOST_CHECK(method);

  BOOST_CHECK_EQUAL(round_method_isvalid(method), false);

  BOOST_CHECK(round_method_delete(method));
}

BOOST_AUTO_TEST_CASE(MethodSet)
{
  const char* TEST_MODULE = "methodname";
  const char* TEST_NAME = "methodname";
  const char* TEST_LANG = "methodlang";
  const char* TEST_CODE = "methodcode";

  RoundMethod* method = round_method_new();
  BOOST_CHECK(method);

  BOOST_CHECK_EQUAL(round_method_isvalid(method), false);

  BOOST_CHECK(round_method_setmodule(method, TEST_MODULE));
  BOOST_CHECK(round_method_setname(method, TEST_NAME));
  BOOST_CHECK(round_method_setlanguage(method, TEST_LANG));
  BOOST_CHECK(round_method_setstringcode(method, TEST_CODE));

  BOOST_CHECK_EQUAL(round_method_getmodule(method), TEST_MODULE);
  BOOST_CHECK_EQUAL(round_method_getname(method), TEST_NAME);
  BOOST_CHECK_EQUAL(round_method_getlanguage(method), TEST_LANG);
  BOOST_CHECK_EQUAL(round_method_getstringcode(method), TEST_CODE);

  BOOST_CHECK_EQUAL(round_method_isvalid(method), true);

  BOOST_CHECK(round_method_delete(method));
}

BOOST_AUTO_TEST_SUITE_END()
