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

#include <round/node_internal.h>

BOOST_AUTO_TEST_CASE(NodeNew)
{
  RoundNode *node = round_node_new();
  BOOST_CHECK(node);
  
  BOOST_CHECK(round_node_delete(node));
}

BOOST_AUTO_TEST_CASE(NodeBaseMember)
{
  const char *TEST_NODE_ADDR = "testaddr";
  const int TEST_NODE_PORT = 4649;
  const char *TEST_NODE_CLUSTER = "testcluster";
  const int TEST_NODE_TIMEOUT = 120;
  
  RoundNode *node = round_node_new();
  BOOST_CHECK(node);
  
  RoundError *err;
  const char *addr;
  int port;
  const char *cluster;
  
  BOOST_CHECK(!round_node_getaddress(node, &addr, err));
  BOOST_CHECK(!round_node_getport(node, &port, err));
  BOOST_CHECK(!round_node_getcluster(node, &cluster, err));
  BOOST_CHECK_EQUAL(round_node_getrequesttimeout(node), ROUNDC_JSON_RPC_REQUEST_TIMEOUT_SEC);
  
  BOOST_CHECK(round_node_setaddress(node, TEST_NODE_ADDR));
  BOOST_CHECK(round_node_setport(node, TEST_NODE_PORT));
  BOOST_CHECK(round_node_setcluster(node, TEST_NODE_CLUSTER));
  BOOST_CHECK(round_node_setrequesttimeout(node, TEST_NODE_TIMEOUT));

  BOOST_CHECK(round_node_getaddress(node, &addr, err));
  BOOST_CHECK(round_node_getport(node, &port, err));
  BOOST_CHECK(round_node_getcluster(node, &cluster, err));
  BOOST_CHECK_EQUAL(round_node_getrequesttimeout(node), TEST_NODE_TIMEOUT);
  
  BOOST_CHECK_EQUAL(addr, TEST_NODE_ADDR);
  BOOST_CHECK_EQUAL(port, TEST_NODE_PORT);
  BOOST_CHECK_EQUAL(cluster, TEST_NODE_CLUSTER);
  
  BOOST_CHECK(round_node_delete(node));
}
