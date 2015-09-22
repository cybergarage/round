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

  round_node_init(node);
  
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
 * round_node_getrequestaddress
 ****************************************/

bool round_node_getrequestaddress(RoundNode *node, const char **address, RoundError *err)
{
  return false;
}

/****************************************
 * round_node_getrequestport
 ****************************************/

bool round_node_getrequestport(RoundNode *node, int *port, RoundError *err)
{
  return false;
}

/****************************************
 * round_node_getclustername
 ****************************************/

bool round_node_getclustername(RoundNode *node, const char **address, RoundError *err)
{
  return false;
}

/****************************************
 * round_node_postmessage
 ****************************************/

bool round_node_postmessage(RoundJSONObject *reqObj, RoundJSONObject *resObj, RoundError *err)
{
  return false;
}
