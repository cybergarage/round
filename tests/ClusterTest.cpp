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

#include <round/cluster_internal.h>

BOOST_AUTO_TEST_SUITE(cluster)

const char* TEST_CLUSTER_NAME = "testCluster";
const char* TEST_CLUSTER_NAME_2 = "testCluster1";
const char* TEST_CLUSTER_NAME_3 = "testCluster2";

BOOST_AUTO_TEST_CASE(ClusterNew)
{
  RoundCluster* cluster = round_cluster_new();
  BOOST_CHECK(cluster);
  round_cluster_delete(cluster);
}

BOOST_AUTO_TEST_CASE(ClusterName)
{
  RoundCluster* cluster = round_cluster_new();
  BOOST_CHECK(round_cluster_setname(cluster, TEST_CLUSTER_NAME));

  BOOST_CHECK_EQUAL(TEST_CLUSTER_NAME, round_cluster_getname(cluster));
  BOOST_CHECK(round_cluster_isname(cluster, TEST_CLUSTER_NAME));

  BOOST_CHECK(!round_cluster_isname(cluster, TEST_CLUSTER_NAME_2));
  BOOST_CHECK(!round_cluster_isname(cluster, TEST_CLUSTER_NAME_3));

  round_cluster_delete(cluster);
}

BOOST_AUTO_TEST_CASE(ClusterCopyTest)
{
  /*
  Round::Cluster cluster1(TEST_CLUSTER_NAME_2);
  Round::Cluster cluster2(&cluster1);
  BOOST_CHECK(cluster1.equals(&cluster2));
   */
}

BOOST_AUTO_TEST_CASE(ClusterEqualTest)
{
  RoundCluster* cluster1 = round_cluster_new();
  BOOST_CHECK(round_cluster_setname(cluster1, TEST_CLUSTER_NAME));
  BOOST_CHECK(round_cluster_equals(cluster1, cluster1));

  RoundCluster* cluster2 = round_cluster_new();
  BOOST_CHECK(round_cluster_setname(cluster2, TEST_CLUSTER_NAME_2));
  BOOST_CHECK(!round_cluster_equals(cluster1, cluster2));
  BOOST_CHECK(!round_cluster_equals(cluster2, cluster1));

  RoundCluster* cluster3 = round_cluster_new();
  BOOST_CHECK(round_cluster_setname(cluster3, TEST_CLUSTER_NAME));
  BOOST_CHECK(round_cluster_equals(cluster1, cluster3));
  BOOST_CHECK(round_cluster_equals(cluster3, cluster1));

  round_cluster_delete(cluster1);
  round_cluster_delete(cluster2);
  round_cluster_delete(cluster3);
}

BOOST_AUTO_TEST_CASE(ClusterAddNode)
{
  RoundCluster* cluster = round_cluster_new();
  BOOST_CHECK(cluster);

  RoundNode* node = round_node_local_new();
  BOOST_CHECK(round_cluster_addnode(cluster, node));

  round_cluster_delete(cluster);
}

BOOST_AUTO_TEST_CASE(ClusterAddNodes)
{
  RoundCluster* cluster = round_cluster_new();
  BOOST_CHECK(cluster);

  RoundNode* node = round_node_local_new();

  BOOST_CHECK(round_cluster_addnode(cluster, node));
  BOOST_CHECK(round_cluster_addnode(cluster, node));

  round_cluster_delete(cluster);
}

BOOST_AUTO_TEST_CASE(ClusterGetNode)
{
  RoundCluster* cluster = round_cluster_new();
  BOOST_CHECK(cluster);

  RoundNode* node = round_node_local_new();
  BOOST_CHECK(round_local_node_setaddress(node, "127.0.0.1"));
  BOOST_CHECK(round_local_node_setport(node, 80));
  BOOST_CHECK(round_cluster_addnode(cluster, node));

  RoundNode* foundNode;

  foundNode = round_cluster_getnodes(cluster);
  BOOST_CHECK(foundNode);
  BOOST_CHECK(round_node_equals(node, foundNode));

  foundNode = round_cluster_getnode(cluster, 0);
  BOOST_CHECK(foundNode);
  BOOST_CHECK(round_node_equals(node, foundNode));

  foundNode = round_cluster_getnodebyrandom(cluster);
  BOOST_CHECK(foundNode);
  BOOST_CHECK(round_node_equals(node, foundNode));

  const char *nodeId;
  BOOST_CHECK(round_node_getid(node, &nodeId));
  foundNode = round_cluster_getnodebyid(cluster, nodeId);
  BOOST_CHECK(foundNode);
  BOOST_CHECK(round_node_equals(node, foundNode));

  round_cluster_delete(cluster);
}

BOOST_AUTO_TEST_SUITE_END()
