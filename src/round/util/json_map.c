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
 * round_json_map_getstring
 ****************************************/

#if defined(ROUND_USE_JSON_PARSER_JANSSON)

json_t* round_json_map_getobject(RoundJSONObject* obj, const char* key)
{
  if (!obj || !key)
    return NULL;

  if (!obj->jsonObj || !json_is_object(obj->jsonObj))
    return NULL;

  return round_jansson_map_getobject(obj->jsonObj, key);
}

#endif

/****************************************
 * round_json_map_getstring
 ****************************************/

bool round_json_map_getstring(RoundJSONObject* obj, const char* key, const char** str)
{
  char buf[32];
  
  round_json_object_clearcaches(obj);
  
#if defined(ROUND_USE_JSON_PARSER_JANSSON)
  json_t* keyJson;

  keyJson = round_json_map_getobject(obj, key);
  if (!keyJson)
    return false;

  switch (json_typeof(keyJson)) {
    case JSON_NULL:
      *str = NULL;
      break;
    case JSON_STRING:
      *str = json_string_value(keyJson);
      break;
    case JSON_INTEGER:
      snprintf(buf, sizeof(buf), "%lld", json_integer_value(keyJson));
      obj->dumpedStr = round_strdup(buf);
      *str = obj->dumpedStr;
      break;
    case JSON_REAL:
      snprintf(buf, sizeof(buf), "%f", json_real_value(keyJson));
      obj->dumpedStr = round_strdup(buf);
      *str = obj->dumpedStr;
      break;
    default:
      obj->dumpedStr = json_dumps(keyJson, 0);
      *str = obj->dumpedStr;
      break;
  }
  
  return true;
#else
  return false;
#endif
}

/****************************************
 * round_json_map_getinteger
 ****************************************/

bool round_json_map_getinteger(RoundJSONObject* obj, const char* key, long* value)
{
#if defined(ROUND_USE_JSON_PARSER_JANSSON)
  json_t* keyJson;

  keyJson = round_json_map_getobject(obj, key);
  if (!keyJson || (json_typeof(keyJson) != JSON_INTEGER))
    return false;

  *value = json_integer_value(keyJson);
  return true;
#else
  return false;
#endif
}

/****************************************
 * round_json_getreal
 ****************************************/

bool round_json_map_getreal(RoundJSONObject* obj, const char* key, double* value)
{
#if defined(ROUND_USE_JSON_PARSER_JANSSON)
  json_t* keyJson;

  keyJson = round_json_map_getobject(obj, key);
  if (!keyJson || (json_typeof(keyJson) != JSON_REAL))
    return false;

  *value = json_real_value(keyJson);
  return true;
#else
  return false;
#endif
}



/****************************************
 * round_json_getbool
 ****************************************/

bool round_json_map_getbool(RoundJSONObject* obj, const char* key, bool* value)
{
#if defined(ROUND_USE_JSON_PARSER_JANSSON)
  json_t* keyJson;

  keyJson = round_json_map_getobject(obj, key);
  if (!keyJson || ((json_typeof(keyJson) != JSON_TRUE) && (json_typeof(keyJson) != JSON_FALSE)))
    return false;

  *value = json_boolean_value(keyJson) ? true : false;
  return true;
#else
  return false;
#endif
}

/****************************************
 * round_json_map_setstring
 ****************************************/

bool round_json_map_setstring(RoundJSONObject* obj, const char* key, const char* value)
{
  RoundJSONObject* valObj;

  valObj = round_json_string_new(value);
  if (round_json_map_setobject(obj, key, valObj)) {
    valObj->jsonObj = NULL;
  }
  round_json_object_delete(valObj);

  return true;
}

/****************************************
 * round_json_map_setinteger
 ****************************************/

bool round_json_map_setinteger(RoundJSONObject* obj, const char* key, long value)
{
  RoundJSONObject* valObj;

  valObj = round_json_integer_new(value);
  if (round_json_map_setobject(obj, key, valObj)) {
    valObj->jsonObj = NULL;
  }
  round_json_object_delete(valObj);

  return true;
}

/****************************************
 * round_json_map_setreal
 ****************************************/

bool round_json_map_setreal(RoundJSONObject* obj, const char* key, double value)
{
  RoundJSONObject* valObj;

  valObj = round_json_real_new(value);
  if (round_json_map_setobject(obj, key, valObj)) {
    valObj->jsonObj = NULL;
  }
  round_json_object_delete(valObj);

  return true;
}

/****************************************
 * round_json_map_setbool
 ****************************************/

bool round_json_map_setbool(RoundJSONObject* obj, const char* key, bool value)
{
  RoundJSONObject* valObj;

  valObj = round_json_bool_new(value);
  if (round_json_map_setobject(obj, key, valObj)) {
    valObj->jsonObj = NULL;
  }
  round_json_object_delete(valObj);

  return true;
}

/****************************************
 * round_json_map_setobject
 ****************************************/

bool round_json_map_setobject(RoundJSONObject* obj, const char* key, RoundJSONObject* valObj)
{
  if (!round_json_object_ismap(obj))
    return false;

#if defined(ROUND_USE_JSON_PARSER_JANSSON)
  if (!valObj->jsonObj)
    return false;

  return (json_object_set(obj->jsonObj, key, valObj->jsonObj) == 0) ? true : false;
#else
  return false;
#endif
}

/****************************************
 * round_json_map_setreplicaobject
 ****************************************/

bool round_json_map_setreplicaobject(RoundJSONObject* obj, const char* key, RoundJSONObject* valObj)
{
  bool isAdded = false;
#if defined(ROUND_USE_JSON_PARSER_JANSSON)
  json_t* copyJsonObj;
#endif

  if (!round_json_object_ismap(obj))
    return false;

#if defined(ROUND_USE_JSON_PARSER_JANSSON)
  if (!valObj->jsonObj)
    return false;

  copyJsonObj = json_copy(valObj->jsonObj);
  if (!copyJsonObj)
    return false;

  isAdded = (json_object_set(obj->jsonObj, key, valObj->jsonObj) == 0) ? true : false;

  json_decref(copyJsonObj);
#endif

  return isAdded;
}
