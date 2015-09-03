/******************************************************************
 *
 * Round SDK for C
 *
 * Copyright (C) Satoshi Konno 2015
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <boost/test/unit_test.hpp>

#include <round/client.h>

BOOST_AUTO_TEST_CASE(ClientNew)
{
  RoundClient *c = round_client_new();
  BOOST_CHECK(c);
  
  BOOST_CHECK(round_client_delete(c));
}
