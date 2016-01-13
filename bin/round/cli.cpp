/******************************************************************
 *
 * Round for C
 *
 * Copyright (C) Satoshi Konno 2015
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include "cli.h"

/****************************************
* round_cli_new
****************************************/

RoundCli* round_cli_new(void)
{
  RoundCli* cli;

  cli = (RoundCli*)malloc(sizeof(RoundCli));

  if (!cli)
    return NULL;

  cli->cmds = round_map_new();
  round_map_setmapobjectdestructor(cli->cmds, (ROUND_MAP_OBJECT_DESTRUCTOR)round_command_delete);

  return cli;
}

/****************************************
* round_cli_delete
****************************************/

bool round_cli_delete(RoundCli* cli)
{
  if (!cli)
    return false;

  round_map_delete(cli->cmds);

  free(cli);

  return true;
}
