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
* round_node_new
****************************************/

RoundNode *round_node_new(void)
{
  RoundNode *node;

  node = (RoundNode *)malloc(sizeof(RoundNode));

  if (!node)
    return NULL;

  round_list_node_init((RoundList *)node);

  return node;
}

/****************************************
* round_node_delete
****************************************/

void round_node_delete(RoundNode *node)
{
  if (!node)
    return;
  
  round_list_remove((RoundList *)node);

  free(node);
}

/****************************************
 * round_node_next
 ****************************************/

RoundNode *round_node_next(RoundNode *node)
{
  return (RoundNode *)round_list_next((RoundList *)node);
}
