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

RoundList* round_list_new()
{
  RoundList* header;

  header = (RoundList*)malloc(sizeof(RoundList));
  if (!header)
    return NULL;

  round_list_header_init(header);

  return header;
}

/****************************************
 * round_list_node_new
 ****************************************/

RoundList* round_list_node_new()
{
  RoundList* header;

  header = (RoundList*)malloc(sizeof(RoundList));
  if (!header)
    return NULL;

  round_list_node_init(header);

  return header;
}

/****************************************
 * round_list_delete
 ****************************************/

bool round_list_delete(RoundList* list)
{
  if (!list)
    return false;

  round_list_clear(list, NULL);

  free(list);

  return true;
}

/****************************************
 * round_list_node_delete
 ****************************************/

bool round_list_node_delete(RoundList* node)
{
  if (!node)
    return false;

  free(node);

  return true;
}

/****************************************
 * round_list_header_init
 ****************************************/

bool round_list_header_init(RoundList* list)
{
  if (!list)
    return false;

  if (!round_object_init((RoundObject *)list))
    return false;
  
  list->headFlag = true;
  list->prev = list->next = list;

  return true;
}

/****************************************
 * round_list_node_init
 ****************************************/

bool round_list_node_init(RoundList* list)
{
  if (!list)
    return false;

  if (!round_object_init((RoundObject *)list))
    return false;
  
  list->headFlag = false;
  list->prev = list->next = list;

  return true;
}

/****************************************
 * round_list_size
 ****************************************/

size_t round_list_size(RoundList* list)
{
  RoundList* node;
  int nodeCnt;

  if (!list)
    return 0;

  nodeCnt = 0;
  for (node = round_list_next(list); node != NULL; node = round_list_next(node))
    nodeCnt++;

  return nodeCnt;
}

/****************************************
 * round_list_getfirst
 ****************************************/

RoundListNode* round_list_getfirst(RoundList* list)
{
  if (!list)
    return NULL;

  return round_list_next(list);
}

/****************************************
 * round_list_getlast
 ****************************************/

RoundListNode* round_list_getlast(RoundList* list)
{
  if (!list)
    return NULL;

  return round_list_prev(list);
}

/****************************************
 * round_list_get
 ****************************************/

RoundListNode* round_list_get(RoundList* list, size_t index)
{
  RoundList* node;
  size_t n;

  if (!list)
    return NULL;

  node = round_list_next(list);
  for (n = 0; n < index; n++) {
    if (!node)
      break;
    node = round_list_next(node);
  }

  return node;
}

/****************************************
 * round_list_insert
 ****************************************/

bool round_list_insert(RoundListNode* prevNode, RoundListNode* node)
{
  if (!prevNode || !node)
    return false;

  round_list_remove(node);

  node->prev = prevNode;
  node->next = prevNode->next;
  prevNode->next->prev = node;
  prevNode->next = node;

  return true;
}

/****************************************
 * round_list_addfirst
 ****************************************/

bool round_list_addfirst(RoundList* list, RoundListNode* node)
{
  if (!list || !node)
    return false;

  if (!list)
    return false;

  round_list_insert(list, node);

  return true;
}

/****************************************
 * round_list_addlast
 ****************************************/

bool round_list_addlast(RoundList* list, RoundListNode* node)
{
  if (!list || !node)
    return false;

  if (!list->prev)
    return false;

  round_list_insert(list->prev, node);

  return true;
}

/****************************************
 * round_list_remove
 ****************************************/

bool round_list_remove(RoundListNode* node)
{
  if (!node)
    return false;

  if (!node->prev || !node->next)
    return false;

  node->prev->next = node->next;
  node->next->prev = node->prev;
  node->prev = node->next = node;

  return true;
}

/****************************************
 * round_list_prev_circular
 ****************************************/

RoundListNode* round_list_prev_circular(RoundListNode* node)
{
  if (!node)
    return NULL;

  if (!node->prev)
    return NULL;

  if (node->prev->headFlag)
    node = node->prev;

  return node->prev;
}

/****************************************
 * round_list_prev
 ****************************************/

RoundListNode* round_list_prev(RoundListNode* node)
{
  if (!node)
    return NULL;

  if (!node->prev)
    return NULL;

  if (node->prev->headFlag)
    return NULL;

  return node->prev;
}

/****************************************
 * round_list_next_circular
 ****************************************/

RoundListNode* round_list_next_circular(RoundListNode* node)
{
  if (!node)
    return NULL;

  if (!node->next)
    return NULL;

  if (node->next->headFlag == true)
    node = node->next;

  return node->next;
}

/****************************************
 * round_list_next
 ****************************************/

RoundListNode* round_list_next(RoundListNode* node)
{
  if (!node)
    return NULL;

  if (!node->next)
    return NULL;

  if (node->next->headFlag == true)
    return NULL;

  return node->next;
}

/****************************************
 * round_list_clear
 ****************************************/

bool round_list_clear(RoundList* headList,
    ROUND_LIST_DESTRUCTORFUNC dstructorFunc)
{
  RoundList* node;

  if (!headList)
    return false;

  node = round_list_next(headList);
  while (node != NULL) {
    round_list_remove(node);
    if (dstructorFunc) {
      dstructorFunc(node);
    }
    else {
      free(node);
    }
    node = round_list_next(headList);
  }

  return true;
}
