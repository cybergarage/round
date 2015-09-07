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

BOOST_AUTO_TEST_CASE(NodeList)
{
  RoundNodeList *nodes = round_nodelist_new();
  
  BOOST_CHECK(nodes);
  BOOST_CHECK_EQUAL(0, round_nodelist_size(nodes));
  
  RoundNode *node[ROUND_TEST_LIST_CNT];
  for (int n=0; n<ROUND_TEST_LIST_CNT; n++) {
    node[n] = round_node_new();
    BOOST_CHECK(round_nodelist_add(nodes, node[n]));
    BOOST_CHECK_EQUAL((n+1), round_nodelist_size(nodes));
  }
  
  BOOST_CHECK_EQUAL(ROUND_TEST_LIST_CNT, round_nodelist_size(nodes));
  
  BOOST_CHECK(round_nodelist_delete(nodes));
}
