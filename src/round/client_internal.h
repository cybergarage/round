/******************************************************************
 *
 * Round for C
 *
 * Copyright (C) Satoshi Konno 2015
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _ROUND_CLIENT_INTERNAL_H_
#define _ROUND_CLIENT_INTERNAL_H_

#include <round/finder_internal.h>
#include <round/cluster_internal.h>

#ifdef  __cplusplus
extern "C" {
#endif

/****************************************
 * Data Type
 ****************************************/
  
typedef struct {
  RoundFinder *finder;
  RoundClusterManager *clusterMgr;
} RoundClient;
  
#ifdef  __cplusplus
} /* extern C */
#endif

bool round_client_clear(RoundClient *client);

void round_client_nodeaddedlistener(RoundFinder *finder, RoundNode *node);
void round_client_noderemovedlistener(RoundFinder *finder, RoundNode *node);

#endif /* _ROUND_CLIENT_INTERNAL_H_ */

#include <round/client.h>
