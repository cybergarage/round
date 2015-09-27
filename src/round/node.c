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
 * round_node_init
 ****************************************/

bool round_node_init(RoundNode *node)
{
  if (!node)
    return false;
  
  round_list_node_init((RoundList *)node);

  round_oo_setdescendantdestoroyfunc(node, NULL);
 
  node->addr = round_string_new();
  node->port = 0;
  node->cluster = round_string_new();

  node->clock = round_clock_new();
  
  if (!node->addr || !node->cluster || !node->clock)
    return false;
  
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
  
  round_list_remove((RoundList *)node);
  
  round_string_delete(node->addr);
  round_string_delete(node->cluster);
  round_clock_delete(node->clock);
  
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
  
  return round_string_setvalue(node->addr, addr);
}

/****************************************
 * round_node_getaddress
 ****************************************/

bool round_node_getaddress(RoundNode *node, const char **addr, RoundError *err)
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
  
  return true;
}

/****************************************
 * round_node_getport
 ****************************************/

bool round_node_getport(RoundNode *node, int *port, RoundError *err)
{
  if (!node)
    return false;
  
  if (node->port <= 0)
    return false;

  *port = node->port;
  
  return true;
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

bool round_node_getcluster(RoundNode *node, const char **cluster, RoundError *err)
{
  if (!node)
    return false;
  
  if (round_string_length(node->cluster) <= 0)
    return false;
  
  *cluster = round_string_getvalue(node->cluster);
  
  return true;
}

/****************************************
 * round_node_postmessage
 ****************************************/

bool round_node_postmessage(RoundNode *node, RoundJSONObject *reqObj, RoundJSONObject *resObj, RoundError *err)
{
  return false;
}
