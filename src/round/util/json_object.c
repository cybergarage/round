/******************************************************************
 *
 * Round for C
 *
 * Copyright (C) Satoshi Konno 2015
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <round/util/json.h>

/****************************************
 * round_json_object_new
 ****************************************/

RoundJSONObject *round_json_object_new(void)
{
  RoundJSONObject *obj;
  
  obj = (RoundJSONObject *)malloc(sizeof(RoundJSONObject));
  
  if (!obj)
    return NULL;
  
  return obj;
}

/****************************************
 * round_json_object_delete
 ****************************************/

bool round_json_object_delete(RoundJSONObject *obj)
{
  if (!obj)
    return false;
  
  free(obj);
  
  return true;
}
