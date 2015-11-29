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

/****************************************
 * Function (Node)
 ****************************************/

RoundCluster *round_node_getcluster(RoundNode *node);
RoundCluster *round_node_getclusterbyname(RoundNode *node, const char *name);
RoundCluster *round_node_getclusters(RoundNode *node);

#ifdef  __cplusplus
} /* extern C */
#endif

#endif /* _ROUND_CLUSTER_H_ */
