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

BOOST_AUTO_TEST_SUITE(list)

BOOST_AUTO_TEST_CASE(ListAdd)
{
  RoundList *list = round_list_new();
  
  BOOST_CHECK(list);
  BOOST_CHECK_EQUAL(0, round_list_size(list));
  
  RoundList *nodes[ROUND_TEST_LIST_SIZE];
  for (int n=0; n<ROUND_TEST_LIST_SIZE; n++) {
    nodes[n] = round_list_node_new();
    BOOST_CHECK(round_list_add(list, nodes[n]));
    BOOST_CHECK_EQUAL((n+1), round_list_size(list));
  }
  
  for (int n=0; n<ROUND_TEST_LIST_SIZE; n++) {
    BOOST_CHECK_EQUAL(nodes[n], round_list_get(list, n));
  }

  RoundListNode *node = round_list_gets(list);
  for (int n=0; n<ROUND_TEST_LIST_SIZE; n++) {
    BOOST_CHECK_EQUAL(nodes[n], node);
    node = round_list_next(node);
  }

  BOOST_CHECK_EQUAL(ROUND_TEST_LIST_SIZE, round_list_size(list));
  
  BOOST_CHECK(round_list_delete(list));
}

BOOST_AUTO_TEST_CASE(ListAddSameNode)
{
  RoundList *list = round_list_new();
  
  BOOST_CHECK(list);
  BOOST_CHECK_EQUAL(0, round_list_size(list));
  
  RoundList *nodes[ROUND_TEST_LIST_SIZE];
  for (int n=0; n<ROUND_TEST_LIST_SIZE; n++) {
    nodes[n] = round_list_node_new();
  }
  
  for (int n=0; n<ROUND_TEST_LIST_SIZE; n++) {
    BOOST_CHECK(round_list_add(list, nodes[n]));
    BOOST_CHECK_EQUAL((n+1), round_list_size(list));
  }
  for (int n=0; n<ROUND_TEST_LIST_SIZE; n++) {
    BOOST_CHECK_EQUAL(nodes[n], round_list_get(list, n));
  }
  BOOST_CHECK_EQUAL(ROUND_TEST_LIST_SIZE, round_list_size(list));
 
  for (int n=0; n<ROUND_TEST_LIST_SIZE; n++) {
    BOOST_CHECK(round_list_add(list, nodes[n]));
    BOOST_CHECK_EQUAL(ROUND_TEST_LIST_SIZE, round_list_size(list));
  }
  for (int n=0; n<ROUND_TEST_LIST_SIZE; n++) {
    BOOST_CHECK_EQUAL(nodes[n], round_list_get(list, n));
  }
  BOOST_CHECK_EQUAL(ROUND_TEST_LIST_SIZE, round_list_size(list));
  
  BOOST_CHECK(round_list_delete(list));
}

BOOST_AUTO_TEST_CASE(ListRemove)
{
  RoundList *list = round_list_new();
  
  BOOST_CHECK(list);
  BOOST_CHECK_EQUAL(0, round_list_size(list));
  
  RoundList *nodes[ROUND_TEST_LIST_SIZE];
  for (int n=0; n<ROUND_TEST_LIST_SIZE; n++) {
    nodes[n] = round_list_node_new();
    BOOST_CHECK(round_list_add(list, nodes[n]));
  }
  
  BOOST_CHECK_EQUAL(ROUND_TEST_LIST_SIZE, round_list_size(list));

  RoundListNode *node = round_list_gets(list);
  for (int n=0; n<ROUND_TEST_LIST_SIZE; n++) {
    BOOST_CHECK_EQUAL(nodes[n], node);
    BOOST_CHECK(round_list_remove(node));
    BOOST_CHECK(round_list_node_delete(node));
    node = round_list_gets(list);
  }
  
  BOOST_CHECK_EQUAL(0, round_list_size(list));
  
  BOOST_CHECK(round_list_delete(list));
}

BOOST_AUTO_TEST_SUITE_END()
