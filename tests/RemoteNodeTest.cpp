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

#include <round/node_internal.h>

BOOST_AUTO_TEST_CASE(RemoteNodeNew)
{
  RoundRemoteNode *node = round_remote_node_new();
  BOOST_CHECK(node);
  
  BOOST_CHECK(round_remote_node_delete(node));
}
