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

#include <round/message.h>
#include <round/util/thread.h>
#include <round/util/timer.h>

#define ROUND_MSGMRG_TEST_COUNT 10

BOOST_AUTO_TEST_SUITE(message)

BOOST_AUTO_TEST_CASE(MessageNew)
{
  RoundMessage* msg = round_message_new();
  BOOST_CHECK(msg);

  BOOST_CHECK_EQUAL(round_message_isnotifyenabled(msg), false);

  BOOST_CHECK(round_message_delete(msg));
}

BOOST_AUTO_TEST_CASE(MessageSemaphore)
{
  RoundMessage* msg = round_message_new();
  BOOST_CHECK(msg);

  BOOST_CHECK_EQUAL(round_message_isnotifyenabled(msg), false);
  BOOST_CHECK_EQUAL(round_message_setnotifyenabled(msg, true), true);
  BOOST_CHECK_EQUAL(round_message_isnotifyenabled(msg), true);

  BOOST_CHECK_EQUAL(round_message_notify(msg), true);
  BOOST_CHECK_EQUAL(round_message_waitnotify(msg), true);

  BOOST_CHECK_EQUAL(round_message_timedwaitnotify(msg, 1), false);

  BOOST_CHECK_EQUAL(round_message_notify(msg), true);
  BOOST_CHECK_EQUAL(round_message_waitnotify(msg), true);

  BOOST_CHECK(round_message_delete(msg));
}

BOOST_AUTO_TEST_CASE(MessageManager)
{
  RoundMessageManager* mgr = round_message_manager_new();

  char data[32];
  for (int n = 0; n < ROUND_MSGMRG_TEST_COUNT; n++) {
    snprintf(data, sizeof(data), "msg%d", n);
    RoundMessage* msg = round_message_new();
    round_message_setstring(msg, data);
    BOOST_CHECK(round_message_manager_pushmessage(mgr, msg));
  }

  for (int n = 0; n < ROUND_MSGMRG_TEST_COUNT; n++) {
    snprintf(data, sizeof(data), "msg%d", n);
    RoundMessage* msg = NULL;
    BOOST_CHECK(round_message_manager_waitmessage(mgr, &msg));
    BOOST_CHECK(msg);
    BOOST_CHECK_EQUAL(data, round_message_getstring(msg));
    BOOST_CHECK(round_message_delete(msg));
  }

  BOOST_CHECK(round_message_manager_delete(mgr));
}

void RoundMsgPushThread(RoundThread* thread)
{
  RoundMessageManager* mgr = (RoundMessageManager*)round_thread_getuserdata(thread);

  char data[32];
  for (int n = 0; n < ROUND_MSGMRG_TEST_COUNT; n++) {
    round_sleep(0.1);
    snprintf(data, sizeof(data), "msg%d", n);
    RoundMessage* msg = round_message_new();
    round_message_setstring(msg, data);
    BOOST_CHECK(round_message_manager_pushmessage(mgr, msg));
  }
}

BOOST_AUTO_TEST_CASE(MessageManagerThread)
{
  RoundMessageManager* mgr = round_message_manager_new();

  RoundThread* thread = round_thread_new();
  round_thread_setaction(thread, message::RoundMsgPushThread);
  round_thread_setuserdata(thread, mgr);
  BOOST_CHECK(round_thread_start(thread));

  char data[32];
  for (int n = 0; n < ROUND_MSGMRG_TEST_COUNT; n++) {
    snprintf(data, sizeof(data), "msg%d", n);
    RoundMessage* msg = NULL;
    BOOST_CHECK(round_message_manager_waitmessage(mgr, &msg));
    BOOST_CHECK(msg);
    BOOST_CHECK_EQUAL(data, round_message_getstring(msg));
    BOOST_CHECK(round_message_delete(msg));
  }

  BOOST_CHECK(round_thread_stop(thread));
  BOOST_CHECK(round_message_manager_delete(mgr));
}

BOOST_AUTO_TEST_SUITE_END()
