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

  round_finder_setuserdata(client->finder, client);
  round_finder_setnodeaddedlistener(client->finder, round_client_nodeaddedlistener);
  round_finder_setnoderemovedlistener(client->finder, round_client_noderemovedlistener);
  
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

/****************************************
 * round_client_clear
 ****************************************/

bool round_client_clear(RoundClient *client)
{
  if (!client)
    return false;
  
  bool isSuccess = true;
  
  isSuccess &= round_cluster_manager_clear(client->clusterMgr);
  
  return true;
}

/****************************************
 * round_client_start
 ****************************************/

bool round_client_start(RoundClient *client)
{
  if (!client)
    return false;
  
  if (!round_client_stop(client))
    return false;
  
  bool isSuccess = true;
  
  isSuccess &= round_client_clear(client);
  isSuccess &= round_finder_start(client->finder);
  isSuccess &= round_client_search(client);
  
  if (!isSuccess) {
    round_client_stop(client);
    return false;
  }
  
  return true;
}

/****************************************
 * round_client_stop
 ****************************************/

bool round_client_stop(RoundClient *client)
{
  if (!client)
    return false;
  
  bool isSuccess = round_finder_stop(client->finder);
  
  return isSuccess;
}

/****************************************
 * round_client_search
 ****************************************/

bool round_client_search(RoundClient *client)
{
  if (!client)
    return false;
  
  return round_finder_search(client->finder);
}

/****************************************
 * round_client_getclustersize
 ****************************************/

size_t round_client_getclustersize(RoundClient *client)
{
  return round_cluster_manager_size(client->clusterMgr);
}

/****************************************
 * round_client_nodeaddedlistener
 ****************************************/

RoundCluster *round_client_getclusters(RoundClient *client)
{
  return round_cluster_manager_getclusters(client->clusterMgr);
}

/****************************************
 * round_client_nodeaddedlistener
 ****************************************/

RoundCluster *round_client_getcluster(RoundClient *client, size_t n)
{
  return round_cluster_manager_getcluster(client->clusterMgr, n);
}


/****************************************
 * round_client_nodeaddedlistener
 ****************************************/

void round_client_nodeaddedlistener(RoundFinder *finder, RoundNode *node)
{
  if (!finder || !node)
    return;
  
  RoundClient *client = round_finder_getuserdata(finder);
  if (!client)
    return;
  
  round_cluster_manager_addnode(client->clusterMgr, node);
}

/****************************************
 * round_client_noderemovedlistener
 ****************************************/

void round_client_noderemovedlistener(RoundFinder *finder, RoundNode *node)
{
  if (!finder || !node)
    return;
  
  RoundClient *client = round_finder_getuserdata(finder);
  if (!client)
    return;
  
  round_cluster_manager_removenode(client->clusterMgr, node);
}
