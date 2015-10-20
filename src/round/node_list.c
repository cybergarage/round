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
* round_nodelist_new
****************************************/

RoundNodeList *round_nodelist_new(void)
{
  RoundNodeList *nodes;

  nodes = (RoundNodeList *)malloc(sizeof(RoundNodeList));
  if (!nodes)
    return NULL;

  round_list_header_init((RoundList *)nodes);

  return nodes;
}

/****************************************
* round_nodelist_delete
****************************************/

bool round_nodelist_delete(RoundNodeList *list)
{
  if (!list)
    return false;
  
  round_nodelist_clear(list);

  free(list);
  
  return true;
}
