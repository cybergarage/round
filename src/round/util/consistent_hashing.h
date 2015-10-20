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

bool round_consistenthashing_ring_addnode(RoundConsistentHashingRing *ring, void *node);
bool round_consistenthashing_ring_hasnode(RoundConsistentHashingRing *ring, void *node);
ssize_t round_consistenthashing_ring_getnodeindex(RoundConsistentHashingRing *ring, void *node);

bool round_consistenthashing_ring_islastnode(RoundConsistentHashingRing *ring, void *node);
RoundConsistentHashingNode *round_consistenthashing_ring_getlastnode(RoundConsistentHashingRing *ring);

bool round_consistenthashing_ring_clear(RoundConsistentHashingRing *ring);
  
int round_consistenthashing_ring_comp(RoundConsistentHashingNode *thisNode, RoundConsistentHashingNode *otherNode);
  
/****************************************
 * Functions (Node)
 ****************************************/
  
bool round_consistenthashing_node_init(RoundConsistentHashingNode *node);

#define round_consistenthashing_node_prev_circular(node) ((RoundConsistentHashingNode *)round_list_prev_circular((RoundListNode *)node))
#define round_consistenthashing_node_prev(node) ((RoundConsistentHashingNode *)round_list_prev((RoundListNode *)node))
#define round_consistenthashing_node_next_circular(node) ((RoundConsistentHashingNode *)round_list_next_circular((RoundListNode *)node))
#define round_consistenthashing_node_next(node) ((RoundConsistentHashingNode *)round_list_next((RoundListNode *)node))
  
#define round_consistenthashing_node_sethashfunc(node,func) (node->hashFunc = (ROUND_CONSISTENTHASH_NODE_HASHFUNC)func)
const char *round_consistenthashing_node_gethash(RoundConsistentHashingNode *node);
  
#ifdef  __cplusplus
} /* extern "C" */
#endif

#endif
