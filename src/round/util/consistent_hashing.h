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
  
typedef const char *(*ROUND_CONSISTENTHASH_HASHFUNC)(const void *);

/****************************************
 * Data Type
 ****************************************/

typedef struct {
  RoundOrderedList *orderedList;
  ROUND_CONSISTENTHASH_HASHFUNC nodeHashFunc;
} RoundConsistentHashingRing;

/****************************************
 * Functions
 ****************************************/

RoundConsistentHashingRing *round_consistenthashing_ring_new();
bool round_consistenthashing_ring_delete(RoundConsistentHashingRing *ring);

#define round_consistenthashing_ring_size(ring) round_ordered_list_size(ring->orderedList)
#define round_consistenthashing_ring_setnodehashfunc(ring,func) (ring->nodeHashFunc = func)

int *round_consistenthashing_ring_comp(const void *, const void *);
  
#ifdef  __cplusplus
} /* extern "C" */
#endif

#endif
