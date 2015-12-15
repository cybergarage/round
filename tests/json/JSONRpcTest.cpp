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

#include <round/util/strings.h>
#include <round/util/json_rpc.h>

BOOST_AUTO_TEST_SUITE(rpc)

BOOST_AUTO_TEST_CASE(RpcRequest)
{
  RoundJSONObject* obj = round_json_rpc_request_new();
  BOOST_CHECK(obj);

  const char* value;
  BOOST_CHECK(round_json_rpc_getversion(obj, &value));
  BOOST_CHECK(round_streq(value, ROUND_JSON_RPC_VERSION));

  BOOST_CHECK(round_json_object_delete(obj));
}

BOOST_AUTO_TEST_CASE(RpcResponse)
{
  RoundJSONObject* obj = round_json_rpc_response_new();
  BOOST_CHECK(obj);

  const char* value;
  BOOST_CHECK(round_json_rpc_getversion(obj, &value));
  BOOST_CHECK(round_streq(value, ROUND_JSON_RPC_VERSION));

  BOOST_CHECK(round_json_object_delete(obj));
}

BOOST_AUTO_TEST_CASE(RpcSetMethod)
{
  static const char* RPC_METHOD_PARAM = "{"
                                        "\"name\": \"hello\", "
                                        "\"method\": \"function echo(params) {return params;}\""
                                        "}";

  static const char* RPC_SET_METHOD = "{\"jsonrpc\": \"2.0\","
                                      "\"method\": \"set_method\","
                                      "\"params\": {"
                                      "\"name\": \"hello\", "
                                      "\"method\": \"function echo(params) {return params;}\""
                                      "}, \"id\": 1}";

  RoundJSON* json = round_json_new();
  BOOST_CHECK(json);
  BOOST_CHECK(round_json_parse(json, RPC_SET_METHOD, NULL));

  RoundJSONObject* rootObj = round_json_getrootobject(json);
  BOOST_CHECK(rootObj);
  BOOST_CHECK(round_json_object_ismap(rootObj));

  const char* method;
  BOOST_CHECK(round_json_rpc_getmethod(rootObj, &method));
  BOOST_CHECK(method);
  BOOST_CHECK_EQUAL(method, "set_method");

  const char* id;
  BOOST_CHECK(id);
  BOOST_CHECK(round_json_rpc_getid(rootObj, &id));
  BOOST_CHECK_EQUAL(id, "1");

  const char* params;
  BOOST_CHECK(round_json_rpc_getparams(rootObj, &params));
  BOOST_CHECK(params);
  BOOST_CHECK_EQUAL(params, RPC_METHOD_PARAM);

  round_json_delete(json);
}

BOOST_AUTO_TEST_SUITE_END()
