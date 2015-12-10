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
#include <round/cluster_internal.h>
#include <round/method/system_method.h>

BOOST_AUTO_TEST_SUITE(node)

BOOST_AUTO_TEST_CASE(LocalNodeNew)
{
  RoundLocalNode* node = round_local_node_new();
  BOOST_CHECK(node);
  BOOST_CHECK(round_local_node_delete(node));
}

BOOST_AUTO_TEST_CASE(LocalNodeVirtualNew)
{
  RoundNode* node = (RoundNode*)round_local_node_new();
  BOOST_CHECK(node);
  BOOST_CHECK(round_node_delete(node));
}

BOOST_AUTO_TEST_CASE(LocalSystemMethod)
{
  RoundLocalNode* node = round_local_node_new();
  BOOST_CHECK(node);

  BOOST_CHECK(round_local_node_isfinalmethod(node, ROUND_SYSTEM_METHOD_SET_METHOD));
  BOOST_CHECK(round_local_node_isfinalmethod(node, ROUND_SYSTEM_METHOD_REMOVE_METHOD));

  BOOST_CHECK(round_local_node_isfinalmethod(node, ROUND_SYSTEM_METHOD_SET_METHOD));

  BOOST_CHECK(!round_local_node_setmethod(node, round_system_method_setmethod_new()));

  BOOST_CHECK(!round_local_node_removemethod(node, ROUND_SYSTEM_METHOD_SET_METHOD));
  BOOST_CHECK(!round_local_node_removemethod(node, ROUND_SYSTEM_METHOD_REMOVE_METHOD));

  BOOST_CHECK(round_local_node_delete(node));
}

BOOST_AUTO_TEST_CASE(LocalNodeRun)
{
  const char* TEST_ADDR = "1.2.3.4";
  const int TEST_PORT = 8080;
  const char* TEST_CLUSTER = "round";

  RoundLocalNode* node = round_local_node_new();
  BOOST_CHECK(node);
  round_local_node_setaddress(node, TEST_ADDR);
  round_local_node_setport(node, TEST_PORT);
  round_local_node_setclustername(node, TEST_CLUSTER);

  BOOST_CHECK(round_local_node_start(node));

  RoundCluster* cluster = round_local_node_getcluster(node);
  BOOST_CHECK(cluster);
  BOOST_CHECK_EQUAL(round_cluster_size(cluster), 1);
  BOOST_CHECK(round_cluster_hasequalnode(cluster, node));

  BOOST_CHECK(round_local_node_stop(node));

  BOOST_CHECK(round_local_node_delete(node));
}

BOOST_AUTO_TEST_SUITE_END()
