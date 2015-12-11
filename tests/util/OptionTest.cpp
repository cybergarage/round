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

#include <round/util/option.h>

#define ROUND_TEST_LIST_SIZE 10

BOOST_AUTO_TEST_SUITE(option)

BOOST_AUTO_TEST_CASE(OptionSet)
{
  RoundOption opt;
  
  BOOST_CHECK_EQUAL(round_option_get(opt), 0);
  BOOST_CHECK(round_option_isdisabled(opt, 0x01));
  BOOST_CHECK(round_option_isdisabled(opt, 0x02));
  
  round_option_set(opt, 0x01);
  BOOST_CHECK_EQUAL(round_option_get(opt), 0x01);
  BOOST_CHECK(round_option_isenabled(opt, 0x01));
  BOOST_CHECK(round_option_isdisabled(opt, 0x02));
  
  round_option_set(opt, 0x02);
  BOOST_CHECK_EQUAL(round_option_get(opt), 0x02);
  BOOST_CHECK(round_option_isdisabled(opt, 0x01));
  BOOST_CHECK(round_option_isenabled(opt, 0x02));
  
  round_option_set(opt, 0x03);
  BOOST_CHECK_EQUAL(round_option_get(opt), 0x03);
  BOOST_CHECK(round_option_isenabled(opt, 0x01));
  BOOST_CHECK(round_option_isenabled(opt, 0x02));

  round_option_clear(opt);
  BOOST_CHECK_EQUAL(round_option_get(opt), 0);
  round_option_setflag(opt, 0x01, true);
  round_option_setflag(opt, 0x02, true);
  BOOST_CHECK(round_option_isenabled(opt, 0x01));
  BOOST_CHECK(round_option_isenabled(opt, 0x02));
  round_option_setflag(opt, 0x02, false);
  BOOST_CHECK(round_option_isenabled(opt, 0x01));
  BOOST_CHECK(round_option_isdisabled(opt, 0x02));
  round_option_setflag(opt, 0x01, false);
  BOOST_CHECK(round_option_isdisabled(opt, 0x01));
  BOOST_CHECK(round_option_isdisabled(opt, 0x02));
  BOOST_CHECK_EQUAL(round_option_get(opt), 0);
}

BOOST_AUTO_TEST_SUITE_END()
