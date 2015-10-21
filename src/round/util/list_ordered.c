/******************************************************************
 *
 * Round for C
 *
 * Copyright (C) Satoshi Konno 2015
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <round/util/list.h>

/****************************************
 * round_ordered_list_add
 ****************************************/

RoundOrderedList *round_ordered_list_new()
{
  RoundOrderedList *list;
  
  list = (RoundOrderedList *)malloc(sizeof(RoundOrderedList));
  if (!list)
    return NULL;
  
  list->sortedList = round_list_new();
  if (!list->sortedList) {
    round_ordered_list_delete(list);
    return false;
  }
  
  return list;
}

/****************************************
 * round_ordered_list_delete
 ****************************************/

bool round_ordered_list_delete(RoundOrderedList *list)
{
  if (!list)
    return false;

  if (list->sortedList) {
    round_list_delete(list->sortedList);
    list->sortedList = NULL;
  }
  
  return true;
}

/****************************************
 * round_ordered_list_add
 ****************************************/

bool round_ordered_list_add(RoundOrderedList *list, RoundListNode *newNode)
{
  RoundList *node;

  if (!list || !list->cmpFunc)
    return false;
  
  // TODO : Fix the O(n) algorithm
  
  for (node = round_ordered_list_getlast(list); node != NULL; node = round_list_prev(node)) {
    if (list->cmpFunc(node, newNode) == RoundListNodeCompareGreater) {
      return round_list_insert(node, newNode);
    }
  }
  
  return round_list_addfirst(list->sortedList, newNode);
}