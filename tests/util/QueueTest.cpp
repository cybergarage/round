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

#include <round/util/queue.h>

#define ROUND_QUEUE_TEST_COUNT 64
#define ROUND_QUEUE_TEST_DATA_MAX 32

BOOST_AUTO_TEST_SUITE(queue)

BOOST_AUTO_TEST_CASE(QueuePushPopTest) {
  RoundQueue *queue = round_queue_new();

  BOOST_CHECK_EQUAL(round_queue_size(queue), 0);

  for (int n = 0; n < ROUND_QUEUE_TEST_COUNT; n++) {
    char *data = (char *)malloc(ROUND_QUEUE_TEST_DATA_MAX);
    snprintf(data, ROUND_QUEUE_TEST_DATA_MAX, "obj%d", n);
    RoundQueueObject *obj = round_queue_object_new();
    round_queue_object_setuserdata(obj, data);
    BOOST_CHECK(round_queue_push(queue, obj));
  }

  BOOST_CHECK_EQUAL(round_queue_size(queue), ROUND_QUEUE_TEST_COUNT);

  for (int n = 0; n < ROUND_QUEUE_TEST_COUNT; n++) {
    char data[ROUND_QUEUE_TEST_DATA_MAX];
    snprintf(data, sizeof(data), "obj%d", n);
    RoundQueueObject *obj = NULL;
    BOOST_CHECK(round_queue_pop(queue, &obj));
    BOOST_CHECK(obj);
    char *objData = (char *)round_queue_object_getuserdata(obj);
    BOOST_CHECK_EQUAL(data, objData);
    free(objData);
  }

  BOOST_CHECK_EQUAL(round_queue_size(queue), 0);
}

BOOST_AUTO_TEST_CASE(QueueEachPushPopTest) {
  RoundQueue *queue = round_queue_new();

  BOOST_CHECK_EQUAL(round_queue_size(queue), 0);

  for (int n = 0; n < ROUND_QUEUE_TEST_COUNT; n++) {
    char *data = (char *)malloc(ROUND_QUEUE_TEST_DATA_MAX);
    snprintf(data, ROUND_QUEUE_TEST_DATA_MAX, "obj%d", n);

    RoundQueueObject *obj = round_queue_object_new();
    round_queue_object_setuserdata(obj, data);
    BOOST_CHECK(round_queue_push(queue, obj));
    BOOST_CHECK_EQUAL(round_queue_size(queue), 1);

    RoundQueueObject *popObj = NULL;
    BOOST_CHECK(round_queue_pop(queue, &popObj));
    BOOST_CHECK(popObj);
    char *popObjData = (char *)round_queue_object_getuserdata(popObj);
    BOOST_CHECK_EQUAL(data, popObjData);
    free(popObjData);
    BOOST_CHECK_EQUAL(round_queue_size(queue), 0);
  }

  BOOST_CHECK_EQUAL(round_queue_size(queue), 0);
}

BOOST_AUTO_TEST_SUITE_END()
