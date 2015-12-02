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
* round_node_ring_new
****************************************/

RoundNodeRing *round_node_ring_new(void) {
  RoundNodeRing *ring;

  ring = (RoundNodeRing *)malloc(sizeof(RoundNodeRing));
  if (!ring)
    return NULL;

  ring->consHashRing = round_consistenthashing_ring_new();
  round_consistenthashing_ring_setnodedestructor(ring->consHashRing,
                                                 round_node_delete);

  return ring;
}

/****************************************
* round_node_ring_delete
****************************************/

bool round_node_ring_delete(RoundNodeRing *ring) {
  if (!ring)
    return false;

  round_consistenthashing_ring_delete(ring->consHashRing);

  free(ring);

  return true;
}
