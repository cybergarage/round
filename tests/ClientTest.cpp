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

#include <round/client_internal.h>
#include <round/server_internal.h>

#include "RoundTest.h"

BOOST_AUTO_TEST_SUITE(client)

BOOST_AUTO_TEST_CASE(ClientNew)
{
  RoundClient* client = round_client_new();
  BOOST_CHECK(client);

  BOOST_CHECK(round_client_start(client));
  BOOST_CHECK(round_client_stop(client));

  BOOST_CHECK(round_client_delete(client));
}

#if defined(ROUND_ENABLE_FINDER)

BOOST_AUTO_TEST_CASE(ClientStartAfterServer)
{
  RoundServer* server = round_server_new();
  BOOST_CHECK(server);
  round_server_setfinderenabled(server, false);
  BOOST_CHECK(!round_server_isfinderenabled(server));
  BOOST_CHECK(round_server_start(server));
  
  RoundClient* client = round_client_new();
  BOOST_CHECK(client);
  BOOST_CHECK(round_client_start(client));

  // Check Cluster

  ROUND_TEST_RETRY_COUNT_INIT();
  Round::Test::Sleep();
  while (round_client_getclustersize(client) < 1) {
    BOOST_TEST_MESSAGE("Cluster is not found ...");
    ROUND_TEST_RETRY_COUNT_CHECK();
    BOOST_CHECK(round_client_search(client));
    Round::Test::Sleep();
  }
  BOOST_CHECK_EQUAL(round_client_getclustersize(client), 1);

  // Check Node

  RoundCluster* cluster = round_client_getclusters(client);
  BOOST_CHECK(cluster);
  RoundNode* node = round_cluster_getnodes(cluster);
  BOOST_CHECK(node);
  BOOST_CHECK(round_node_equals(node, round_server_getnode(server)));

  BOOST_CHECK(round_client_stop(client));
  BOOST_CHECK(round_server_stop(server));

  BOOST_CHECK(round_client_delete(client));

  BOOST_CHECK(round_server_delete(server));
}

BOOST_AUTO_TEST_CASE(ClientStartBeforeServer)
{
  RoundClient* client = round_client_new();
  BOOST_CHECK(client);

  RoundServer* server = round_server_new();
  BOOST_CHECK(server);

  BOOST_CHECK(round_client_start(client));
  BOOST_CHECK(round_server_start(server));

  // Check Cluster

  ROUND_TEST_RETRY_COUNT_INIT();
  Round::Test::Sleep();
  while (round_client_getclustersize(client) < 1) {
    BOOST_TEST_MESSAGE("Cluster is not found ...");
    ROUND_TEST_RETRY_COUNT_CHECK();
    Round::Test::Sleep();
  }
  BOOST_CHECK_EQUAL(round_client_getclustersize(client), 1);

  // Check Node

  RoundCluster* cluster = round_client_getclusters(client);
  BOOST_CHECK(cluster);
  RoundNode* node = round_cluster_getnodes(cluster);
  BOOST_CHECK(node);
  BOOST_CHECK(round_node_equals(node, round_server_getnode(server)));

  BOOST_CHECK(round_server_stop(server));
  BOOST_CHECK(round_client_stop(client));

  BOOST_CHECK(round_client_delete(client));

  BOOST_CHECK(round_server_delete(server));
}

#endif

BOOST_AUTO_TEST_SUITE_END()
