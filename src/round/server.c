/******************************************************************
 *
 * Round for C
 *
 * Copyright (C) Satoshi Konno 2015
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <round/server.h>

/****************************************
* round_server_new
****************************************/

RoundServer *round_server_new(void)
{
  RoundServer *server;

  server = (RoundServer *)malloc(sizeof(RoundServer));

  if (!server)
    return NULL;

  return server;
}

/****************************************
* round_server_delete
****************************************/

bool round_server_delete(RoundServer *server)
{
  if (!server)
    return false;

  free(server);
  
  return true;
}

/****************************************
 * round_server_start
 ****************************************/

bool round_server_start(RoundServer *server)
{
  if (!server)
    return false;

  return true;
}

/****************************************
 * round_server_stop
 ****************************************/

bool round_server_stop(RoundServer *server)
{
  if (!server)
    return false;
  
  return true;
}
