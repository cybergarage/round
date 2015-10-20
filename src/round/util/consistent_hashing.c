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
 * round_consistenthashing_ring_new
 ****************************************/

RoundConsistentHashingRing *round_consistenthashing_ring_new()
{
  RoundConsistentHashingRing *ring;
  
  ring = (RoundConsistentHashingRing *)malloc(sizeof(RoundConsistentHashingRing));
  if (!ring)
    return NULL;
  
  ring->orderedList = round_ordered_list_new();
  if (!ring->orderedList) {
    round_consistenthashing_ring_delete(ring);
    return false;
  }
  round_ordered_list_setcmpfunc(ring->orderedList, round_consistenthashing_ring_comp);
  
  return ring;
}

/****************************************
 * round_consistenthashing_ring_delete
 ****************************************/

bool round_consistenthashing_ring_delete(RoundConsistentHashingRing *ring)
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
 * round_consistenthashing_ring_comp
 ****************************************/

int *round_consistenthashing_ring_comp(const void *node1, const void *node2)
{
  return 0;
}

