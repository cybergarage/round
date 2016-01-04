/******************************************************************
 *
 * Round for C
 *
 * Copyright (C) Satoshi Konno 2015
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _ROUND_ROUND_CONST_H_
#define _ROUND_ROUND_CONST_H_

#include <time.h>

#include <round/typedef.h>
#include <round/util/map.h>

#include "command.h"

#ifdef  __cplusplus
extern "C" {
#endif
  
/****************************************
 * Data Type
 ****************************************/

typedef struct {
  RoundMap *cmds;
} RoundCli;

/****************************************
* Function
****************************************/

RoundCli *round_cli_new(void);
bool round_cli_delete(RoundCli *cli);

#ifdef  __cplusplus
} /* extern "C" */
#endif

#endif
