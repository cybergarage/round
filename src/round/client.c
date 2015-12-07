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

/****************************************
 * round_client_new
 ****************************************/

RoundClient* round_client_new(void)
{
  RoundClient* client;

  client = (RoundClient*)malloc(sizeof(RoundClient));

  if (!client)
    return NULL;

  client->finder = round_finder_new();
  client->clusterMgr = round_cluster_manager_new();

  if (!client->finder || !client->clusterMgr)
    return NULL;

  return client;
}

/****************************************
 * round_client_delete
 ****************************************/

bool round_client_delete(RoundClient* client)
{
  if (!client)
    return false;

  if (client->finder) {
    round_finder_delete(client->finder);
    client->finder = NULL;
  }

  if (client->clusterMgr) {
    round_cluster_manager_delete(client->clusterMgr);
    client->clusterMgr = NULL;
  }

  free(client);

  return true;
}
