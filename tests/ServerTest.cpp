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

#include <round/server.h>
#include <round/client.h>

#include "RoundTest.h"

#define ROUND_TEST_SERVER_CNT 10

BOOST_AUTO_TEST_SUITE(server)

BOOST_AUTO_TEST_CASE(ServerStart)
{
  RoundServer* server = round_server_new();
  BOOST_CHECK(server);

  BOOST_CHECK(round_server_start(server));
  BOOST_CHECK(round_server_stop(server));

  BOOST_CHECK(round_server_delete(server));
}

BOOST_AUTO_TEST_CASE(MultipleServerStart)
{
  RoundClient* client = round_client_new();
  BOOST_CHECK(client);
  BOOST_CHECK(round_client_start(client));

  RoundServer* server[ROUND_TEST_SERVER_CNT];

  for (int n = 0; n < ROUND_TEST_SERVER_CNT; n++) {
    server[n] = round_server_new();
    BOOST_CHECK(server[n]);
    BOOST_CHECK(round_server_start(server[n]));
    Round::Test::Sleep();
    while (round_client_getclustersize(client) < (n + 1)) {
      Round::Test::Sleep();
    }
    BOOST_CHECK_EQUAL(round_client_getclustersize(client), (n + 1));
  }

  BOOST_CHECK_EQUAL(round_client_getclustersize(client), ROUND_TEST_SERVER_CNT);

  for (int n = 0; n < ROUND_TEST_SERVER_CNT; n++) {
    BOOST_CHECK(round_server_stop(server[n]));
    BOOST_CHECK(round_server_delete(server[n]));
  }

  BOOST_CHECK(round_client_stop(client));
  BOOST_CHECK(round_client_delete(client));
}

BOOST_AUTO_TEST_SUITE_END()
