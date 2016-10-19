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

#include <round/server_internal.h>
#include <round/client_internal.h>

#include "RoundTest.h"

#define ROUND_TEST_SERVER_CNT 10

BOOST_AUTO_TEST_SUITE(server)

BOOST_AUTO_TEST_CASE(ServerStart)
{
  RoundServer* server = round_server_new();
  BOOST_CHECK(server);

#if defined(ROUND_ENABLE_FINDER)
  BOOST_CHECK(round_server_isfinderenabled(server));
#endif
  
  BOOST_CHECK(round_server_start(server));
  BOOST_CHECK(round_server_stop(server));

  BOOST_CHECK(round_server_delete(server));
}

#if defined(ROUND_ENABLE_FINDER)

BOOST_AUTO_TEST_CASE(MultipleServerStart)
{
  RoundClient* client = round_client_new();
  BOOST_CHECK(client);
  BOOST_CHECK(round_client_start(client));

  RoundServer* server[ROUND_TEST_SERVER_CNT];

  ROUND_TEST_RETRY_COUNT_INIT();
  for (int n = 0; n < ROUND_TEST_SERVER_CNT; n++) {
    server[n] = round_server_new();
    BOOST_CHECK(server[n]);
    BOOST_CHECK(round_server_start(server[n]));
    Round::Test::Sleep();

    RoundLocalNode* node = round_server_getlocalnode(server[n]);
    const char* clusterName;
    BOOST_CHECK(round_local_node_getclustername(node, &clusterName));
    RoundCluster* cluster = round_client_getclusterbyname(client, clusterName);
    while (!cluster) {
      BOOST_TEST_MESSAGE( "Server[" << n << "] couldn't find the specified cluster (" << clusterName << ")");
      ROUND_TEST_RETRY_COUNT_CHECK();
      Round::Test::Sleep();
      cluster = round_client_getclusterbyname(client, clusterName);
    }
    BOOST_CHECK(cluster);

    if (!cluster)
      return;
    
    while (round_cluster_size(cluster) < (n + 1)) {
      BOOST_TEST_MESSAGE("Searching server[" << n << "]");
      BOOST_CHECK(round_client_search(client));
      Round::Test::Sleep();
    }
    BOOST_CHECK_EQUAL(round_cluster_size(cluster), (n + 1));
  }

  for (int n = 0; n < ROUND_TEST_SERVER_CNT; n++) {
    BOOST_CHECK(round_server_stop(server[n]));
    BOOST_CHECK(round_server_delete(server[n]));
  }

  BOOST_CHECK(round_client_stop(client));
  BOOST_CHECK(round_client_delete(client));
}

#endif

BOOST_AUTO_TEST_SUITE_END()
