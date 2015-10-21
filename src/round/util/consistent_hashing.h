/******************************************************************
 *
 * Round for C
 *
 * Copyright (C) Satoshi Konno 2015
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _ROUNDC_UTIL_CONSISTENT_HASHING_H_
#define _ROUNDC_UTIL_CONSISTENT_HASHING_H_

#include <round/typedef.h>
#include <round/util/list.h>

#ifdef  __cplusplus
extern "C" {
#endif

/****************************************
 * Define
 ****************************************/
  
typedef const char *(*ROUND_CONSISTENTHASH_NODE_HASHFUNC)(void *);

/****************************************
 * Data Type
 ****************************************/

#define ROUND_CONSISTENTHASHING_NODE_STRUCT_MEMBERS \
  ROUND_LIST_STRUCT_MEMBERS \
  ROUND_CONSISTENTHASH_NODE_HASHFUNC hashFunc;
  
typedef struct {
  RoundOrderedList *orderedList;
  ROUND_LIST_DESTRUCTORFUNC nodeDstructorFunc;
} RoundConsistentHashingRing;

typedef struct {
  ROUND_CONSISTENTHASHING_NODE_STRUCT_MEMBERS
} RoundConsistentHashingNode;

/****************************************
 * Functions (Ring)
 ****************************************/

RoundConsistentHashingRing *round_consistenthashing_ring_new();
bool round_consistenthashing_ring_delete(RoundConsistentHashingRing *ring);

#define round_consistenthashing_ring_setnodedestructor(ring, func) (ring->nodeDstructorFunc = (ROUND_LIST_DESTRUCTORFUNC)func)
#define round_consistenthashing_ring_size(ring) round_ordered_list_size(ring->orderedList)
#define round_consistenthashing_ring_getnodes(ring) ((RoundConsistentHashingNode *)round_ordered_list_gets(ring->orderedList))
#define round_consistenthashing_ring_getnode(ring,idx) ((RoundConsistentHashingNode *)round_ordered_list_get(ring->orderedList,idx))

RoundConsistentHashingNode *round_consistenthashing_ring_gethandlenode(RoundConsistentHashingRing *ring, const char *hashCode);
bool round_consistenthashing_ring_ishandlenode(RoundConsistentHashingRing *ring, void *node, const char *hashCode);

bool round_consistenthashing_ring_addnode(RoundConsistentHashingRing *ring, void *node);
bool round_consistenthashing_ring_hasnode(RoundConsistentHashingRing *ring, void *node);
ssize_t round_consistenthashing_ring_getnodeindex(RoundConsistentHashingRing *ring, void *node);

bool round_consistenthashing_ring_islastnode(RoundConsistentHashingRing *ring, void *node);
RoundConsistentHashingNode *round_consistenthashing_ring_getlastnode(RoundConsistentHashingRing *ring);

RoundConsistentHashingNode *round_consistenthashing_ring_getoffsetnode(RoundConsistentHashingRing *ring, void *node, off_t offset);
RoundConsistentHashingNode *round_consistenthashing_ring_getnextnode(RoundConsistentHashingRing *ring, void *node);
RoundConsistentHashingNode *round_consistenthashing_ring_getprevnode(RoundConsistentHashingRing *ring, void *node);

off_t round_consistenthashing_ring_getforwardnodedistance(RoundConsistentHashingRing *ring, void *firstNode, void *lastNode);
off_t round_consistenthashing_ring_getbackwardnodedistance(RoundConsistentHashingRing *ring, void *firstNode, void *lastNode);
off_t round_consistenthashing_ring_getminnodedistance(RoundConsistentHashingRing *ring, void *firstNode, void *lastNode);

bool round_consistenthashing_ring_clear(RoundConsistentHashingRing *ring);
  
/****************************************
 * Functions (Node)
 ****************************************/
  
bool round_consistenthashing_node_init(RoundConsistentHashingNode *node);
bool round_consistenthashing_node_destroy(RoundConsistentHashingNode *node);

#define round_consistenthashing_node_remove(node) round_list_remove((RoundListNode *)node)
#define round_consistenthashing_node_prevcircular(node) ((RoundConsistentHashingNode *)round_list_prev_circular((RoundListNode *)node))
#define round_consistenthashing_node_prev(node) ((RoundConsistentHashingNode *)round_list_prev((RoundListNode *)node))
#define round_consistenthashing_node_nextcircular(node) ((RoundConsistentHashingNode *)round_list_next_circular((RoundListNode *)node))
#define round_consistenthashing_node_next(node) ((RoundConsistentHashingNode *)round_list_next((RoundListNode *)node))
  
#define round_consistenthashing_node_sethashfunc(node,func) (node->hashFunc = (ROUND_CONSISTENTHASH_NODE_HASHFUNC)func)
const char *round_consistenthashing_node_gethash(void *node);

int round_consistenthashing_node_compfunc(RoundConsistentHashingNode *thisNode, RoundConsistentHashingNode *otherNode);
#define round_consistenthashing_node_comp(thisNode,otherNode) round_consistenthashing_node_compfunc((RoundConsistentHashingNode *)thisNode, (RoundConsistentHashingNode *)otherNode)

bool round_consistenthashing_node_equals(void *thisNode, void *otherNode);
  
#ifdef  __cplusplus
} /* extern "C" */
#endif

#endif
