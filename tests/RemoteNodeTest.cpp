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

BOOST_AUTO_TEST_SUITE(node)

BOOST_AUTO_TEST_CASE(RemoteNodeNew)
{
  RoundRemoteNode *node = round_remote_node_new();
  BOOST_CHECK(node);
  
  BOOST_CHECK(round_remote_node_delete(node));
}

BOOST_AUTO_TEST_CASE(RemoteNodeCopy)
{
  const char *TEST_ADDR = "1.2.3.4";
  const int TEST_PORT = 8080;
  const char *TEST_CLUSTER = "round";
  
  RoundRemoteNode *node0 = round_remote_node_new();
  BOOST_CHECK(node0);
  round_remote_node_setaddress(node0, TEST_ADDR);
  round_remote_node_setport(node0, TEST_PORT);
  round_remote_node_setclustername(node0, TEST_CLUSTER);
  
  RoundRemoteNode *node1 = round_remote_node_copy((RoundNode *)node0);
  BOOST_CHECK(node1);
  
  BOOST_CHECK(round_node_equals((RoundNode *)node0, (RoundNode *)node1));
  
  BOOST_CHECK(round_remote_node_delete(node0));
  BOOST_CHECK(round_remote_node_delete(node1));
}

BOOST_AUTO_TEST_SUITE_END()
