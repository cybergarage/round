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

bool round_route_init(RoundRoute* route)
{
  route->name = round_string_new();
  route->srcObj = round_route_object_new();
  route->destObj = round_route_object_new();

  if (!route->name || !route->srcObj || !route->destObj)
    return false;

  return true;
}

/****************************************
 * round_route_new
 ****************************************/

RoundRoute* round_route_new()
{
  RoundRoute* route;

  route = (RoundRoute*)malloc(sizeof(RoundRoute));
  if (!route)
    return NULL;

  if (!round_route_init(route)) {
    round_route_delete(route);
    return NULL;
  }

  return route;
}

/****************************************
 * round_route_delete
 ****************************************/

bool round_route_delete(RoundRoute* route)
{
  if (!route)
    return false;

  bool isSuccess = true;
  
  isSuccess &= round_string_delete(route->name);
  isSuccess &= round_route_object_delete(route->srcObj);
  isSuccess &= round_route_object_delete(route->destObj);

  free(route);

  return true;
}
