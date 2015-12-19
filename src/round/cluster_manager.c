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
* round_cluster_manager_new
****************************************/

RoundClusterManager* round_cluster_manager_new(void)
{
  RoundClusterManager* mgr;

  mgr = (RoundClusterManager*)malloc(sizeof(RoundClusterManager));
  if (!mgr)
    return NULL;

  round_list_header_init((RoundList*)mgr);

  return mgr;
}

/****************************************
* round_cluster_manager_delete
****************************************/

bool round_cluster_manager_delete(RoundClusterManager* mgr)
{
  if (!mgr)
    return false;

  round_cluster_manager_clear(mgr);

  free(mgr);

  return true;
}

/****************************************
 * round_cluster_manager_clear
 ****************************************/

bool round_cluster_manager_clear(RoundClusterManager* mgr)
{
  if (!mgr)
    return false;

  round_list_clear((RoundList*)mgr, (ROUND_LIST_DESTRUCTORFUNC)round_cluster_delete);

  return true;
}

/****************************************
 * round_cluster_manager_getclusterbyname
 ****************************************/

RoundCluster* round_cluster_manager_getclusterbyname(RoundClusterManager* mgr, const char* name)
{
  if (!mgr)
    return NULL;

  RoundCluster* cluster;
  for (cluster = round_cluster_manager_getclusters(mgr); cluster;
       cluster = round_cluster_next(cluster)) {
    if (round_streq(name, round_cluster_getname(cluster)))
      return cluster;
  }

  return NULL;
}

/****************************************
 * round_cluster_manager_getclusterbyname
 ****************************************/

RoundCluster* round_cluster_manager_getclusterbynode(RoundClusterManager* mgr, RoundNode* node)
{
  const char* clusterName;
  if (!round_node_getclustername(node, &clusterName))
    return NULL;

  return round_cluster_manager_getclusterbyname(mgr, clusterName);
}

/****************************************
 * round_cluster_manager_addnode
 ****************************************/

bool round_cluster_manager_addnode(RoundClusterManager* mgr, RoundNode* node)
{
  if (!mgr || !node)
    return false;

  const char* clusterName;
  if (!round_node_getclustername(node, &clusterName))
    return false;

  RoundCluster* cluster = round_cluster_manager_getclusterbyname(mgr, clusterName);
  if (!cluster) {
    cluster = round_cluster_new();
    if (!cluster)
      return false;

    round_cluster_setname(cluster, clusterName);
    if (!round_cluster_manager_addcluster(mgr, cluster)) {
      round_cluster_delete(cluster);
      return false;
    }
  }

  if (!cluster)
    return false;

  // Add as a remote node

  RoundRemoteNode* newNode = round_remote_node_copy(node);
  if (!newNode)
    return false;

  return round_cluster_addnode(cluster, newNode);
}

/****************************************
 * round_cluster_manager_removenode
 ****************************************/

bool round_cluster_manager_removenode(RoundClusterManager* mgr, RoundNode* node)
{
  if (!mgr || !node)
    return false;

  RoundCluster* cluster = round_cluster_manager_getclusterbynode(mgr, node);
  if (!cluster)
    return false;

  return round_cluster_removenode(cluster, node);
}

/****************************************
 * round_cluster_manager_getnode
 ****************************************/

RoundNode* round_cluster_manager_getnode(RoundClusterManager* mgr, RoundNode* node)
{
  RoundCluster* cluster = round_cluster_manager_getclusterbynode(mgr, node);
  if (!cluster)
    return false;

  return (RoundNode*)round_cluster_getequalnode(cluster, node);
}

/****************************************
 * round_cluster_manager_hasnode
 ****************************************/

bool round_cluster_manager_hasnode(RoundClusterManager* mgr, RoundNode* node)
{
  RoundCluster* cluster = round_cluster_manager_getclusterbynode(mgr, node);
  if (!cluster)
    return false;

  return round_cluster_hasequalnode(cluster, node);
}
