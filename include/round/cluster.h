/******************************************************************
 *
 * Round for C
 *
 * Copyright (C) Satoshi Konno 2015
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _ROUND_CLUSTER_H_
#define _ROUND_CLUSTER_H_

#include <round/typedef.h>
#include <round/node.h>

#ifdef  __cplusplus
extern "C" {
#endif

/****************************************
 * Data Type
 ****************************************/

#if !defined(_ROUND_CLUSTER_INTERNAL_H_)
typedef void RoundCluster;
#endif
  
/****************************************
 * Function
 ****************************************/

RoundCluster *round_cluster_new(void);
void round_cluster_delete(RoundCluster *cluster);

RoundCluster *round_cluster_next(RoundCluster *cluster);
const char *round_cluster_getname(RoundCluster *cluster);

size_t round_cluster_size(RoundCluster* cluster);
RoundNode *round_cluster_getnodes(RoundCluster* cluster);
RoundNode *round_cluster_getnode(RoundCluster *cluster, size_t idx);
RoundNode *round_cluster_getnodebyid(RoundCluster *cluster, const char *id);
RoundNode *round_cluster_getnodebyrandom(RoundCluster *cluster);
bool round_cluster_hasnode(RoundCluster* cluster, RoundNode *node);

/****************************************
 * Function (Node)
 ****************************************/

RoundCluster *round_node_getcluster(RoundNode *node);
RoundCluster *round_node_getclusterbyname(RoundNode *node, const char *name);
RoundCluster *round_node_getclusters(RoundNode *node);

/****************************************
 * Function (Local Node)
 ****************************************/

#define round_local_node_getcluster(node) round_node_getcluster((RoundNode*)node)
#define round_local_node_getclusterbyname(node, name) round_node_getclusterbyname((RoundNode*)node, name)
#define round_local_node_getclusters(node) round_node_getclusters((RoundNode*)node)

#ifdef  __cplusplus
} /* extern C */
#endif

#endif /* _ROUND_CLUSTER_H_ */
