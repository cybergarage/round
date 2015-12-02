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

BOOST_AUTO_TEST_SUITE(server)

BOOST_AUTO_TEST_CASE(ServerNew) {
  RoundServer *server = round_server_new();
  BOOST_CHECK(server);

  BOOST_CHECK(round_server_start(server));

  BOOST_CHECK(round_server_stop(server));

  BOOST_CHECK(round_server_delete(server));
}

BOOST_AUTO_TEST_SUITE_END()
