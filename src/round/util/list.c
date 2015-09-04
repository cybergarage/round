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
* round_list_header_init
****************************************/

bool round_list_header_init(RoundList *list)
{
  if (!list)
    return false;

  list->headFlag = true;      
  list->prev = list->next = list;

  return true;
}

/****************************************
* round_list_node_init
****************************************/

bool round_list_node_init(RoundList *list)
{
  if (!list)
    return false;

  list->headFlag = false;      
  list->prev = list->next = list;

  return true;
}

/****************************************
* round_list_size
****************************************/

size_t round_list_size(RoundList *headList)
{
  RoundList *list;
  int listCnt;

  if (!headList)
    return 0;

  listCnt = 0;
  for (list = round_list_next(headList); list != NULL; list = round_list_next(list))
    listCnt++;
  
  return listCnt;
}

/****************************************
* round_list_get
****************************************/

RoundList *round_list_get(RoundList *headList, int index)
{
  RoundList *list;
  int n;
  
  if (!headList)
    return NULL;

  list = round_list_next(headList);
  for (n=0; n<index; n++) {
    if (!list)
      break;
    list = round_list_next(list);
  }
  
  return list;
}

/****************************************
* round_list_insert
****************************************/

bool round_list_insert(
RoundList *prevList,
RoundList *list)
{
  if (!prevList|| !list)
    return false;

  list->prev = prevList;
  list->next = prevList->next;
  prevList->next->prev = list;
  prevList->next = list;

  return true;
}

/****************************************
* round_list_add
****************************************/

bool round_list_add(
RoundList *headList,
RoundList *list)
{
  if (!headList || !list)
    return false;

  if (!headList->prev)
    return false;
  
  round_list_insert(headList->prev, list);

  return true;
}

/****************************************
* round_list_remove
****************************************/

bool round_list_remove(RoundList *list)
{
  if (!list)
    return false;

  if (!list->prev || !list->next)
    return false;
  
  list->prev->next = list->next;
  list->next->prev = list->prev;
  list->prev = list->next = list;

  return true;
}

/****************************************
* round_list_prev_circular
****************************************/

RoundList *round_list_prev_circular (
RoundList *list)
{
  if (!list)
    return NULL;

  if (!list->prev)
    return NULL;
  
  if (list->prev->headFlag)
    list = list->prev;

  return list->prev;
}

/****************************************
* round_list_prev
****************************************/

RoundList *round_list_prev(
RoundList *list)
{
  if (!list)
    return NULL;

  if (!list->prev)
    return NULL;
  
  if (list->prev->headFlag)
    return NULL;

  return list->prev;
}

/****************************************
* round_list_next_circular
****************************************/

RoundList *round_list_next_circular(
RoundList *list)
{
  if (!list)
    return NULL;

  if (!list->next)
    return NULL;
  
  if (list->next->headFlag == true)
    list = list->next;
  
  return list->next;
}

/****************************************
 * round_list_gets
 ****************************************/

RoundList *round_list_gets(RoundList *headList)
{
  if (!headList)
    return NULL;
  
  return round_list_next(headList);
}


/****************************************
* round_list_next
****************************************/

RoundList *round_list_next(RoundList *list)
{
  if (!list)
    return NULL;

  if (!list->next)
    return NULL;
  
  if (list->next->headFlag == true)
    return NULL;

  return list->next;
}

/****************************************
* round_list_clear
****************************************/

bool round_list_clear(RoundList *headList, ROUND_LIST_DESTRUCTORFUNC dstructorFunc)
{
  RoundList *list;

  if (!headList)
    return false;

  list = round_list_next(headList);
  while(list != NULL) {
    round_list_remove(list);
    if (dstructorFunc != NULL){
      dstructorFunc(list);
    } else {
      free(list);
    }
    list = round_list_next(headList);
  }

  return true;
}
