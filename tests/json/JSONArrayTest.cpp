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

#include <round/util/json_internal.h>

BOOST_AUTO_TEST_SUITE(json)

BOOST_AUTO_TEST_CASE(JsonArrayAppendObject)
{
  const int TEST_LOOP_CNT = 10;
  long objVal;
  
  RoundJSONObject* obj = round_json_array_new();
  BOOST_CHECK(obj);
  BOOST_CHECK(round_json_object_isarray(obj));
  BOOST_CHECK_EQUAL(round_json_array_size(obj), 0);
  
  for (int n = 0; n < TEST_LOOP_CNT; n++) {
    RoundJSONObject* cobj = round_json_integer_new(n);
    BOOST_CHECK(round_json_array_append(obj, cobj));
    BOOST_CHECK(round_json_object_delete(cobj));
    BOOST_CHECK_EQUAL(round_json_array_size(obj), (n + 1));
  }
  
  for (int n = 0; n < TEST_LOOP_CNT; n++) {
    RoundJSONObject* cobj = round_json_array_get(obj, n);
    BOOST_CHECK(cobj);
    BOOST_CHECK(round_json_object_isinteger(cobj));
    BOOST_CHECK(round_json_object_getinteger(cobj, &objVal));
    BOOST_CHECK_EQUAL(objVal, n);
  }
  
  BOOST_CHECK_EQUAL(round_json_array_size(obj), TEST_LOOP_CNT);
  
  BOOST_CHECK(round_json_object_delete(obj));
}

BOOST_AUTO_TEST_CASE(JsonArrayAppendReplicaObject)
{
  const int TEST_LOOP_CNT = 10;
  long objVal;

  RoundJSONObject* obj = round_json_array_new();
  BOOST_CHECK(obj);
  BOOST_CHECK(round_json_object_isarray(obj));
  BOOST_CHECK_EQUAL(round_json_array_size(obj), 0);

  for (int n = 0; n < TEST_LOOP_CNT; n++) {
    RoundJSONObject* cobj = round_json_integer_new(n);
    BOOST_CHECK(round_json_array_appendreplica(obj, cobj));
    BOOST_CHECK(round_json_object_delete(cobj));
    BOOST_CHECK_EQUAL(round_json_array_size(obj), (n + 1));
  }

  for (int n = 0; n < TEST_LOOP_CNT; n++) {
    RoundJSONObject* cobj = round_json_array_get(obj, n);
    BOOST_CHECK(cobj);
    BOOST_CHECK(round_json_object_isinteger(cobj));
    BOOST_CHECK(round_json_object_getinteger(cobj, &objVal));
    BOOST_CHECK_EQUAL(objVal, n);
  }

  BOOST_CHECK_EQUAL(round_json_array_size(obj), TEST_LOOP_CNT);

  BOOST_CHECK(round_json_object_delete(obj));
}

BOOST_AUTO_TEST_SUITE_END()
