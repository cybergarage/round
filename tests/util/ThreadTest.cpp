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

BOOST_AUTO_TEST_SUITE(thread)

void TestThereadFunc(RoundThread *thread)
{
  int *testCounter = (int *)round_thread_getuserdata(thread);
  for (int n = 0; n < THREAD_TEST_LOOP_NUM; n++) {
    (*testCounter)++;
  }
}

BOOST_AUTO_TEST_CASE(ThreadTest)
{
  RoundThread *thread = round_thread_new();
  
  int testCounter = 0;
  round_thread_setaction(thread, TestThereadFunc);
  round_thread_setuserdata(thread, &testCounter);
  
  BOOST_CHECK_EQUAL (round_thread_start(thread), true);
  while (testCounter != THREAD_TEST_LOOP_NUM) {
    round_sleep(100);
  }
  BOOST_CHECK_EQUAL(testCounter, THREAD_TEST_LOOP_NUM);
  BOOST_CHECK_EQUAL(round_thread_stop(thread), true);
  
  round_thread_delete(thread);
}

BOOST_AUTO_TEST_SUITE_END()
