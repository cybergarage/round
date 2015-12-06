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
 * round_json_array_size
 ****************************************/

size_t round_json_array_size(RoundJSONObject* obj)
{
  if (!round_json_object_isarray(obj))
    return 0;

#if defined(ROUND_USE_JSON_PARSER_JANSSON)
  return json_array_size(obj->jsonObj);
#else
  return 0;
#endif
}

/****************************************
 * round_json_array_get
 ****************************************/

RoundJSONObject* round_json_array_get(RoundJSONObject* obj, size_t idx)
{
  if (!round_json_object_isarray(obj))
    return NULL;

#if defined(ROUND_USE_JSON_PARSER_JANSSON)
  obj->childObj->jsonObj = json_array_get(obj->jsonObj, idx);
  if (!obj->childObj->jsonObj)
    return NULL;
  return obj->childObj;
#else
  return NULL;
#endif
}

/****************************************
 * round_json_array_append
 ****************************************/

bool round_json_array_append(RoundJSONObject* obj, RoundJSONObject* valObj)
{
  if (!round_json_object_isarray(obj))
    return false;
  
  bool isAdded = false;
  
#if defined(ROUND_USE_JSON_PARSER_JANSSON)
  if (!valObj->jsonObj)
    return false;
  
  isAdded = (json_array_append(obj->jsonObj, valObj->jsonObj) == 0) ? true : false;
#endif
  
  return isAdded;
}

/****************************************
 * round_json_array_append
 ****************************************/

bool round_json_array_appendreplica(RoundJSONObject* obj, RoundJSONObject* valObj)
{
  if (!round_json_object_isarray(obj))
    return false;

  bool isAdded = false;
  
#if defined(ROUND_USE_JSON_PARSER_JANSSON)
  if (!valObj->jsonObj)
    return false;

  json_t* copyJsonObj = json_copy(valObj->jsonObj);
  if (!copyJsonObj)
    return false;

  isAdded = (json_array_append(obj->jsonObj, copyJsonObj) == 0) ? true : false;
  json_decref(copyJsonObj);
#endif

  return isAdded;
}
