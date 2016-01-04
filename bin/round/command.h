/******************************************************************
 *
 * Round for C
 *
 * Copyright (C) Satoshi Konno 2015
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _ROUND_ROUND_COMMAND_H_
#define _ROUND_ROUND_COMMAND_H_

#include <time.h>

#include <round/typedef.h>

#ifdef  __cplusplus
extern "C" {
#endif

/****************************************
 * Data Type
 ****************************************/

typedef struct {
  const char *name;
  const char *desc;
} RoundCommand;

/****************************************
 * Function
 ****************************************/

RoundCommand *round_command_new(void);
bool round_command_delete(RoundCommand *cmd);

#ifdef  __cplusplus
} /* extern "C" */
#endif

#endif
