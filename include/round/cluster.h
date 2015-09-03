/******************************************************************
 *
 * Round SDK for C
 *
 * Copyright (C) Satoshi Konno 2015
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _ROUNDC_CLUSTER_H_
#define _ROUNDC_CLUSTER_H_

#include <round/typedef.h>

#ifdef  __cplusplus
extern "C" {
#endif

/****************************************
 * Data Type
 ****************************************/

#if !defined(_ROUNDC_CLUSTER_INTERNAL_H_)
typedef void RoundCluster;
#endif
  
/****************************************
 * Function
 ****************************************/

RoundCluster *round_cluster_new(void);
void round_cluster_delete(RoundCluster *node);
RoundCluster *round_cluster_next(RoundCluster *node);

#ifdef  __cplusplus
} /* extern C */
#endif

#endif /* _ROUNDC_CLUSTER_H_ */
