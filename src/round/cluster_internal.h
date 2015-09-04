/******************************************************************
 *
 * Round for C
 *
 * Copyright (C) Satoshi Konno 2015
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _ROUNDC_CLUSTER_INTERNAL_H_
#define _ROUNDC_CLUSTER_INTERNAL_H_

#include <round/typedef.h>
#include <round/util/list.h>

#ifdef  __cplusplus
extern "C" {
#endif

/****************************************
 * Data Type
 ****************************************/

typedef struct _RoundCluster {
  bool headFlag;
  struct _RoundCluster *prev;
  struct _RoundCluster *next;

} RoundCluster, RoundClusterList;

/****************************************
 * Header
 ****************************************/
  
#include <round/cluster.h>
  
/****************************************
 * Function
 ****************************************/

#define round_cluster_remove(cluster) round_list_remove((RoundList *)cluster)

/****************************************
 * Function (Class List)
 ****************************************/
  
RoundClusterList *round_clusterlist_new(void);
void round_clusterlist_delete(RoundClusterList *clusters);
  
#define round_clusterlist_clear(clusters) round_list_clear((RoundList *)clusters, (ROUND_LIST_DESTRUCTORFUNC)round_cluster_delete)
#define round_clusterlist_size(clusters) round_list_size((RoundList *)clusters)
#define round_clusterlist_gets(clusters) (RoundCluster *)round_list_next((RoundList *)clusters)
#define round_clusterlist_add(clusters,cluster) round_list_add((RoundList *)clusters, (RoundList *)cluster)

#ifdef  __cplusplus
} /* extern C */
#endif

#endif /* _ROUNDC_CLUSTER_H_ */
