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
#include <boost/thread.hpp>

#include <round/util/timer.h>

BOOST_AUTO_TEST_SUITE(timer)

BOOST_AUTO_TEST_CASE(TimeFuncTest)
{
  time_t currTime = time(NULL);
  round_sleep(100);
  
  BOOST_CHECK(round_getcurrentsystemtime() > 0);
  BOOST_CHECK(round_getcurrentunixtime() > 0.0);
  
  BOOST_CHECK(round_getcurrentunixtime() > (double)currTime);
}

BOOST_AUTO_TEST_SUITE_END()
