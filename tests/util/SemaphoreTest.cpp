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

#include <round/util/semaphore.h>
#include <round/util/thread.h>
#include <round/util/timer.h>

BOOST_AUTO_TEST_SUITE(semaphore)

BOOST_AUTO_TEST_CASE(RoundSemaphoreBasicTest)
{
  RoundSemaphore* sem = round_semaphore_new(0);
  BOOST_CHECK(sem);

  BOOST_CHECK_EQUAL(round_semaphore_post(sem), true);
  BOOST_CHECK_EQUAL(round_semaphore_wait(sem), true);

  BOOST_CHECK_EQUAL(round_semaphore_post(sem), true);
  BOOST_CHECK_EQUAL(round_semaphore_post(sem), true);
  BOOST_CHECK_EQUAL(round_semaphore_wait(sem), true);
  BOOST_CHECK_EQUAL(round_semaphore_wait(sem), true);

  BOOST_CHECK_EQUAL(round_semaphore_post(sem), true);
  BOOST_CHECK_EQUAL(round_semaphore_wait(sem), true);
  BOOST_CHECK_EQUAL(round_semaphore_post(sem), true);
  BOOST_CHECK_EQUAL(round_semaphore_wait(sem), true);

  BOOST_CHECK(round_semaphore_delete(sem));
}

BOOST_AUTO_TEST_CASE(RoundSemaphoreMaxCountTest)
{
  for (size_t semMaxCount = 1; semMaxCount < 10; semMaxCount++) {
    RoundSemaphore* sem = round_semaphore_new(semMaxCount);
    BOOST_CHECK(sem);

    for (size_t n = 0; n < semMaxCount; n++) {
      BOOST_CHECK_EQUAL(round_semaphore_wait(sem), true);
    }

    for (size_t n = 0; n < semMaxCount; n++) {
      BOOST_CHECK_EQUAL(round_semaphore_post(sem), true);
    }

    BOOST_CHECK(round_semaphore_delete(sem));
  }
}

static const int SEMAPHORE_THREAD_TEST_LOOP_NUM = 10;

void RoundSemaphorePostThread(RoundThread* thread)
{
  RoundSemaphore* sem = (RoundSemaphore*)round_thread_getuserdata(thread);
  for (int n = 0; n < SEMAPHORE_THREAD_TEST_LOOP_NUM; n++) {
    round_sleep(100);
    BOOST_CHECK_EQUAL(round_semaphore_post(sem), true);
  }
}

BOOST_AUTO_TEST_CASE(RoundSemaphoreThreadTest)
{
  RoundSemaphore* sem = round_semaphore_new(0);

  RoundThread* thread = round_thread_new();
  round_thread_setaction(thread, RoundSemaphorePostThread);
  round_thread_setuserdata(thread, sem);
  BOOST_CHECK(round_thread_start(thread));

  for (int n = 0; n < SEMAPHORE_THREAD_TEST_LOOP_NUM; n++) {
    BOOST_CHECK_EQUAL(round_semaphore_wait(sem), true);
  }

  BOOST_CHECK(round_thread_stop(thread));
  BOOST_CHECK(round_thread_delete(thread));
  BOOST_CHECK(round_semaphore_delete(sem));
}

BOOST_AUTO_TEST_CASE(RoundSemaphoreTimeoutTest)
{
  RoundSemaphore* sem = round_semaphore_new(0);
  BOOST_CHECK(sem);

  BOOST_CHECK_EQUAL(round_semaphore_post(sem), true);
  BOOST_CHECK_EQUAL(round_semaphore_wait(sem), true);

  BOOST_CHECK_EQUAL(round_semaphore_timedwait(sem, 1), false);

  BOOST_CHECK_EQUAL(round_semaphore_post(sem), true);
  BOOST_CHECK_EQUAL(round_semaphore_wait(sem), true);

  BOOST_CHECK(round_semaphore_delete(sem));
}

BOOST_AUTO_TEST_SUITE_END()
