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

bool round_route_object_init(RoundRouteObject* obj)
{
  obj->key = round_string_new();
  obj->value = round_string_new();

  if (!obj->key || !obj->value)
    return false;

  return true;
}

/****************************************
 * round_route_object_new
 ****************************************/

RoundRouteObject* round_route_object_new()
{
  RoundRouteObject* obj;

  obj = (RoundRouteObject*)malloc(sizeof(RoundRouteObject));
  if (!obj)
    return NULL;

  if (!round_route_object_init(obj)) {
    round_route_object_delete(obj);
    return NULL;
  }

  return obj;
}

/****************************************
 * round_route_object_delete
 ****************************************/

bool round_route_object_delete(RoundRouteObject* obj)
{
  if (!obj)
    return false;

  round_string_delete(obj->key);
  round_string_delete(obj->value);

  free(obj);

  return true;
}
