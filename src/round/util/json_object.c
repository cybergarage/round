/******************************************************************
 *
 * Round for C
 *
 * Copyright (C) Satoshi Konno 2015
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <round/util/json_internal.h>

/****************************************
 * round_json_object_new
 ****************************************/

RoundJSONObject *round_json_object_new(void)
{
  RoundJSONObject *obj;
  
  obj = (RoundJSONObject *)malloc(sizeof(RoundJSONObject));
  
  if (!obj)
    return NULL;

#if defined(ROUND_USE_JSON_PARSER_JANSSON)
  obj->jsonObj = NULL;
#endif
  
  return obj;
}

/****************************************
 * round_json_object_delete
 ****************************************/

bool round_json_object_delete(RoundJSONObject *obj)
{
  if (!obj)
    return false;
  
#if defined(ROUND_USE_JSON_PARSER_JANSSON)
  if (obj->jsonObj) {
    json_decref(obj->jsonObj);
    obj->jsonObj = NULL;
  }
#endif
  
  free(obj);
  
  return true;
}

/****************************************
 * round_json_object_delete
 ****************************************/

int round_json_object_gettype(RoundJSONObject *obj)
{
  if (!obj)
    return ROUND_JSON_UNKOWN;
  
  switch (json_typeof(obj->jsonObj)) {
    case JSON_OBJECT:
      return ROUND_JSON_MAP;
    case JSON_ARRAY:
      return ROUND_JSON_ARRAY;
    case JSON_NULL:
      return ROUND_JSON_NULL;
    case JSON_STRING:
      return ROUND_JSON_STRING;
    case JSON_INTEGER:
      return ROUND_JSON_INTEGER;
    case JSON_REAL:
      return ROUND_JSON_REAL;
    case JSON_TRUE:
    case JSON_FALSE:
      return ROUND_JSON_BOOL;
  }

  return ROUND_JSON_UNKOWN;
}

/****************************************
 * round_json_object_delete
 ****************************************/

bool round_json_object_istype(RoundJSONObject *obj, int type)
{
  if (!obj)
    return false;
  return (round_json_object_gettype(obj) == type) ? true : false;
}
