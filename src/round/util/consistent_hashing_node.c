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
#include <round/util/strings.h>

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
 * round_consistenthashing_node_destroy
 ****************************************/

bool round_consistenthashing_node_destroy(RoundConsistentHashingNode *node)
{
  if (!node)
    return false;

  round_list_remove((RoundList *)node);
  
  return true;
}

/****************************************
 * round_consistenthashing_node_gethash
 ****************************************/

const char *round_consistenthashing_node_gethash(void *node)
{
  ROUND_CONSISTENTHASH_NODE_HASHFUNC hashFunc;
  
  if (!node)
    return NULL;
  
  hashFunc = ((RoundConsistentHashingNode *)node)->hashFunc;
  if (!hashFunc)
    return NULL;
  
  return hashFunc(node);
}

/****************************************
 * round_consistenthashing_node_compfunc
 ****************************************/

int round_consistenthashing_node_compfunc(RoundConsistentHashingNode *thisNode, RoundConsistentHashingNode *otherNode)
{
  const char *thisHash, *otherHash;
  int strCmp;
  
  if (!thisNode || !otherNode)
    return 0;
  
  thisHash =round_consistenthashing_node_gethash(thisNode);
  otherHash =round_consistenthashing_node_gethash(otherNode);
  
  if (!thisHash || !otherHash)
    return 0;
  
  strCmp = round_strcmp(thisHash, otherHash);
  
  if (strCmp == 0)
    return RoundListNodeCompareSame;
  
  return (0 < strCmp) ? RoundListNodeCompareLess : RoundListNodeCompareGreater;
}

/****************************************
 * round_consistenthashing_node_equals
 ****************************************/

bool round_consistenthashing_node_equals(void *thisNode, void *otherNode)
{
  return (round_consistenthashing_node_comp(thisNode, otherNode) == RoundListNodeCompareSame) ? true : false;
}
