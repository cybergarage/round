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

#include <round/util/thread.h>
#include <round/util/timer.h>

const int THREAD_TEST_LOOP_NUM = 10;
const double THREAD_TEST_CYCLEINTERVAL = 0.1;

BOOST_AUTO_TEST_SUITE(thread)

BOOST_AUTO_TEST_CASE(ThreadNew)
{
  RoundThread *thread = round_thread_new();
  
  BOOST_CHECK_EQUAL(round_thread_isloop(thread), false);
  BOOST_CHECK_EQUAL(round_thread_getcycleinterval(thread), 0.0);

  BOOST_CHECK_EQUAL(round_thread_getstarttime(thread), 0.0);
  BOOST_CHECK_EQUAL(round_thread_isstarttimeenabled(thread), false);

  BOOST_CHECK_EQUAL(round_thread_getstoptime(thread), 0.0);
  BOOST_CHECK_EQUAL(round_thread_isstoptimeenabled(thread), false);

  BOOST_CHECK_EQUAL(round_thread_isrunnable(thread), false);
  BOOST_CHECK_EQUAL(round_thread_isrunning(thread), false);
  
  round_thread_delete(thread);
}

static void RoundTestThereadFunc(RoundThread *thread)
{
  int *testCounter = (int *)round_thread_getuserdata(thread);
  for (int n = 0; n < THREAD_TEST_LOOP_NUM; n++) {
    (*testCounter)++;
  }
}

BOOST_AUTO_TEST_CASE(ThreadLoop)
{
  RoundThread *thread = round_thread_new();
  
  int testCounter = 0;
  round_thread_setaction(thread, RoundTestThereadFunc);
  round_thread_setuserdata(thread, &testCounter);
  
  BOOST_CHECK_EQUAL (round_thread_start(thread), true);
  BOOST_CHECK_EQUAL(round_thread_isrunning(thread), true);
  while (testCounter != THREAD_TEST_LOOP_NUM) {
    round_sleep(0.1);
  }
  BOOST_CHECK_EQUAL(testCounter, THREAD_TEST_LOOP_NUM);
  BOOST_CHECK_EQUAL(round_thread_stop(thread), true);
  BOOST_CHECK_EQUAL(round_thread_isrunning(thread), false);
  
  round_thread_delete(thread);
}

static void RoundTestCycleIntervalFunc(RoundThread *thread)
{
  int *testCounter = (int *)round_thread_getuserdata(thread);
  (*testCounter)++;
}

BOOST_AUTO_TEST_CASE(ThreadCycleInterval)
{
  RoundThread *thread = round_thread_new();
  
  static int testCounter = 0;
  round_thread_setaction(thread, RoundTestCycleIntervalFunc);
  round_thread_setuserdata(thread, &testCounter);
  round_thread_setloop(thread, true);
  round_thread_setcycleinterval(thread, THREAD_TEST_CYCLEINTERVAL);
  
  BOOST_CHECK_EQUAL (round_thread_start(thread), true);
  BOOST_CHECK_EQUAL(round_thread_isrunning(thread), true);
  
  round_sleep(THREAD_TEST_CYCLEINTERVAL * (THREAD_TEST_LOOP_NUM +1));
  
  BOOST_CHECK_EQUAL(round_thread_stop(thread), true);
  
  BOOST_CHECK(THREAD_TEST_LOOP_NUM <= testCounter);
  
  round_thread_delete(thread);
}

BOOST_AUTO_TEST_CASE(ThreadStartAndEndTime)
{
  RoundThread *thread = round_thread_new();
  
  double startTime = round_getcurrentunixtime();
  double stopTime = startTime + (THREAD_TEST_CYCLEINTERVAL * (THREAD_TEST_LOOP_NUM + 2));
  
  static int testCounter = 0;
  round_thread_setaction(thread, RoundTestCycleIntervalFunc);
  round_thread_setuserdata(thread, &testCounter);
  round_thread_setloop(thread, true);
  round_thread_setstarttime(thread, startTime);
  round_thread_setstoptime(thread, stopTime);
  round_thread_setcycleinterval(thread, THREAD_TEST_CYCLEINTERVAL);

  BOOST_CHECK(round_thread_isstarttimeenabled(thread));
  BOOST_CHECK(round_thread_isstoptimeenabled(thread));
  BOOST_CHECK(round_thread_getstarttime(thread) < round_thread_getstoptime(thread));
  
  BOOST_CHECK_EQUAL(round_thread_start(thread), true);
  BOOST_CHECK_EQUAL(round_thread_isrunning(thread), true);
  
  while (round_getcurrentunixtime() < stopTime) {
    round_sleep(THREAD_TEST_CYCLEINTERVAL);
  }
  
  BOOST_CHECK(THREAD_TEST_LOOP_NUM <= testCounter);
  
  BOOST_CHECK_EQUAL(round_thread_stop(thread), true);
  BOOST_CHECK_EQUAL(round_thread_isrunning(thread), false);
  
  round_thread_delete(thread);
}

BOOST_AUTO_TEST_SUITE_END()
