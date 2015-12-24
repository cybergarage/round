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
 * round_route_object_init
 ****************************************/

bool round_route_object_init(RoundRouteObject* reg)
{
  reg->key = round_string_new();
  reg->value = round_string_new();

  if (!reg->key || !reg->value)
    return false;

  round_route_object_setts(reg, 0);
  round_route_object_setlts(reg, 0);

  return true;
}

/****************************************
 * round_route_object_new
 ****************************************/

RoundRouteObject* round_route_object_new()
{
  RoundRouteObject* reg;

  reg = (RoundRouteObject*)malloc(sizeof(RoundRouteObject));
  if (!reg)
    return NULL;

  if (!round_route_object_init(reg)) {
    round_route_object_delete(reg);
    return NULL;
  }

  return reg;
}

/****************************************
 * round_route_object_delete
 ****************************************/

bool round_route_object_delete(RoundRouteObject* reg)
{
  if (!reg)
    return false;

  round_string_delete(reg->key);
  round_string_delete(reg->value);

  free(reg);

  return true;
}
