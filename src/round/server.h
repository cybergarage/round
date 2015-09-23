/******************************************************************
 *
 * Round for C
 *
 * Copyright (C) Satoshi Konno 2015
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _ROUNDC_SERVER_H_
#define _ROUNDC_SERVER_H_

#include <round/typedef.h>

#ifdef  __cplusplus
extern "C" {
#endif

/****************************************
 * Data Type
 ****************************************/

typedef struct {
  int dummy;
} RoundServer;

/****************************************
 * Function
 ****************************************/
  
RoundServer *round_server_new(void);
bool round_server_delete(RoundServer *server);

bool round_server_start(RoundServer *server);
bool round_server_stop(RoundServer *server);

#ifdef  __cplusplus
} /* extern C */
#endif

#endif
