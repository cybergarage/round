/******************************************************************
 *
 * Round for C
 *
 * Copyright (C) Satoshi Konno 2015
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _ROUND_CLUSTER_INTERNAL_H_
#define _ROUND_CLUSTER_INTERNAL_H_

#include <round/typedef.h>
#include <round/util/list.h>
#include <round/node_internal.h>

#ifdef  __cplusplus
extern "C" {
#endif

/****************************************
 * Data Type
 ****************************************/

typedef struct _RoundCluster {
  ROUND_LIST_STRUCT_MEMBERS
  RoundString *name;
  RoundNodeRing *nodeRing;
} RoundCluster;

/****************************************
 * Header
 ****************************************/
  
#include <round/cluster.h>
  
/****************************************
 * Function
 ****************************************/

#define round_cluster_setname(cluster,value) round_string_setvalue(cluster->name, value)
#define round_cluster_isname(cluster,value) round_streq(round_cluster_getname(cluster), value)
#define round_cluster_remove(cluster) round_list_remove((RoundList *)cluster)
#define round_cluster_equals(cluster1, cluster2) round_string_equals(cluster1->name, cluster2->name)

#define round_cluster_addnode(cluster,node) round_node_ring_add(cluster->nodeRing,node)
#define round_cluster_removenode(cluster,node) round_node_ring_remove(cluster->nodeRing,node)
#define round_cluster_getnode(cluster,node) round_node_ring_getequalnode(cluster->nodeRing,node)
#define round_cluster_hasnode(cluster,node) round_node_ring_hasnode(cluster->nodeRing,node)

/****************************************
 * Function (Class Manager)
 ****************************************/
  
RoundClusterManager *round_cluster_manager_new(void);
bool round_cluster_manager_delete(RoundClusterManager *mgr);
bool round_cluster_manager_clear(RoundClusterManager *mgr);
  
bool round_cluster_manager_addnode(RoundClusterManager *mgr, RoundNode *node);
bool round_cluster_manager_removenode(RoundClusterManager *mgr, RoundNode *node);
RoundNode *round_cluster_manager_getnode(RoundClusterManager *mgr, RoundNode *node);
bool round_cluster_manager_hasnode(RoundClusterManager *mgr, RoundNode *node);
RoundCluster *round_cluster_manager_getclusterbynode(RoundClusterManager *mgr, RoundNode *node);
RoundCluster *round_cluster_manager_getclusterbyname(RoundClusterManager *mgr, const char *name);
  
#define round_cluster_manager_hascluster(mgr, name) (round_cluster_manager_getclusterbyname(mgr,name) ? true : false)
#define round_cluster_manager_size(mgr) round_list_size((RoundList *)mgr)
#define round_cluster_manager_getclusters(mgr) (RoundCluster *)round_list_next((RoundList *)mgr)
#define round_cluster_manager_addcluster(mgr,cluster) round_list_add((RoundList *)mgr, (RoundList *)cluster)

#ifdef  __cplusplus
} /* extern C */
#endif

#endif /* _ROUND_CLUSTER_H_ */
