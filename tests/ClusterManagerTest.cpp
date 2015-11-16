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

#include "RoundTest.h"
#include <round/cluster_internal.h>

const char *TEST_CLUSTER_NAME = "testCluster";

BOOST_AUTO_TEST_SUITE(cluster)

BOOST_AUTO_TEST_CASE(ClusterManager)
{
  RoundClusterManager *mgr = round_cluster_manager_new();
  
  BOOST_CHECK(mgr);
  BOOST_CHECK_EQUAL(0, round_cluster_manager_size(mgr));

  char clusterName[32];
  
  RoundCluster *cluster[ROUND_TEST_MAP_SIZE];
  for (int n=0; n<ROUND_TEST_MAP_SIZE; n++) {
    cluster[n] = round_cluster_new();
    snprintf(clusterName, sizeof(clusterName), "%d", n);
    BOOST_CHECK(round_cluster_setname(cluster[n], clusterName));

    BOOST_CHECK(round_cluster_manager_addcluster(mgr, cluster[n]));
    
    BOOST_CHECK_EQUAL((n+1), round_cluster_manager_size(mgr));
    BOOST_CHECK(round_cluster_manager_hascluster(mgr, clusterName));
  }
  
  BOOST_CHECK_EQUAL(ROUND_TEST_MAP_SIZE, round_cluster_manager_size(mgr));
  
  BOOST_CHECK(round_cluster_manager_delete(mgr));
}

BOOST_AUTO_TEST_CASE(ClusterMgrAddNode)
{
  RoundClusterManager *mgr = round_cluster_manager_new();
  BOOST_CHECK(mgr);
  
  RoundNode *node = round_node_local_new();
  
  BOOST_CHECK(round_node_setcluster(node, TEST_CLUSTER_NAME));
  
  BOOST_CHECK(round_cluster_manager_addnode(mgr, node));
  
  BOOST_CHECK(round_cluster_manager_delete(mgr));
}

BOOST_AUTO_TEST_SUITE_END()

