/******************************************************************
 *
 * Round for C
 *
 * Copyright (C) Satoshi Konno 2015
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <round/node_internal.h>
#include <round/cluster_internal.h>

/****************************************
* round_node_new
****************************************/

RoundNode *round_node_new(void)
{
  RoundNode *node;

  node = (RoundNode *)malloc(sizeof(RoundNode));

  if (!node)
    return NULL;

  if (!round_node_init(node)) {
    round_node_delete(node);
    return NULL;
  }
  
  return node;
}

/****************************************
 * round_node_local_new
 ****************************************/

RoundNode *round_node_local_new(void)
{
  return (RoundNode *)round_local_node_new();
}

/****************************************
 * round_node_remote_new
 ****************************************/

RoundNode *round_node_remote_new(void)
{
  return (RoundNode *)round_remote_node_new();
}

/****************************************
 * round_node_init
 ****************************************/

bool round_node_init(RoundNode *node)
{
  if (!node)
    return false;
  
  round_consistenthashing_node_init((RoundConsistentHashingNode *)node);
  round_oo_setdescendantdestoroyfunc(node, NULL);
 
  node->addr = round_string_new();
  node->port = 0;
  node->digest = round_string_new();
  node->cluster = round_string_new();
  node->clock = round_clock_new();
  node->clusterMgr = round_cluster_manager_new();
  
  if (!node->addr || !node->cluster || !node->clock || !node->clusterMgr)
    return false;

  round_node_setrequesttimeout(node, ROUND_JSON_RPC_REQUEST_TIMEOUT_SEC);
  round_consistenthashing_node_sethashfunc(node, round_node_getdigest);
  
  return true;
}

/****************************************
* round_node_delete
****************************************/

bool round_node_delete(RoundNode *node)
{
  if (!node)
    return false;
  
  if (!round_oo_execdescendantdestoroy(node))
    return false;

  round_node_destroy(node);

  free(node);
  
  return true;
}

/****************************************
 * round_node_destroy
 ****************************************/

bool round_node_destroy(RoundNode *node)
{
  if (!node)
    return false;
  
  round_consistenthashing_node_destroy((RoundConsistentHashingNode *)node);

  round_string_delete(node->addr);
  round_string_delete(node->digest);
  round_string_delete(node->cluster);
  round_clock_delete(node->clock);
  round_cluster_manager_delete(node->clusterMgr);
  
  return true;
}

/****************************************
 * round_node_next
 ****************************************/

RoundNode *round_node_next(RoundNode *node)
{
  return (RoundNode *)round_list_next((RoundList *)node);
}

/****************************************
 * round_node_setaddress
 ****************************************/

bool round_node_setaddress(RoundNode *node, const char *addr)
{
  if (!node)
    return false;
  
  if (!round_string_setvalue(node->addr, addr))
    return false;
  
  return round_node_updatedigest(node);
}

/****************************************
 * round_node_getaddress
 ****************************************/

bool round_node_getaddress(RoundNode *node, const char **addr)
{
  if (!node)
    return false;
  
  if (round_string_length(node->addr) <= 0)
    return false;
  
  *addr = round_string_getvalue(node->addr);
  
  return true;
}

/****************************************
 * round_node_setport
 ****************************************/

bool round_node_setport(RoundNode *node, int port)
{
  if (!node)
    return false;
  
  node->port = port;
  
  return round_node_updatedigest(node);
}

/****************************************
 * round_node_getport
 ****************************************/

bool round_node_getport(RoundNode *node, int *port)
{
  if (!node)
    return false;
  
  if (node->port <= 0)
    return false;

  *port = node->port;
  
  return true;
}

/****************************************
 * round_node_equals
 ****************************************/

bool round_node_equals(RoundNode *node1, RoundNode *node2)
{
  if (!node1 || !node2)
    return false;
  
  if (node1->port != node2->port)
    return false;
  
  if (!round_string_equals(node1->addr, node2->addr))
    return false;
  
  if (!round_string_equals(node1->cluster, node2->cluster))
    return false;
  
  return true;
}

/****************************************
 * round_node_updatedigest
 ****************************************/

bool round_node_updatedigest(RoundNode *node)
{
  if (!node)
    return false;
  
  char seed[32];
  snprintf(seed, sizeof(seed), "%s:%d", round_string_getvalue(node->addr), node->port);
  
  char *digest;
  if (!round_node_digest(seed, &digest))
    return false;
  
  round_node_setdigest(node, digest);
  free(digest);
  
  return true;
}

/****************************************
 * round_node_getdigest
 ****************************************/

const char *round_node_getdigest(RoundNode *node)
{
  if (!node)
    return "";
  
  return round_string_getvalue(node->digest);
}

/****************************************
 * round_node_setcluster
 ****************************************/

bool round_node_setcluster(RoundNode *node, const char *cluster)
{
  if (!node)
    return false;
  
  return round_string_setvalue(node->cluster, cluster);
}

/****************************************
 * round_node_getcluster
 ****************************************/

bool round_node_getcluster(RoundNode *node, const char **cluster)
{
  if (!node)
    return false;
  
  if (round_string_length(node->cluster) <= 0)
    return false;
  
  *cluster = round_string_getvalue(node->cluster);
  
  return true;
}

/****************************************
 * round_node_setrequesttimeout
 ****************************************/

bool round_node_setrequesttimeout(RoundNode *node, time_t value)
{
  if (!node)
    return false;

  node->requestTimeout = value;
  
  return true;
}

/****************************************
 * round_node_getrequesttimeout
 ****************************************/

time_t round_node_getrequesttimeout(RoundNode *node)
{
  if (!node)
    return 0;
  
  return node->requestTimeout;
}

/****************************************
 * round_node_addclusternode
 ****************************************/

bool round_node_addclusternode(RoundNode *node, RoundNode *clusterNode)
{
  if (!node)
    return false;
  
  return round_cluster_manager_addnode(node->clusterMgr, clusterNode);
}

/****************************************
 * round_node_removeclusternode
 ****************************************/

bool round_node_removeclusternode(RoundNode *node, RoundNode *clusterNode)
{
  if (!node)
    return false;
  
  return round_cluster_manager_removenode(node->clusterMgr, clusterNode);
}

/****************************************
 * round_node_clearclusternode
 ****************************************/

bool round_node_clearclusternode(RoundNode *node, RoundNode *clusterNode)
{
  if (!node)
    return false;
  
  return round_cluster_manager_clear(node->clusterMgr);
}

/****************************************
 * round_node_haclusternode
 ****************************************/

bool round_node_haclusternode(RoundNode *node, RoundNode *clusterNode)
{
  if (!node)
    return false;
  
  return round_cluster_manager_hasnode(node->clusterMgr, clusterNode);
}

/****************************************
 * round_node_postmessage
 ****************************************/

bool round_node_postmessage(RoundNode *node, RoundJSONObject *reqObj, RoundJSONObject *resObj, RoundError *err)
{
  return false;
}
