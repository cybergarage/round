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

RoundClusterManager *round_cluster_manager_new(void)
{
  RoundClusterManager *mgr;

  mgr = (RoundClusterManager *)malloc(sizeof(RoundClusterManager));
  if (!mgr)
    return NULL;

  round_list_header_init((RoundList *)mgr);
  
  return mgr;
}

/****************************************
* round_cluster_manager_delete
****************************************/

bool round_cluster_manager_delete(RoundClusterManager *mgr)
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

bool round_cluster_manager_clear(RoundClusterManager *mgr)
{
  if (!mgr)
    return false;
  
  round_list_clear((RoundList *)mgr, (ROUND_LIST_DESTRUCTORFUNC)round_cluster_delete);
  
  return true;
}

/****************************************
 * round_cluster_manager_getcluster
 ****************************************/

RoundCluster *round_cluster_manager_getcluster(RoundClusterManager *mgr, const char *name)
{
  if (!mgr)
    return NULL;
  
  for (RoundCluster *cluster = round_cluster_manager_getclusters(mgr); cluster; cluster = round_cluster_next(cluster)) {
    if (round_streq(name, round_cluster_getname(cluster)))
        return cluster;
  }
  
  return NULL;
}

/****************************************
 * round_cluster_manager_addnode
 ****************************************/

bool round_cluster_manager_addnode(RoundClusterManager *mgr, RoundNode *node)
{
  if (!mgr || !node)
    return false;
  
  const char *clusterName;
  if (!round_node_getcluster(node, &clusterName))
    return false;

  RoundCluster *cluster = round_cluster_manager_getcluster(mgr, clusterName);
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

  return round_cluster_addnode(cluster, node);
}

/****************************************
 * round_cluster_manager_removenode
 ****************************************/

bool round_cluster_manager_removenode(RoundClusterManager *mgr, RoundNode *node)
{
  if (!mgr || !node)
    return false;
  
  const char *clusterName;
  if (!round_node_getcluster(node, &clusterName))
    return false;
  
  RoundCluster *cluster = round_cluster_manager_getcluster(mgr, clusterName);
  if (!cluster)
    return false;
  
  return round_cluster_removenode(cluster, node);
  
}
