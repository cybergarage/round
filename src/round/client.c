/******************************************************************
 *
 * Round for C
 *
 * Copyright (C) Satoshi Konno 2015
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <round/client_internal.h>

/****************************************
 * round_client_new
 ****************************************/

RoundClient* round_client_new(void)
{
  RoundClient* c;

  c = (RoundClient*)malloc(sizeof(RoundClient));

  if (!c)
    return NULL;

  c->finder = round_finder_new();

  return c;
}

/****************************************
 * round_client_delete
 ****************************************/

bool round_client_delete(RoundClient* c)
{
  if (!c)
    return false;

  round_finder_delete(c->finder);

  free(c);

  return true;
}
