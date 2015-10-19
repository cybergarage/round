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

#include <round/util/list.h>

#define ROUND_TEST_LIST_SIZE 10

BOOST_AUTO_TEST_CASE(ListAdd)
{
  RoundList *nodes = round_list_header_new();
  
  BOOST_CHECK(nodes);
  BOOST_CHECK_EQUAL(0, round_list_size(nodes));
  
  RoundList *node[ROUND_TEST_LIST_SIZE];
  for (int n=0; n<ROUND_TEST_LIST_SIZE; n++) {
    node[n] = round_list_node_new();
    BOOST_CHECK(round_list_add(nodes, node[n]));
    BOOST_CHECK_EQUAL((n+1), round_list_size(nodes));
  }
  
  BOOST_CHECK_EQUAL(ROUND_TEST_LIST_SIZE, round_list_size(nodes));
  
  BOOST_CHECK(round_list_delete(nodes));
}
