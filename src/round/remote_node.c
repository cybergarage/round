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
* round_remote_node_new
****************************************/

RoundRemoteNode *round_remote_node_new(void)
{
  RoundRemoteNode *node;

  node = (RoundRemoteNode *)malloc(sizeof(RoundRemoteNode));

  if (!node)
    return NULL;

  round_node_init((RoundNode *)node);
  round_oo_setdescendantdestoroyfunc(node, round_remote_node_destory);

  return node;
}

/****************************************
 * round_remote_node_destory
 ****************************************/

bool round_remote_node_destory(RoundRemoteNode *node)
{
  if (!node)
    return false;
  
  return true;
}

/****************************************
* round_remote_node_delete
****************************************/

bool round_remote_node_delete(RoundRemoteNode *node)
{
  if (!node)
    return false;
  
  round_remote_node_destory(node);
  round_node_destroy((RoundNode *)node);

  free(node);
  
  return true;
}