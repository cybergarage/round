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

BOOST_AUTO_TEST_CASE(ClusterList)
{
  RoundClusterList *clusters = round_clusterlist_new();
  
  BOOST_CHECK(clusters);
  BOOST_CHECK_EQUAL(0, round_clusterlist_size(clusters));
  
  RoundCluster *cluster[ROUND_TEST_LIST_CNT];
  for (int n=0; n<ROUND_TEST_LIST_CNT; n++) {
    cluster[n] = round_cluster_new();
    BOOST_CHECK(round_clusterlist_add(clusters, cluster[n]));
    BOOST_CHECK_EQUAL((n+1), round_clusterlist_size(clusters));
  }
  
  BOOST_CHECK_EQUAL(ROUND_TEST_LIST_CNT, round_clusterlist_size(clusters));
  
  BOOST_CHECK(round_clusterlist_delete(clusters));
}
