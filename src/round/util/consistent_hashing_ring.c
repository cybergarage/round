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
 * round_consistenthashing_ring_new
 ****************************************/

RoundConsistentHashingRing* round_consistenthashing_ring_new()
{
  RoundConsistentHashingRing* ring;

  ring = (RoundConsistentHashingRing*)malloc(sizeof(RoundConsistentHashingRing));
  if (!ring)
    return NULL;

  ring->orderedList = round_ordered_list_new();
  if (!ring->orderedList) {
    round_consistenthashing_ring_delete(ring);
    return false;
  }

  round_ordered_list_setcmpfunc(ring->orderedList, round_consistenthashing_node_compfunc);
  round_consistenthashing_ring_setnodedestructor(ring, NULL);

  return ring;
}

/****************************************
 * round_consistenthashing_ring_delete
 ****************************************/

bool round_consistenthashing_ring_delete(RoundConsistentHashingRing* ring)
{
  if (!ring)
    return false;

  if (ring->orderedList) {
    round_ordered_list_delete(ring->orderedList);
    ring->orderedList = NULL;
  }

  free(ring);

  return true;
}

/****************************************
 * round_consistenthashing_ring_clear
 ****************************************/

bool round_consistenthashing_ring_clear(RoundConsistentHashingRing* ring)
{
  if (!ring)
    return false;

  if (ring->orderedList) {
    round_ordered_list_clear(ring->orderedList);
  }

  return true;
}

/****************************************
 * round_consistenthashing_ring_addnode
 ****************************************/

bool round_consistenthashing_ring_addnode(RoundConsistentHashingRing* ring, void* node)
{
  if (!ring || !node)
    return false;

  if (round_consistenthashing_ring_hasnode(ring, node))
    return false;

  return round_ordered_list_add(ring->orderedList, node);
}

/****************************************
 * round_consistenthashing_ring_removenode
 ****************************************/

bool round_consistenthashing_ring_removenode(RoundConsistentHashingRing* ring, void* node)
{
  if (!ring || !node)
    return false;

  RoundConsistentHashingNode* eqNode = round_consistenthashing_ring_getequalnode(ring, node);
  if (!eqNode)
    return false;

  return round_ordered_list_remove(eqNode);
}

/****************************************
 * round_consistenthashing_ring_getnodebyhashcode
 ****************************************/

RoundConsistentHashingNode* round_consistenthashing_ring_getnodebyhashcode(RoundConsistentHashingRing* ring, const char* targetNodeHash)
{
  RoundConsistentHashingNode* node;
  for (node = round_consistenthashing_ring_getnodes(ring); node;
       node = round_consistenthashing_node_next(node)) {
    const char* nodeHash = round_consistenthashing_node_gethash(node);
    if (nodeHash) {
      if (round_strcmp(targetNodeHash, nodeHash) == 0)
        return node;
    }
  }

  return NULL;
}

/****************************************
 * round_consistenthashing_ring_getequalnode
 ****************************************/

RoundConsistentHashingNode* round_consistenthashing_ring_getequalnode(RoundConsistentHashingRing* ring, void* node)
{
  const char* nodeHash = round_consistenthashing_node_gethash(node);
  if (!nodeHash)
    return NULL;

  return round_consistenthashing_ring_getnodebyhashcode(ring, nodeHash);
}

/****************************************
 * round_consistenthashing_ring_getnodeindex
 ****************************************/

ssize_t round_consistenthashing_ring_getnodeindex(RoundConsistentHashingRing* ring, void* targetNode)
{
  const char* targetNodeHash = round_consistenthashing_node_gethash(targetNode);
  if (!targetNodeHash)
    return -1;

  ssize_t nodeIdx = 0;
  RoundConsistentHashingNode* node;
  for (node = round_consistenthashing_ring_getnodes(ring); node; node = round_consistenthashing_node_next(node)) {
    const char* nodeHash = round_consistenthashing_node_gethash(node);
    if (nodeHash) {
      if (round_strcmp(targetNodeHash, nodeHash) == 0)
        return nodeIdx;
    }
    nodeIdx++;
  }

  return -1;
}

/****************************************
 * round_consistenthashing_ring_islastnode
 ****************************************/

bool round_consistenthashing_ring_islastnode(RoundConsistentHashingRing* ring, void* node)
{
  ssize_t ringSize, nodeIdx;

  ringSize = round_consistenthashing_ring_size(ring);
  if (ringSize <= 0)
    return false;

  nodeIdx = round_consistenthashing_ring_getnodeindex(ring, node);
  if (nodeIdx < 0)
    return false;

  return (nodeIdx == (ringSize - 1)) ? true : false;
}

/****************************************
 * round_consistenthashing_ring_getlastnode
 ****************************************/

RoundConsistentHashingNode* round_consistenthashing_ring_getlastnode(RoundConsistentHashingRing* ring)
{
  ssize_t ringSize;

  ringSize = round_consistenthashing_ring_size(ring);
  if (ringSize <= 0)
    return NULL;
  return round_consistenthashing_ring_getnode(ring, (ringSize - 1));
}

/****************************************
 * round_consistenthashing_ring_gethandlenode
 ****************************************/

RoundConsistentHashingNode* round_consistenthashing_ring_gethandlenode(RoundConsistentHashingRing* ring, const char* hashCode)
{
  RoundConsistentHashingNode* node, *nextNode;
  const char* nodeHashCode, *nextNodeHashCode;

  // TODO : Fix the O(n) algorithm

  for (node = round_consistenthashing_ring_getnodes(ring); node;
       node = round_consistenthashing_node_next(node)) {
    nextNode = round_consistenthashing_node_next(node);
    if (!nextNode)
      break;

    nodeHashCode = round_consistenthashing_node_gethash(node);
    if (round_strcmp(hashCode, nodeHashCode) < 0)
      continue;

    nextNodeHashCode = round_consistenthashing_node_gethash(nextNode);
    if (round_strcmp(hashCode, nextNodeHashCode) >= 0)
      continue;

    return node;
  }

  return round_consistenthashing_ring_getlastnode(ring);
}

/****************************************
 * round_consistenthashing_ring_ishandlenode
 ****************************************/

bool round_consistenthashing_ring_ishandlenode(RoundConsistentHashingRing* ring, void* node, const char* hashCode)
{
  return (node == round_consistenthashing_ring_gethandlenode(ring, hashCode)) ? true : false;
}

/****************************************
 * round_consistenthashing_ring_getoffsetnode
 ****************************************/

RoundConsistentHashingNode* round_consistenthashing_ring_getoffsetnode(RoundConsistentHashingRing* ring, void* node, off_t offset)
{
  ssize_t ringSize, nodeIndex, offsetNodeIndex;

  nodeIndex = round_consistenthashing_ring_getnodeindex(ring, node);
  if (nodeIndex < 0)
    return NULL;

  ringSize = round_consistenthashing_ring_size(ring);

  offsetNodeIndex = nodeIndex + offset;
  if (offsetNodeIndex < 0) {
    while (offsetNodeIndex < 0) {
      offsetNodeIndex += ringSize;
    }
    offsetNodeIndex = offsetNodeIndex % ringSize;
  }
  offsetNodeIndex = offsetNodeIndex % ringSize;

  return round_consistenthashing_ring_getnode(ring, offsetNodeIndex);
}

/****************************************
 * round_consistenthashing_ring_getnextnode
 ****************************************/

RoundConsistentHashingNode*
round_consistenthashing_ring_getnextnode(RoundConsistentHashingRing* ring,
                                         void* node)
{
  return round_consistenthashing_ring_getoffsetnode(ring, node, 1);
}

/****************************************
 * round_consistenthashing_ring_getprevnode
 ****************************************/

RoundConsistentHashingNode*
round_consistenthashing_ring_getprevnode(RoundConsistentHashingRing* ring,
                                         void* node)
{
  return round_consistenthashing_ring_getoffsetnode(ring, node, -1);
}

/****************************************
 * round_consistenthashing_ring_getforwardnodedistance
 ****************************************/

off_t round_consistenthashing_ring_getforwardnodedistance(
    RoundConsistentHashingRing* ring, void* firstNode, void* lastNode)
{
  size_t ringSize;
  ssize_t firstNodeIndex, lastNodeIndex;

  firstNodeIndex = round_consistenthashing_ring_getnodeindex(ring, firstNode);
  if (firstNodeIndex < 0)
    return 0;

  lastNodeIndex = round_consistenthashing_ring_getnodeindex(ring, lastNode);
  if (lastNodeIndex < 0)
    return 0;

  ringSize = round_consistenthashing_ring_size(ring);

  off_t clockwiseOffset;
  if (firstNodeIndex == lastNodeIndex) {
    clockwiseOffset = 0;
  }
  else if (firstNodeIndex <= lastNodeIndex) {
    clockwiseOffset = lastNodeIndex - firstNodeIndex;
  }
  else {
    clockwiseOffset = (lastNodeIndex + ringSize) - firstNodeIndex;
  }

  return clockwiseOffset;
}

/****************************************
 * round_consistenthashing_ring_getbackwardnodedistance
 ****************************************/

off_t round_consistenthashing_ring_getbackwardnodedistance(
    RoundConsistentHashingRing* ring, void* firstNode, void* lastNode)
{
  size_t ringSize;
  ssize_t firstNodeIndex, lastNodeIndex;

  firstNodeIndex = round_consistenthashing_ring_getnodeindex(ring, firstNode);
  if (firstNodeIndex < 0)
    return 0;

  lastNodeIndex = round_consistenthashing_ring_getnodeindex(ring, lastNode);
  if (lastNodeIndex < 0)
    return 0;

  ringSize = round_consistenthashing_ring_size(ring);

  off_t counterClockwiseOffset;
  if (firstNodeIndex == lastNodeIndex) {
    counterClockwiseOffset = 0;
  }
  else if (firstNodeIndex <= lastNodeIndex) {
    counterClockwiseOffset = lastNodeIndex - (firstNodeIndex + ringSize);
  }
  else {
    counterClockwiseOffset = lastNodeIndex - firstNodeIndex;
  }

  return counterClockwiseOffset;
}

/****************************************
 * round_consistenthashing_ring_getprevnode
 ****************************************/

#define abs_off_t(a) ((a) < 0 ? -(a) : (a))

off_t round_consistenthashing_ring_getminnodedistance(
    RoundConsistentHashingRing* ring, void* firstNode, void* lastNode)
{
  off_t clockwiseOffset, counterClockwiseOffset;

  clockwiseOffset = round_consistenthashing_ring_getforwardnodedistance(ring, firstNode, lastNode);
  counterClockwiseOffset = round_consistenthashing_ring_getbackwardnodedistance(ring, firstNode, lastNode);

  return (abs_off_t(clockwiseOffset) < abs_off_t(counterClockwiseOffset))
             ? clockwiseOffset
             : counterClockwiseOffset;
}
