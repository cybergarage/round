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

BOOST_AUTO_TEST_CASE(JsonMapSetString)
{
  const char* key = "testKey";
  const char* val = "test";
  const char* objVal;

  RoundJSONObject* obj = round_json_map_new();
  BOOST_CHECK(obj);
  BOOST_CHECK(round_json_object_ismap(obj));

  BOOST_CHECK(round_json_map_setstring(obj, key, val));
  BOOST_CHECK(round_json_map_getstring(obj, key, &objVal));
  BOOST_CHECK_EQUAL(val, objVal);

  BOOST_CHECK(round_json_object_delete(obj));
}

BOOST_AUTO_TEST_CASE(JsonMapSetNullString)
{
  const char* key = "testKey";
  const char* val = NULL;
  const char* objVal;

  RoundJSONObject* obj = round_json_map_new();
  BOOST_CHECK(obj);
  BOOST_CHECK(round_json_object_ismap(obj));

  BOOST_CHECK(round_json_map_setstring(obj, key, val));
  BOOST_CHECK(round_json_map_getstring(obj, key, &objVal));
  BOOST_CHECK_EQUAL(val, objVal);

  BOOST_CHECK(round_json_object_delete(obj));
}

BOOST_AUTO_TEST_CASE(JsonMapSetInt)
{
  const char* key = "testKey";
  long val = 123456;
  long objVal;

  RoundJSONObject* obj = round_json_map_new();
  BOOST_CHECK(obj);
  BOOST_CHECK(round_json_object_ismap(obj));

  BOOST_CHECK(round_json_map_setinteger(obj, key, val));
  BOOST_CHECK(round_json_map_getinteger(obj, key, &objVal));
  BOOST_CHECK_EQUAL(val, objVal);

  BOOST_CHECK(round_json_object_delete(obj));
}

BOOST_AUTO_TEST_CASE(JsonMapSetReal)
{
  const char* key = "testKey";
  double val = 100;
  double objVal;

  RoundJSONObject* obj = round_json_map_new();
  BOOST_CHECK(obj);
  BOOST_CHECK(round_json_object_ismap(obj));

  BOOST_CHECK(round_json_map_setreal(obj, key, val));
  BOOST_CHECK(round_json_map_getreal(obj, key, &objVal));
  BOOST_CHECK_EQUAL(val, objVal);

  BOOST_CHECK(round_json_object_delete(obj));
}

BOOST_AUTO_TEST_CASE(JsonMapSetBool)
{
  const char* key = "testKey";
  bool val = true;
  bool objVal;

  RoundJSONObject* obj = round_json_map_new();
  BOOST_CHECK(obj);
  BOOST_CHECK(round_json_object_ismap(obj));

  BOOST_CHECK(round_json_map_setbool(obj, key, val));
  BOOST_CHECK(round_json_map_getbool(obj, key, &objVal));
  BOOST_CHECK_EQUAL(val, objVal);

  BOOST_CHECK(round_json_object_delete(obj));
}

BOOST_AUTO_TEST_CASE(JsonMapSetObject)
{
  const char* key = "testKey";
  const char* val = NULL;
  const char* objVal;

  RoundJSONObject* obj = round_json_map_new();
  BOOST_CHECK(obj);
  BOOST_CHECK(round_json_object_ismap(obj));

  RoundJSONObject* cobj = round_json_string_new(val);
  BOOST_CHECK(round_json_map_setobject(obj, key, cobj));
  BOOST_CHECK(round_json_object_delete(cobj));

  BOOST_CHECK(round_json_map_getstring(obj, key, &objVal));
  BOOST_CHECK_EQUAL(val, objVal);

  BOOST_CHECK(round_json_object_delete(obj));
}

BOOST_AUTO_TEST_CASE(JsonMapSetRplicaObject)
{
  const char* key = "testKey";
  const char* val = NULL;
  const char* objVal;
  
  RoundJSONObject* obj = round_json_map_new();
  BOOST_CHECK(obj);
  BOOST_CHECK(round_json_object_ismap(obj));
  
  RoundJSONObject* cobj = round_json_string_new(val);
  BOOST_CHECK(round_json_map_setreplicaobject(obj, key, cobj));
  BOOST_CHECK(round_json_object_delete(cobj));
  
  BOOST_CHECK(round_json_map_getstring(obj, key, &objVal));
  BOOST_CHECK_EQUAL(val, objVal);
  
  BOOST_CHECK(round_json_object_delete(obj));
}

BOOST_AUTO_TEST_SUITE_END()
