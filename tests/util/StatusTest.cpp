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

#include <round/util/status.h>

#define ROUND_TEST_LIST_SIZE 10

BOOST_AUTO_TEST_SUITE(status)

BOOST_AUTO_TEST_CASE(StatusSet)
{
  RoundStatus stat;

  round_status_init(stat);
  
  BOOST_CHECK_EQUAL(round_status_get(stat), 0);
  BOOST_CHECK(round_status_isdisabled(stat, 0x01));
  BOOST_CHECK(round_status_isdisabled(stat, 0x02));

  round_status_set(stat, 0x01);
  BOOST_CHECK_EQUAL(round_status_get(stat), 0x01);
  BOOST_CHECK(round_status_isenabled(stat, 0x01));
  BOOST_CHECK(round_status_isdisabled(stat, 0x02));

  round_status_set(stat, 0x02);
  BOOST_CHECK_EQUAL(round_status_get(stat), 0x02);
  BOOST_CHECK(round_status_isdisabled(stat, 0x01));
  BOOST_CHECK(round_status_isenabled(stat, 0x02));

  round_status_set(stat, 0x03);
  BOOST_CHECK_EQUAL(round_status_get(stat), 0x03);
  BOOST_CHECK(round_status_isenabled(stat, 0x01));
  BOOST_CHECK(round_status_isenabled(stat, 0x02));

  round_status_clear(stat);
  BOOST_CHECK_EQUAL(round_status_get(stat), 0);
  round_status_setflag(stat, 0x01, true);
  round_status_setflag(stat, 0x02, true);
  BOOST_CHECK(round_status_isenabled(stat, 0x01));
  BOOST_CHECK(round_status_isenabled(stat, 0x02));
  round_status_setflag(stat, 0x02, false);
  BOOST_CHECK(round_status_isenabled(stat, 0x01));
  BOOST_CHECK(round_status_isdisabled(stat, 0x02));
  round_status_setflag(stat, 0x01, false);
  BOOST_CHECK(round_status_isdisabled(stat, 0x01));
  BOOST_CHECK(round_status_isdisabled(stat, 0x02));
  BOOST_CHECK_EQUAL(round_status_get(stat), 0);
}

BOOST_AUTO_TEST_SUITE_END()
