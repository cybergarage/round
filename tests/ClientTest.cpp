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
#include <round/server.h>

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

BOOST_AUTO_TEST_CASE(ClientStartAfterServer)
{
  RoundClient* client = round_client_new();
  BOOST_CHECK(client);
  
  RoundServer* server = round_server_new();
  BOOST_CHECK(server);
  
  BOOST_CHECK(round_server_start(server));
  BOOST_CHECK(round_client_start(client));
  
  Round::Test::Sleep();
  while (round_client_getclustersize(client) < 1) {
    BOOST_MESSAGE("Cluster is not found ...");
    BOOST_CHECK(round_client_search(client));
    Round::Test::Sleep();
  }
  
  BOOST_CHECK_EQUAL(round_client_getclustersize(client), 1);
  
  BOOST_CHECK(round_client_stop(client));
  BOOST_CHECK(round_server_stop(server));
  
  BOOST_CHECK(round_client_delete(client));

  BOOST_CHECK(round_server_delete(server));
}

BOOST_AUTO_TEST_SUITE_END()
