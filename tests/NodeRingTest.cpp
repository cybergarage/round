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
#include <round/node_internal.h>

BOOST_AUTO_TEST_SUITE(node)

BOOST_AUTO_TEST_CASE(NodeRingAdd)
{
  RoundNodeRing* nodes = round_node_ring_new();

  BOOST_CHECK(nodes);
  BOOST_CHECK_EQUAL(0, round_node_ring_size(nodes));

  RoundNode* node[ROUND_TEST_MAP_SIZE];
  for (int n = 0; n < ROUND_TEST_MAP_SIZE; n++) {
    node[n] = round_node_new();
    BOOST_CHECK(round_node_ring_add(nodes, node[n]));
    BOOST_CHECK_EQUAL((n + 1), round_node_ring_size(nodes));
  }

  BOOST_CHECK_EQUAL(ROUND_TEST_MAP_SIZE, round_node_ring_size(nodes));

  BOOST_CHECK(round_node_ring_delete(nodes));
}

BOOST_AUTO_TEST_SUITE_END()
