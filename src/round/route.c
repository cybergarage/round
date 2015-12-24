/******************************************************************
 *
 * Round for C
 *
 * Copyright (C) Satoshi Konno 2015
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <round/route.h>

/****************************************
 * round_route_init
 ****************************************/

bool round_route_init(RoundRoute* reg)
{
  reg->key = round_string_new();
  reg->value = round_string_new();

  if (!reg->key || !reg->value)
    return false;

  round_route_setts(reg, 0);
  round_route_setlts(reg, 0);

  return true;
}

/****************************************
 * round_route_new
 ****************************************/

RoundRoute* round_route_new()
{
  RoundRoute* reg;

  reg = (RoundRoute*)malloc(sizeof(RoundRoute));
  if (!reg)
    return NULL;

  if (!round_route_init(reg)) {
    round_route_delete(reg);
    return NULL;
  }

  return reg;
}

/****************************************
 * round_route_delete
 ****************************************/

bool round_route_delete(RoundRoute* reg)
{
  if (!reg)
    return false;

  round_string_delete(reg->key);
  round_string_delete(reg->value);

  free(reg);

  return true;
}
