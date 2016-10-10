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
typedef void RoundServerList;
#endif

/****************************************
 * Function
 ****************************************/
  
RoundServer *round_server_new(void);
bool round_server_delete(RoundServer *server);
bool round_server_clear(RoundServer *server);

bool round_server_start(RoundServer *server);
bool round_server_stop(RoundServer *server);
bool round_server_restart(RoundServer *server);
bool round_server_isrunning(RoundServer *server);

RoundLocalNode *round_server_getlocalnode(RoundServer *server);
#define round_server_getnode(server) (RoundNode *)round_server_getlocalnode(server)

bool round_server_setbindaddress(RoundServer *server, const char *addr);
const char *round_server_getbindaddress(RoundServer* server);

bool round_server_setbindport(RoundServer *server, int port);
int round_server_getbindport(RoundServer* server);

void round_server_setuserdata(RoundServer *server, void *data);
void *round_server_getuserdata(RoundServer *server);

/****************************************
 * Function (Server List)
 ****************************************/

RoundServerList *round_server_list_new();
void round_server_list_delete(RoundServerList *servers);

bool round_server_list_add(RoundServerList *servers, RoundServer *server);

bool round_server_list_start(RoundServerList *servers);
bool round_server_list_stop(RoundServerList *servers);

#ifdef  __cplusplus
} /* extern C */
#endif

#endif
