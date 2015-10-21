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

#include <round/util/json.h>
#include <round/util/strings.h>

BOOST_AUTO_TEST_SUITE(json)

////////////////////////////////////////////////////////////
// Array
////////////////////////////////////////////////////////////

BOOST_AUTO_TEST_CASE(JSONParseIntArray)
{
  RoundJSON *json = round_json_new();
  BOOST_CHECK(json);
  
  BOOST_CHECK(round_json_parse(json, "[0, 1, 2]", NULL));

  char path[8];
  for (int n=0; n<3; n++) {
    long value;
    sprintf(path, "%d", n);
    BOOST_CHECK(round_json_getintegerforpath(json, path, &value));
    BOOST_CHECK_EQUAL(value, n);
  }
  
  BOOST_CHECK(round_json_delete(json));
}

BOOST_AUTO_TEST_CASE(JSONParseStrArray)
{
  RoundJSON *json = round_json_new();
  BOOST_CHECK(json);
  
  BOOST_CHECK(round_json_parse(json, "[\"milk\", \"bread\", \"eggs\"]", NULL));
  
  const char *value;
  
  BOOST_CHECK(round_json_getstringforpath(json, "0", &value));
  BOOST_CHECK_EQUAL("milk", value);
  
  BOOST_CHECK(round_json_getstringforpath(json, "1", &value));
  BOOST_CHECK_EQUAL("bread", value);

  BOOST_CHECK(round_json_getstringforpath(json, "2", &value));
  BOOST_CHECK_EQUAL("eggs", value);
  
  BOOST_CHECK(round_json_delete(json));
}

BOOST_AUTO_TEST_CASE(JSONParseStrArrayWithSpace)
{
  RoundJSON *json = round_json_new();
  BOOST_CHECK(json);
  
  BOOST_CHECK(round_json_parse(json, "[\"name\", \"John Smith\"]", NULL));
  
  const char *value;
  
  BOOST_CHECK(round_json_getstringforpath(json, "0", &value));
  BOOST_CHECK_EQUAL("name", value);
  
  BOOST_CHECK(round_json_getstringforpath(json, "1", &value));
  BOOST_CHECK_EQUAL("John Smith", value);
  
  BOOST_CHECK(round_json_delete(json));
}

////////////////////////////////////////////////////////////
// Dictionary
////////////////////////////////////////////////////////////

BOOST_AUTO_TEST_CASE(JSONParseIntDict)
{
  RoundJSON *json = round_json_new();
  BOOST_CHECK(json);
  
  BOOST_CHECK(round_json_parse(json, "{\"a\": 1, \"b\": 2, \"c\": 3}", NULL));
  
  long value;
  
  BOOST_CHECK(round_json_getintegerforpath(json, "a", &value));
  BOOST_CHECK_EQUAL(1, value);
  
  BOOST_CHECK(round_json_getintegerforpath(json, "b", &value));
  BOOST_CHECK_EQUAL(2, value);
  
  BOOST_CHECK(round_json_getintegerforpath(json, "c", &value));
  BOOST_CHECK_EQUAL(3, value);
  
  BOOST_CHECK(round_json_delete(json));
}

BOOST_AUTO_TEST_CASE(JSONParseStrDict)
{
  RoundJSON *json = round_json_new();
  BOOST_CHECK(json);
  
  BOOST_CHECK(round_json_parse(json, "{\"name\": \"John Smith\", \"age\": 32}", NULL));

  union MixValue {
    const char *s;
    long i;
  };
  union MixValue value;
  
  BOOST_CHECK(round_json_getstringforpath(json, "name", &value.s));
  BOOST_CHECK_EQUAL("John Smith", value.s);
  
  BOOST_CHECK(round_json_getintegerforpath(json, "age", &value.i));
  BOOST_CHECK_EQUAL(32, value.i);
  
  BOOST_CHECK(round_json_delete(json));
}

////////////////////////////////////////////////////////////
// Dictionary in Array
////////////////////////////////////////////////////////////

BOOST_AUTO_TEST_CASE(JSONParseDictInArray)
{
  RoundJSON *json = round_json_new();
  BOOST_CHECK(json);
  
  BOOST_CHECK(round_json_parse(json, "[ {\"age\": 32,\"name\":\"John Smith\"},{\"age\": 31,\"name\":\"John Lennon\"} ]", NULL));
  
  union MixValue {
    const char *s;
    long i;
  };
  union MixValue value;
  
  BOOST_CHECK(round_json_getstringforpath(json, "0/name", &value.s));
  BOOST_CHECK_EQUAL("John Smith", value.s);
  
  BOOST_CHECK(round_json_getintegerforpath(json, "0/age", &value.i));
  BOOST_CHECK_EQUAL(32, value.i);
  
  BOOST_CHECK(round_json_getstringforpath(json, "1/name", &value.s));
  BOOST_CHECK_EQUAL("John Lennon", value.s);
  
  BOOST_CHECK(round_json_getintegerforpath(json, "1/age", &value.i));
  BOOST_CHECK_EQUAL(31, value.i);
  
  BOOST_CHECK(round_json_delete(json));
}

////////////////////////////////////////////////////////////
// Array in Dictionary
////////////////////////////////////////////////////////////

BOOST_AUTO_TEST_CASE(JSONParseArrayInDict)
{
  RoundJSON *json = round_json_new();
  BOOST_CHECK(json);
  
  BOOST_CHECK(round_json_parse(json, "{\"phoneNumber\": [\"212 555-1234\", \"646 555-4567\"]}", NULL));
  
  union MixValue {
    const char *s;
    int i;
  };
  const char *value;
  
  BOOST_CHECK(round_json_getstringforpath(json, "phoneNumber/0", &value));
  BOOST_CHECK_EQUAL("212 555-1234", value);
  
  BOOST_CHECK(round_json_getstringforpath(json, "phoneNumber/1", &value));
  BOOST_CHECK_EQUAL("646 555-4567", value);
  
  BOOST_CHECK(round_json_delete(json));
}

////////////////////////////////////////////////////////////
// Other
////////////////////////////////////////////////////////////

BOOST_AUTO_TEST_CASE(JSONParsePopObject)
{
  RoundJSON *json = round_json_new();
  BOOST_CHECK(json);
  
  BOOST_CHECK(round_json_parse(json, "[0, 1, 2]", NULL));

  RoundJSONObject *rootObj = round_json_poprootobject(json);
  BOOST_CHECK(rootObj);
  BOOST_CHECK(!round_json_getrootobject(json));
  
  BOOST_CHECK(round_json_delete(json));

  BOOST_CHECK(round_json_object_delete(rootObj));
}

BOOST_AUTO_TEST_SUITE_END()
