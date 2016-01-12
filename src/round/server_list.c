/******************************************************************
 *
 * Round for C
 *
 * Copyright (C) Satoshi Konno 2015
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <round/server_internal.h>

/****************************************
* round_server_list_new
****************************************/

RoundServerList* round_server_list_new(void)
{
  RoundServerList* servers;

  servers = (RoundServerList*)malloc(sizeof(RoundServerList));

  if (!servers)
    return NULL;

  round_list_header_init((RoundList*)servers);

  return servers;
}

/****************************************
* round_server_list_delete
****************************************/

void round_server_list_delete(RoundServerList* servers)
{
  if (!servers)
    return;

  round_server_list_clear(servers);

  free(servers);
}

/****************************************
* round_server_list_start
****************************************/

bool round_server_list_start(RoundServerList* servers)
{
  RoundServer* server;

  if (!servers)
    return false;

  for (server = round_server_list_gets(servers); server != NULL; server = round_server_next(server)) {
    round_server_start(server);
  }

  return true;
}

/****************************************
* round_server_list_stop
****************************************/

bool round_server_list_stop(RoundServerList* servers)
{
  RoundServerList* server;

  if (!servers)
    return false;

  for (server = round_server_list_gets(servers); server != NULL; server = round_server_next(server)) {
    round_server_stop(server);
  }

  return true;
}
