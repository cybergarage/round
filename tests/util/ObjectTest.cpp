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

#include <round/util/object.h>
#include <round/util/thread.h>
#include <round/util/timer.h>

#include "RoundTest.h"


BOOST_AUTO_TEST_SUITE(object)

BOOST_AUTO_TEST_CASE(ObjectNew)
{
  RoundObject* obj = round_object_new();

  BOOST_CHECK(obj);

  BOOST_CHECK_EQUAL(round_object_getreferencecount(obj), 0);
  
  BOOST_CHECK(round_object_delete(obj));
}

BOOST_AUTO_TEST_CASE(ObjecCheckReference)
{
  RoundObject* obj = round_object_new();
  
  BOOST_CHECK(obj);

  int n;
  
  for (n=0; n < ROUND_TEST_LOOP_COUNT; n++) {
    BOOST_CHECK_EQUAL(round_object_getreferencecount(obj), 0);
    BOOST_CHECK(round_object_alloc(obj));
    BOOST_CHECK_EQUAL(round_object_getreferencecount(obj), 1);
    BOOST_CHECK(round_object_release(obj));
    BOOST_CHECK_EQUAL(round_object_getreferencecount(obj), 0);
  }
  
  BOOST_CHECK_EQUAL(round_object_getreferencecount(obj), 0);

  for (n=0; n < ROUND_TEST_LOOP_COUNT; n++) {
    BOOST_CHECK_EQUAL(round_object_getreferencecount(obj), n);
    BOOST_CHECK(round_object_alloc(obj));
    BOOST_CHECK_EQUAL(round_object_getreferencecount(obj), (n+1));
  }
  
  BOOST_CHECK_EQUAL(round_object_getreferencecount(obj), ROUND_TEST_LOOP_COUNT);
  
  for (n=0; n < ROUND_TEST_LOOP_COUNT; n++) {
    BOOST_CHECK_EQUAL(round_object_getreferencecount(obj), (ROUND_TEST_LOOP_COUNT - n));
    BOOST_CHECK(round_object_release(obj));
    BOOST_CHECK_EQUAL(round_object_getreferencecount(obj), (ROUND_TEST_LOOP_COUNT - (n + 1)));
  }
  
  BOOST_CHECK_EQUAL(round_object_getreferencecount(obj), 0);
  
  BOOST_CHECK(round_object_delete(obj));
}


static void RoundTestObjectReleaseReference(RoundThread *thread)
{
  RoundObject *obj = (RoundObject *)round_thread_getuserdata(thread);
  round_wait(1.0);
  for (int n=0; n < ROUND_TEST_LOOP_COUNT; n++) {
    round_object_release(obj);
  }
}

BOOST_AUTO_TEST_CASE(ObjecReleaseReferenceByThread)
{
  RoundObject* obj = round_object_new();
  
  BOOST_CHECK(obj);
  
  for (int n=0; n < ROUND_TEST_LOOP_COUNT; n++) {
    BOOST_CHECK(round_object_alloc(obj));
  }
  
  RoundThread *thread = round_thread_new();
  round_thread_setaction(thread, RoundTestObjectReleaseReference);
  round_thread_setuserdata(thread, obj);
  BOOST_CHECK_EQUAL (round_thread_start(thread), true);
  
  BOOST_CHECK(round_object_delete(obj));

  BOOST_CHECK_EQUAL(round_thread_stop(thread), true);
  BOOST_CHECK_EQUAL(round_thread_isrunning(thread), false);
  BOOST_CHECK_EQUAL(round_thread_delete(thread), true);
}

static void RoundTestObjectRandomAllocReference(RoundThread *thread)
{
  RoundObject *obj = (RoundObject *)round_thread_getuserdata(thread);
  for (int n=0; n < ROUND_TEST_LOOP_COUNT; n++) {
    round_waitrandom(0.1);
    round_object_alloc(obj);
  }
}

static void RoundTestObjectRandomReleaseReference(RoundThread *thread)
{
  RoundObject *obj = (RoundObject *)round_thread_getuserdata(thread);
  for (int n=0; n < ROUND_TEST_LOOP_COUNT; n++) {
    round_waitrandom(0.1);
    round_object_release(obj);
  }
}

BOOST_AUTO_TEST_CASE(ObjecRandomAllocReleaseReferenceByThread)
{
  RoundObject* obj = round_object_new();
  
  BOOST_CHECK(obj);
  
  BOOST_CHECK(round_object_alloc(obj));
  
  RoundThread *thread0 = round_thread_new();
  round_thread_setaction(thread0, RoundTestObjectRandomAllocReference);
  round_thread_setuserdata(thread0, obj);
  BOOST_CHECK_EQUAL (round_thread_start(thread0), true);
  
  RoundThread *thread1 = round_thread_new();
  round_thread_setaction(thread1, RoundTestObjectRandomReleaseReference);
  round_thread_setuserdata(thread1, obj);
  BOOST_CHECK_EQUAL (round_thread_start(thread1), true);
  
  BOOST_CHECK(round_object_release(obj));
  
  BOOST_CHECK(round_object_delete(obj));
  
  BOOST_CHECK_EQUAL(round_thread_stop(thread0), true);
  BOOST_CHECK_EQUAL(round_thread_stop(thread1), true);
  
  BOOST_CHECK_EQUAL(round_thread_delete(thread0), true);
  BOOST_CHECK_EQUAL(round_thread_delete(thread1), true);
}

BOOST_AUTO_TEST_SUITE_END()
