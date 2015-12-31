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
  obj->tokenCnt = 0;
  obj->tokens = NULL;
  obj->tokenObjs = NULL;

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

  size_t n;
  for (n = 0; n < obj->tokenCnt; n++) {
    if (obj->tokens[n]) {
      free(obj->tokens[n]);
    }
    obj->tokenObjs[n] = NULL;
  }

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
