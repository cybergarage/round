/******************************************************************
 *
 * Round for C
 *
 * Copyright (C) Satoshi Konno 2015
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _ROUND_CLIENT_H_
#define _ROUND_CLIENT_H_

#include <round/typedef.h>
#include <round/const.h>
#include <round/cluster.h>

#ifdef  __cplusplus
extern "C" {
#endif

/****************************************
 * Data Type
 ****************************************/
  
#if !defined(_ROUND_CLIENT_INTERNAL_H_)
typedef void RoundClient;
#endif

/****************************************
 * Function
 ****************************************/
  
RoundClient *round_client_new(void);
bool round_client_delete(RoundClient *client);
  
bool round_client_start(RoundClient *client);
bool round_client_stop(RoundClient *client);

size_t round_client_getclustersize(RoundClient *client);
RoundCluster *round_client_getclusters(RoundClient *client);
RoundCluster *round_client_getcluster(RoundClient *client, size_t n);
RoundCluster *round_client_getclusterbyname(RoundClient* client, const char *name);

/****************************************
 * Function (Finder)
 ****************************************/
  
#if defined(ROUND_ENABLE_FINDER)
bool round_client_search(RoundClient *client);
#endif

#ifdef  __cplusplus
} /* extern C */
#endif

#endif /* _ROUND_CLIENT_H_ */
