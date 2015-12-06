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

BOOST_AUTO_TEST_SUITE_END()
