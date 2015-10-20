/******************************************************************
 *
 * Round for C
 *
 * Copyright (C) Satoshi Konno 2015
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <round/util/consistent_hashing.h>

/****************************************
 * round_consistenthashing_node_init
 ****************************************/

bool round_consistenthashing_node_init(RoundConsistentHashingNode *node)
{
  if (!node)
    return false;

  round_list_node_init((RoundListNode *)node);
  round_consistenthashing_node_sethashfunc(node, NULL);
  
  return true;
}

/****************************************
 * round_consistenthashing_node_gethash
 ****************************************/

const char *round_consistenthashing_node_gethash(RoundConsistentHashingNode *node)
{
  if (!node || !node->hashFunc)
    return NULL;  
  return node->hashFunc(node);
}