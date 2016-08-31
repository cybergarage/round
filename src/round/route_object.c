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
  if (!obj)
    return false;
  
  obj->name = round_string_new();
  
  if (!obj->name)
    return false;
  
  round_route_object_settype(obj, RoundRouteObjectNone);
  round_route_object_settarget(obj, NULL);
  
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
 * round_route_object_clear
 ****************************************/

bool round_route_object_clear(RoundRouteObject* obj)
{
  if (!obj)
    return false;

  round_string_delete(obj->name);

  return true;
}

/****************************************
 * round_route_object_delete
 ****************************************/

bool round_route_object_delete(RoundRouteObject* obj)
{
  if (!obj)
    return false;

  bool isSuccess = round_route_object_clear(obj);

  free(obj);

  return isSuccess;
}
