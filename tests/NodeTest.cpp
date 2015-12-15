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

#include <round/const.h>
#include <round/node_internal.h>

BOOST_AUTO_TEST_SUITE(node)

BOOST_AUTO_TEST_CASE(NodeNew)
{
  RoundNode* node = round_node_new();
  BOOST_CHECK(node);

  BOOST_CHECK(!round_node_hasdigest(node));

  BOOST_CHECK(round_node_delete(node));
}

BOOST_AUTO_TEST_CASE(NodeBaseMember)
{
  const char* TEST_NODE_ADDR = "testaddr";
  const int TEST_NODE_PORT = 4649;
  const char* TEST_NODE_CLUSTER = "testcluster";
  const int TEST_NODE_TIMEOUT = 120;

  RoundNode* node = round_node_new();
  BOOST_CHECK(node);

  const char* addr;
  int port;
  const char* cluster;

  BOOST_CHECK(!round_node_getaddress(node, &addr));
  BOOST_CHECK(!round_node_getport(node, &port));
  BOOST_CHECK(round_node_getclustername(node, &cluster));
  BOOST_CHECK(!round_node_hasdigest(node));
  BOOST_CHECK_EQUAL(round_node_getrequesttimeout(node),
      ROUND_JSON_RPC_REQUEST_TIMEOUT_SEC);

  BOOST_CHECK(round_node_setaddress(node, TEST_NODE_ADDR));
  BOOST_CHECK(round_node_setport(node, TEST_NODE_PORT));
  BOOST_CHECK(round_node_setclustername(node, TEST_NODE_CLUSTER));
  BOOST_CHECK(round_node_setrequesttimeout(node, TEST_NODE_TIMEOUT));

  BOOST_CHECK(round_node_getaddress(node, &addr));
  BOOST_CHECK(round_node_getport(node, &port));
  BOOST_CHECK(round_node_getclustername(node, &cluster));
  BOOST_CHECK(round_node_hasdigest(node));
  BOOST_CHECK_EQUAL(round_node_getrequesttimeout(node), TEST_NODE_TIMEOUT);

  BOOST_CHECK_EQUAL(addr, TEST_NODE_ADDR);
  BOOST_CHECK_EQUAL(port, TEST_NODE_PORT);
  BOOST_CHECK_EQUAL(cluster, TEST_NODE_CLUSTER);

  BOOST_CHECK(round_node_delete(node));
}

BOOST_AUTO_TEST_CASE(NodeHash)
{
  RoundNode* node = round_node_new();
  BOOST_CHECK(node);

  char nodeHash[4][ROUND_NODE_DIGEST_LENGTH] = { "", "", "", "" };

  BOOST_CHECK_EQUAL(round_node_hasdigest(node), false);
  round_strcpy(nodeHash[0], round_node_getdigest(node));
  BOOST_CHECK_EQUAL(round_strlen(nodeHash[0]), 0);

  BOOST_CHECK_EQUAL(round_node_setaddress(node, "127.0.0.1"), true);
  BOOST_CHECK_EQUAL(round_node_hasdigest(node), true);
  round_strcpy(nodeHash[1], round_node_getdigest(node));
  BOOST_CHECK_EQUAL(round_strlen(nodeHash[1]), ROUND_NODE_DIGEST_LENGTH);

  BOOST_CHECK_EQUAL(round_node_setport(node, 80), true);
  BOOST_CHECK_EQUAL(round_node_hasdigest(node), true);
  round_strcpy(nodeHash[1], round_node_getdigest(node));
  BOOST_CHECK_EQUAL(round_strlen(nodeHash[1]), ROUND_NODE_DIGEST_LENGTH);
  BOOST_CHECK(round_strcmp(nodeHash[1], nodeHash[0]) != 0);

  BOOST_CHECK_EQUAL(round_node_setaddress(node, "localhost"), true);
  BOOST_CHECK_EQUAL(round_node_hasdigest(node), true);
  round_strcpy(nodeHash[2], round_node_getdigest(node));
  BOOST_CHECK_EQUAL(round_strlen(nodeHash[2]), ROUND_NODE_DIGEST_LENGTH);
  BOOST_CHECK(round_strcmp(nodeHash[2], nodeHash[0]) != 0);
  BOOST_CHECK(round_strcmp(nodeHash[2], nodeHash[1]) != 0);

  BOOST_CHECK_EQUAL(round_node_setport(node, 8080), true);
  BOOST_CHECK_EQUAL(round_node_hasdigest(node), true);
  round_strcpy(nodeHash[3], round_node_getdigest(node));
  BOOST_CHECK_EQUAL(round_strlen(nodeHash[3]), ROUND_NODE_DIGEST_LENGTH);
  BOOST_CHECK(round_strcmp(nodeHash[3], nodeHash[0]) != 0);
  BOOST_CHECK(round_strcmp(nodeHash[3], nodeHash[1]) != 0);
  BOOST_CHECK(round_strcmp(nodeHash[3], nodeHash[2]) != 0);

  BOOST_CHECK(round_node_delete(node));
}

BOOST_AUTO_TEST_SUITE_END()
