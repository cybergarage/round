/******************************************************************
 *
 * Round for C
 *
 * Copyright (C) Satoshi Konno 2015
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include "command.h"

/****************************************
* round_command_new
****************************************/

RoundCommand* round_command_new(void)
{
  RoundCommand* cmd;

  cmd = (RoundCommand*)malloc(sizeof(RoundCommand));

  if (!cmd)
    return NULL;

  return cmd;
}

/****************************************
* round_command_delete
****************************************/

bool round_command_delete(RoundCommand* cmd)
{
  if (!cmd)
    return false;

  free(cmd);

  return true;
}
