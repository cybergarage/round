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

  round_node_setpostmessagefunc(node, round_remote_node_postmessage);
  
  return node;
}

/****************************************
 * round_remote_node_copy
 ****************************************/

RoundRemoteNode *round_remote_node_copy(RoundNode *node)
{
  if (!node)
    return NULL;

  RoundRemoteNode *newNode = round_remote_node_new();
  if (!newNode)
    return NULL;

  const char *addr;
  if (round_node_getaddress(node, &addr)) {
    round_remote_node_setaddress(newNode, addr);
  }

  int port;
  if (round_node_getport(node, &port)) {
    round_remote_node_setport(newNode, port);
  }

  const char *clusterName;
  if (round_node_getclustername(node, &clusterName)) {
    round_remote_node_setclustername(newNode, clusterName);
  }
  
  return newNode;
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

/****************************************
 * round_remote_node_postmessage
 ****************************************/

bool round_remote_node_postmessage(RoundLocalNode *node, RoundJSONObject *reqMap, RoundJSONObject *resMap, RoundError *err)
{
  return false;
}
