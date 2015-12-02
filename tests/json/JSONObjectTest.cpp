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

BOOST_AUTO_TEST_CASE(JsonMapObjNew) {
  RoundJSONObject *obj = round_json_map_new();
  BOOST_CHECK(obj);
  BOOST_CHECK(round_json_object_ismap(obj));

  BOOST_CHECK(round_json_object_delete(obj));
}

BOOST_AUTO_TEST_CASE(JsonArrayObjNew) {
  RoundJSONObject *obj = round_json_array_new();
  BOOST_CHECK(obj);
  BOOST_CHECK(round_json_object_isarray(obj));

  BOOST_CHECK(round_json_object_delete(obj));
}

BOOST_AUTO_TEST_CASE(JsonStringObjNew) {
  const char *val = "test";
  const char *objVal;

  RoundJSONObject *obj = round_json_string_new(val);
  BOOST_CHECK(obj);
  BOOST_CHECK(round_json_object_isstring(obj));
  BOOST_CHECK(round_json_object_getstring(obj, &objVal));
  BOOST_CHECK_EQUAL(objVal, val);

  BOOST_CHECK(round_json_object_delete(obj));
}

BOOST_AUTO_TEST_CASE(JsonIntegerObjNew) {
  long val = 123456;
  long objVal;

  RoundJSONObject *obj = round_json_integer_new(val);
  BOOST_CHECK(obj);
  BOOST_CHECK(round_json_object_isinteger(obj));
  BOOST_CHECK(round_json_object_getinteger(obj, &objVal));
  BOOST_CHECK_EQUAL(objVal, val);

  BOOST_CHECK(round_json_object_delete(obj));
}

BOOST_AUTO_TEST_CASE(JsonReadObjNew) {
  double val = 1.0;
  double objVal;

  RoundJSONObject *obj = round_json_real_new(val);
  BOOST_CHECK(obj);
  BOOST_CHECK(round_json_object_isreal(obj));
  BOOST_CHECK(round_json_object_getreal(obj, &objVal));
  BOOST_CHECK_EQUAL(objVal, val);

  BOOST_CHECK(round_json_object_delete(obj));
}

BOOST_AUTO_TEST_CASE(JsonBoolObjNew) {
  bool val = true;
  bool objVal;

  RoundJSONObject *obj = round_json_bool_new(val);
  BOOST_CHECK(obj);
  BOOST_CHECK(round_json_object_isbool(obj));
  BOOST_CHECK(round_json_object_getbool(obj, &objVal));
  BOOST_CHECK_EQUAL(objVal, val);

  BOOST_CHECK(round_json_object_delete(obj));
}

BOOST_AUTO_TEST_SUITE_END()
