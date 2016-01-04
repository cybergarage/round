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

#include <round/error_internal.h>

BOOST_AUTO_TEST_SUITE(error)

static void BOOST_ROUND_ERROR_TEST(RoundError* err)
{
  BOOST_CHECK(err);

  BOOST_CHECK_EQUAL(round_error_getcode(err), 0);
  BOOST_CHECK_EQUAL(round_error_getdetailcode(err), 0);
  BOOST_CHECK_EQUAL(round_strlen(round_error_getmessage(err)), 0);
  BOOST_CHECK_EQUAL(round_strlen(round_error_getdetailmessage(err)), 0);

  int code = 1234;
  BOOST_CHECK(round_error_setcode(err, code));
  BOOST_CHECK_EQUAL(round_error_getcode(err), code);

  const char* msg = "hello";
  BOOST_CHECK(round_error_setmessage(err, msg));
  BOOST_CHECK(round_streq(round_error_getmessage(err), msg));

  int detailCode = 5678;
  BOOST_CHECK(round_error_setdetailcode(err, detailCode));
  BOOST_CHECK_EQUAL(round_error_getdetailcode(err), detailCode);

  const char* detailMsg = "hello world";
  BOOST_CHECK(round_error_setdetailmessage(err, detailMsg));
  BOOST_CHECK(round_streq(round_error_getdetailmessage(err), detailMsg));

  BOOST_CHECK_EQUAL(round_error_getcode(err), code);
  BOOST_CHECK(round_streq(round_error_getmessage(err), msg));
  BOOST_CHECK_EQUAL(round_error_getdetailcode(err), detailCode);
  BOOST_CHECK(round_streq(round_error_getdetailmessage(err), detailMsg));

  round_error_clear(err);
  BOOST_CHECK_EQUAL(round_error_getcode(err), 0);
  BOOST_CHECK_EQUAL(round_error_getdetailcode(err), 0);
  BOOST_CHECK_EQUAL(round_strlen(round_error_getmessage(err)), 0);
  BOOST_CHECK_EQUAL(round_strlen(round_error_getdetailmessage(err)), 0);
}

BOOST_AUTO_TEST_CASE(ErrortNew)
{
  RoundError* err = round_error_new();

  BOOST_ROUND_ERROR_TEST(err);

  BOOST_CHECK(round_error_delete(err));
}

BOOST_AUTO_TEST_CASE(ErrortStruct)
{
  RoundError err;

  BOOST_CHECK(round_error_init(&err));
  BOOST_ROUND_ERROR_TEST(&err);
  BOOST_CHECK(round_error_destroy(&err));
}

BOOST_AUTO_TEST_SUITE_END()
