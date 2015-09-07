/******************************************************************
 *
 * Round for C
 *
 * Copyright (C) Satoshi Konno 2015
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <round/cluster_internal.h>

/****************************************
* round_clusterlist_new
****************************************/

RoundClusterList *round_clusterlist_new(void)
{
  RoundClusterList *clusterses;

  clusterses = (RoundClusterList *)malloc(sizeof(RoundClusterList));
  if (!clusterses)
    return NULL;

  round_list_header_init((RoundList *)clusterses);

  return clusterses;
}

/****************************************
* round_clusterlist_delete
****************************************/

bool round_clusterlist_delete(RoundClusterList *clusterses)
{
  if (!clusterses)
    return false;
  
  round_clusterlist_clear(clusterses);

  free(clusterses);

  return true;
}
