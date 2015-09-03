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

#include <round/node.h>

BOOST_AUTO_TEST_CASE(NodeNew)
{
  RoundNode *node = round_node_new();
  BOOST_CHECK(node);
  
  round_node_delete(node);
}
