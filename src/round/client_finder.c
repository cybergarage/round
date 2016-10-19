/******************************************************************
 *
 * Round for C
 *
 * Copyright (C) Satoshi Konno 2015
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <round/client_internal.h>

#if defined(ROUND_ENABLE_FINDER)

/****************************************
 * round_client_nodeaddedlistener
 ****************************************/

void round_client_nodeaddedlistener(RoundFinder* finder, RoundNode* node)
{
  if (!finder || !node)
    return;

  RoundClient* client = round_finder_getuserdata(finder);
  if (!client)
    return;

  round_cluster_manager_addnode(client->clusterMgr, node);
}

/****************************************
 * round_client_noderemovedlistener
 ****************************************/

void round_client_noderemovedlistener(RoundFinder* finder, RoundNode* node)
{
  if (!finder || !node)
    return;

  RoundClient* client = round_finder_getuserdata(finder);
  if (!client)
    return;

  round_cluster_manager_removenode(client->clusterMgr, node);
}

#endif
