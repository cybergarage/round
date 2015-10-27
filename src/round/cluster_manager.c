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
 * round_cluster_manager_addnode
 ****************************************/

bool round_cluster_manager_addnode(RoundClusterManager *mgr, RoundNode *node)
{
  return false;
}
