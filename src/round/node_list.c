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
  RoundNodeList *nodeses;

  nodeses = (RoundNodeList *)malloc(sizeof(RoundNodeList));
  if (!nodeses)
    return NULL;

  round_list_header_init((RoundList *)nodeses);

  return nodeses;
}

/****************************************
* round_nodelist_delete
****************************************/

void round_nodelist_delete(RoundNodeList *nodeses)
{
  if (!nodeses)
    return;
  
  round_nodelist_clear(nodeses);

  free(nodeses);
}
