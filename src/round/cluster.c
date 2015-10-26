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
* round_cluster_new
****************************************/

RoundCluster *round_cluster_new(void)
{
  RoundCluster *cluster;

  cluster = (RoundCluster *)malloc(sizeof(RoundCluster));

  if (!cluster)
    return NULL;

  round_list_node_init((RoundList *)cluster);

  cluster->nodeRing = round_node_ring_new();
  
  return cluster;
}

/****************************************
* round_cluster_delete
****************************************/

void round_cluster_delete(RoundCluster *cluster)
{
  if (!cluster)
    return;
  
  round_list_remove((RoundList *)cluster);
  round_node_ring_delete(cluster->nodeRing);

  free(cluster);
}

/****************************************
 * round_cluster_next
 ****************************************/

RoundCluster *round_cluster_next(RoundCluster *cluster)
{
  return (RoundCluster *)round_list_next((RoundList *)cluster);
}
