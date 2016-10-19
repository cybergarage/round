/******************************************************************
 *
 * Round for C
 *
 * Copyright (C) Satoshi Konno 2015
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <round/server_internal.h>

#if defined(ROUND_ENABLE_FINDER)

/****************************************
 * round_server_nodeaddedlistener
 ****************************************/

void round_server_nodeaddedlistener(RoundFinder* finder, RoundNode* node)
{
  if (!finder || !node)
    return;

  RoundServer* server = round_finder_getuserdata(finder);
  if (!server)
    return;

  round_local_node_addclusternode(server->node, node);
}

/****************************************
 * round_server_noderemovedlistener
 ****************************************/

void round_server_noderemovedlistener(RoundFinder* finder, RoundNode* node)
{
  if (!finder || !node)
    return;

  RoundServer* server = round_finder_getuserdata(finder);
  if (!server)
    return;

  round_local_node_removeclusternode(server->node, node);
}

#endif
