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

RoundNodeRing *round_node_ring_new(void)
{
  RoundNodeRing *nodes;

  nodes = (RoundNodeRing *)malloc(sizeof(RoundNodeRing));
  if (!nodes)
    return NULL;

  round_list_header_init((RoundList *)nodes);

  return nodes;
}

/****************************************
* round_node_ring_delete
****************************************/

bool round_node_ring_delete(RoundNodeRing *list)
{
  if (!list)
    return false;
  
  round_node_ring_clear(list);

  free(list);
  
  return true;
}
