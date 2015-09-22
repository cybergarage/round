/******************************************************************
 *
 * Round for C
 *
 * Copyright (C) Satoshi Konno 2015
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <round/node_internal.h>

/****************************************
* round_local_node_new
****************************************/

RoundLocalNode *round_local_node_new(void)
{
  RoundLocalNode *node;

  node = (RoundLocalNode *)malloc(sizeof(RoundLocalNode));

  if (!node)
    return NULL;

  round_node_init((RoundNode *)node);
  round_oo_setdescendantdestoroyfunc(node, round_local_node_destory);

  return node;
}

/****************************************
 * round_local_node_destory
 ****************************************/

bool round_local_node_destory(RoundLocalNode *node)
{
  if (!node)
    return false;
  
  return true;
}

/****************************************
* round_local_node_delete
****************************************/

bool round_local_node_delete(RoundLocalNode *node)
{
  if (!node)
    return false;
  
  round_local_node_destory(node);
  round_node_destroy((RoundNode *)node);

  free(node);
  
  return true;
}
