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

#include <round/clock.h>

BOOST_AUTO_TEST_SUITE(clock_test)

BOOST_AUTO_TEST_CASE(ClockSet)
{
  RoundClock *clk = round_clock_new();
  BOOST_CHECK(clk);
  
  time_t timeValue = time(NULL);
  round_clock_setvalue(clk, timeValue);
  BOOST_CHECK_EQUAL(round_clock_getvalue(clk), timeValue);
  BOOST_CHECK(round_clock_delete(clk));
}

BOOST_AUTO_TEST_CASE(ClockIncrement)
{
  RoundClock *clk = round_clock_new();
  BOOST_CHECK(clk);
  
  round_clock_setvalue(clk, time(NULL));
  clock_t startClk = round_clock_getvalue(clk);
  
  const int incLoopCnt = 10;
  for (int n=0; n<incLoopCnt; n++) {
    clock_t prevClock = round_clock_getvalue(clk);
    clock_t nowClock = round_clock_increment(clk);
    BOOST_CHECK(prevClock < nowClock);
    BOOST_CHECK_EQUAL(nowClock, (prevClock + ROUNDC_CLOCK_INCREMENT_VALUE));
  }
  
  clock_t endClock = round_clock_getvalue(clk);
  BOOST_CHECK_EQUAL(endClock, (startClk + incLoopCnt));

  BOOST_CHECK(round_clock_delete(clk));
}

BOOST_AUTO_TEST_CASE(ClockCompare) {
  time_t timeValue = time(NULL);
  
  RoundClock *clk01 = round_clock_new();
  RoundClock *clk02 = round_clock_new();
  RoundClock *clk03 = round_clock_new();
  RoundClock *clk04 = round_clock_new();
  
  round_clock_setvalue(clk01, (timeValue));
  round_clock_setvalue(clk02, (timeValue));
  round_clock_setvalue(clk03, (timeValue + 1));
  round_clock_setvalue(clk04, (timeValue - 1));
  
  BOOST_CHECK_EQUAL(round_clock_compare(clk01, clk01), RoundClockOrderSame);
  BOOST_CHECK_EQUAL(round_clock_compare(clk01, clk02), RoundClockOrderSame);
  BOOST_CHECK_EQUAL(round_clock_compare(clk01, clk03), RoundClockOrderAscending);
  BOOST_CHECK_EQUAL(round_clock_compare(clk01, clk04), RoundClockOrderDescending);

  BOOST_CHECK(round_clock_delete(clk01));
  BOOST_CHECK(round_clock_delete(clk02));
  BOOST_CHECK(round_clock_delete(clk03));
  BOOST_CHECK(round_clock_delete(clk04));
}

BOOST_AUTO_TEST_SUITE_END()
