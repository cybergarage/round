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

  cluster->name = round_string_new();
  cluster->nodeRing = round_node_ring_new();
  
  if (!cluster->name || !cluster->nodeRing) {
    round_cluster_delete(cluster);
    return NULL;
  }
  
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
  round_string_delete(cluster->name);
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

/****************************************
 * round_cluster_getname
 ****************************************/

const char *round_cluster_getname(RoundCluster *cluster)
{
  if (!cluster)
    return NULL;
  
  return round_string_getvalue(cluster->name);
}

/****************************************
 * round_cluster_addnode
 ****************************************/

bool round_cluster_addnode(RoundCluster *cluster, RoundNode *node)
{
  return false;
}
