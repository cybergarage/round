/******************************************************************
 *
 * Round for C
 *
 * Copyright (C) Satoshi Konno 2015
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _ROUND_SERVER_H_
#define _ROUND_SERVER_H_

#include <round/typedef.h>
#include <round/node.h>
#include <round/cluster.h>
#include <round/finder.h>

#ifdef  __cplusplus
extern "C" {
#endif

/****************************************
 * Data Type
 ****************************************/

#if !defined(_ROUND_SERVER_INTERNAL_H_)
typedef void RoundServer;
#endif

/****************************************
 * Function
 ****************************************/
  
RoundServer *round_server_new(void);
bool round_server_delete(RoundServer *server);
bool round_server_clear(RoundServer *server);

bool round_server_start(RoundServer *server);
bool round_server_stop(RoundServer *server);
bool round_server_isrunning(RoundServer *server);

RoundNode *round_server_getnode(RoundServer *server);

#ifdef  __cplusplus
} /* extern C */
#endif

#endif
