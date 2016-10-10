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

RoundCluster* round_cluster_new(void)
{
  RoundCluster* cluster;

  cluster = (RoundCluster*)malloc(sizeof(RoundCluster));

  if (!cluster)
    return NULL;

  round_list_node_init((RoundList*)cluster);

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

void round_cluster_delete(RoundCluster* cluster)
{
  if (!cluster)
    return;

  round_list_remove((RoundList*)cluster);
  round_string_delete(cluster->name);
  round_node_ring_delete(cluster->nodeRing);

  free(cluster);
}

/****************************************
 * round_cluster_next
 ****************************************/

RoundCluster* round_cluster_next(RoundCluster* cluster)
{
  return (RoundCluster*)round_list_next((RoundList*)cluster);
}

/****************************************
 * round_cluster_size
 ****************************************/

size_t round_cluster_size(RoundCluster* cluster)
{
  if (!cluster)
    return 0;

  return round_node_ring_size(cluster->nodeRing);
}

/****************************************
 * round_cluster_getname
 ****************************************/

const char* round_cluster_getname(RoundCluster* cluster)
{
  if (!cluster)
    return NULL;

  return round_string_getvalue(cluster->name);
}

/****************************************
 * round_cluster_getnodes
 ****************************************/

RoundNode* round_cluster_getnodes(RoundCluster* cluster)
{
  if (!cluster)
    return NULL;

  return (RoundNode*)round_node_ring_getnodes(cluster->nodeRing);
}

/****************************************
 * round_cluster_getnode
 ****************************************/

RoundNode* round_cluster_getnode(RoundCluster* cluster, size_t idx)
{
  if (!cluster)
    return NULL;

  return (RoundNode*)round_node_ring_getnode(cluster->nodeRing, idx);
}

/****************************************
 * round_cluster_getnodebyid
 ****************************************/

RoundNode* round_cluster_getnodebyid(RoundCluster* cluster, const char* id)
{
  if (!cluster)
    return NULL;

  return (RoundNode*)round_node_ring_getnodebyid(cluster->nodeRing, id);
}

/****************************************
 * round_cluster_getnodebyrandom
 ****************************************/

RoundNode* round_cluster_getnodebyrandom(RoundCluster* cluster)
{
  if (!cluster)
    return NULL;

  size_t n = rand() % round_cluster_size(cluster);
  return round_cluster_getnode(cluster, n);
}

/****************************************
 * round_cluster_hasnode
 ****************************************/

bool round_cluster_hasnode(RoundCluster* cluster, RoundNode* node)
{
  if (!cluster)
    return false;

  return round_cluster_hasequalnode(cluster, node);
}
