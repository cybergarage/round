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

BOOST_AUTO_TEST_SUITE(list)

#define ROUND_TEST_LIST_SIZE 10

typedef struct {
  ROUND_LIST_STRUCT_MEMBERS
  int number;
} RoundTestNumberNode;

RoundTestNumberNode* round_test_numbernode_new(int value)
{
  RoundTestNumberNode* node;

  node = (RoundTestNumberNode*)malloc(sizeof(RoundTestNumberNode));

  if (!node)
    return NULL;
  
  round_list_node_init((RoundListNode *)node);
  node->number = value;

  return node;
}

int round_test_numbernode_comp(RoundTestNumberNode* thisNode, RoundTestNumberNode* otherNode)
{
  if (thisNode->number == otherNode->number)
    return RoundListNodeCompareSame;

  if (thisNode->number < otherNode->number)
    return RoundListNodeCompareGreater;

  return RoundListNodeCompareLess;
}

BOOST_AUTO_TEST_CASE(OrderedListAddAsc)
{
  RoundOrderedList* list = round_ordered_list_new();
  BOOST_CHECK(list);

  round_ordered_list_setcmpfunc(list, round_test_numbernode_comp);

  BOOST_CHECK_EQUAL(0, round_ordered_list_size(list));

  RoundTestNumberNode* nodes[ROUND_TEST_LIST_SIZE];
  for (int n = 0; n < ROUND_TEST_LIST_SIZE; n++) {
    nodes[n] = round_test_numbernode_new(n);
    BOOST_CHECK(nodes[n]);
    BOOST_CHECK(round_ordered_list_add(list, (RoundListNode*)nodes[n]));
    BOOST_CHECK_EQUAL((n + 1), round_ordered_list_size(list));
  }

  BOOST_CHECK_EQUAL(ROUND_TEST_LIST_SIZE, round_ordered_list_size(list));

  for (int n = 0; n < ROUND_TEST_LIST_SIZE; n++) {
    RoundTestNumberNode* node = (RoundTestNumberNode*)round_ordered_list_get(list, n);
    BOOST_CHECK(node);
    BOOST_CHECK_EQUAL(node, nodes[n]);
  }

  BOOST_CHECK_EQUAL(ROUND_TEST_LIST_SIZE, round_ordered_list_size(list));

  BOOST_CHECK(round_ordered_list_delete(list));
}

BOOST_AUTO_TEST_CASE(OrderedListAddDesc)
{
  RoundOrderedList* list = round_ordered_list_new();
  BOOST_CHECK(list);

  round_ordered_list_setcmpfunc(list, round_test_numbernode_comp);

  BOOST_CHECK_EQUAL(0, round_ordered_list_size(list));

  RoundTestNumberNode* nodes[ROUND_TEST_LIST_SIZE];
  for (int n = 0; n < ROUND_TEST_LIST_SIZE; n++) {
    int idx = ROUND_TEST_LIST_SIZE - n - 1;
    nodes[idx] = round_test_numbernode_new(idx);
    BOOST_CHECK(nodes[idx]);
    BOOST_CHECK(round_ordered_list_add(list, (RoundListNode*)nodes[idx]));
    BOOST_CHECK_EQUAL((n + 1), round_ordered_list_size(list));
  }

  BOOST_CHECK_EQUAL(ROUND_TEST_LIST_SIZE, round_ordered_list_size(list));

  for (int n = 0; n < ROUND_TEST_LIST_SIZE; n++) {
    RoundTestNumberNode* node = (RoundTestNumberNode*)round_ordered_list_get(list, n);
    BOOST_CHECK(node);
    BOOST_CHECK_EQUAL(node, nodes[n]);
  }

  BOOST_CHECK_EQUAL(ROUND_TEST_LIST_SIZE, round_ordered_list_size(list));

  BOOST_CHECK(round_ordered_list_delete(list));
}

BOOST_AUTO_TEST_CASE(OrderedListRemove)
{
  RoundOrderedList* list = round_ordered_list_new();
  BOOST_CHECK(list);

  round_ordered_list_setcmpfunc(list, round_test_numbernode_comp);

  BOOST_CHECK_EQUAL(0, round_ordered_list_size(list));

  RoundTestNumberNode* nodes[ROUND_TEST_LIST_SIZE];
  for (int n = 0; n < ROUND_TEST_LIST_SIZE; n++) {
    nodes[n] = round_test_numbernode_new(n);
    BOOST_CHECK(nodes[n]);
    BOOST_CHECK(round_ordered_list_add(list, (RoundListNode*)nodes[n]));
    BOOST_CHECK_EQUAL((n + 1), round_ordered_list_size(list));
  }

  BOOST_CHECK_EQUAL(ROUND_TEST_LIST_SIZE, round_ordered_list_size(list));

  for (int n = 0; n < ROUND_TEST_LIST_SIZE; n++) {
    BOOST_CHECK(round_ordered_list_remove(nodes[n]));
    BOOST_CHECK_EQUAL((ROUND_TEST_LIST_SIZE - (n + 1)),
        round_ordered_list_size(list));
  }

  BOOST_CHECK_EQUAL(0, round_ordered_list_size(list));

  BOOST_CHECK(round_ordered_list_delete(list));
}

BOOST_AUTO_TEST_SUITE_END()
