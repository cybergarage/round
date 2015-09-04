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

#include <round/cluster.h>

BOOST_AUTO_TEST_CASE(ClusterNew)
{
  RoundCluster *cluster = round_cluster_new();
  BOOST_CHECK(cluster);
  
  round_cluster_delete(cluster);
}
