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
#include <round/util/strings.h>

/****************************************
* round_json_new
****************************************/

RoundJSON *round_json_new(void)
{
  RoundJSON *json;
  
  json = (RoundJSON *)malloc(sizeof(RoundJSON));
  
  if (!json)
    return NULL;
  
  json->pathObj = round_json_object_new();

  return json;
}

/****************************************
 * round_json_delete
 ****************************************/

bool round_json_delete(RoundJSON *json)
{
  if (!json)
    return false;
  
  round_json_clear(json);

  round_json_object_delete(json->pathObj);

  free(json);
  
  return true;
}

/****************************************
 * round_json_clear
 ****************************************/

bool round_json_clear(RoundJSON *json)
{
  if (!json)
    return false;
  
  if (json->rootObj) {
    round_json_object_delete(json->rootObj);
    json->rootObj = NULL;
  }

  round_json_object_setjanssonobject(json->pathObj, NULL);

  return true;
}

/****************************************
 * round_json_parse
 ****************************************/

RoundJSONObject *round_json_getrootobject(RoundJSON *json)
{
  if (!json)
    return NULL;
  
  return json->rootObj;
}

/****************************************
 * round_json_parse
 ****************************************/

bool round_json_parse(RoundJSON *json, const char *jsonStr, RoundError *err)
{
  RoundJSONObject *jsonObj;
  char errMsg[128];
#if defined(ROUND_USE_JSON_PARSER_JANSSON)
  json_error_t jsonErr;
#endif

  if (!json || !jsonStr)
    return false;
  
  if (!round_json_clear(json))
    return false;
  
#if defined(ROUND_USE_JSON_PARSER_JANSSON)
  json_t *jsonRes = json_loads(jsonStr, 0, &jsonErr);
  if (!jsonRes) {
    round_error_setcode(err, jsonErr.line);
    snprintf(errMsg, sizeof(errMsg), "Error : Line %d , Pos %d, %s", jsonErr.line, jsonErr.position, jsonErr.text);
    round_error_setmessage(err, errMsg);
    return false;
  }
  
  jsonObj = round_json_object_new();
  if (!jsonObj) {
    json_decref(jsonRes);
    return false;
  }

  round_json_setrootobject(json, jsonObj);
  round_json_object_setjanssonobject(jsonObj, jsonRes);
#endif
  
  return false;
}


/****************************************
 * round_json_getobjectforpath
 ****************************************/

#if defined(ROUND_USE_JSON_PARSER_JANSSON)

json_t *round_jansson_map_getobject(json_t *jsonMap, const char *name) {
  const char *jsonKey;
  json_t *jsonObj;

  if (!jsonMap || !name)
    return NULL;
  
#if defined(ROUND_USE_JANSSON_JSON_OBJECT_FOREACH)
  // New in version 2.3
  json_object_foreach(jsonMap, jsonKey, jsonObj) {
#else
  for (void *it = json_object_iter(jsonMap); it; it = json_object_iter_next(jsonMap, it)) {
    jsonKey = json_object_iter_key(it);
    jsonObj = json_object_iter_value(it);
#endif
    if (round_streq(jsonKey, name))
      return jsonObj;
  }

  return NULL;
}
  
json_t *round_jansson_array_getobject(json_t *jsonArray, size_t n)
{
  size_t jsonIdx;
  json_t *jsonObj;
  size_t jsonArraySize;
  
  if (!jsonArray)
    return NULL;
  
  jsonArraySize = json_array_size(jsonArray);
  if ((jsonArraySize - 1) < n)
    return NULL;

  if (n < jsonArraySize)
    return json_array_get(jsonArray, n);
  
#if defined(ROUND_USE_JANSSON_JSON_ARRAY_FOREACH)
  // New in version 2.5.
  json_array_foreach(jsonArray, jsonIdx, jsonObj) {
#else
  for (jsonIdx =0; jsonIdx < jsonArraySize; jsonIdx++) {
    jsonObj = json_array_get(jsonArray, jsonIdx);
#endif
  }

  return NULL;
}
#endif

RoundJSONObject *round_json_getobjectforpath(RoundJSON *json, const char *pathStr)
{
  char *path, *token, *ptr;
#if defined(ROUND_USE_JSON_PARSER_JANSSON)
  json_t *rootJson, *tokenJson;
#endif
  
  if (!json || !pathStr)
    return NULL;

  if (!json->rootObj)
    return NULL;
  
#if defined(ROUND_USE_JSON_PARSER_JANSSON)
  rootJson = json->rootObj->jsonObj;
  if (!rootJson)
    return NULL;
#endif

  path = round_strdup(pathStr);
  if (!path)
    return NULL;
  
  token = round_strtok(path, ROUND_JSON_PATH_DELIM, &ptr);
  
  if (!token)
    return NULL;
  
#if defined(ROUND_USE_JSON_PARSER_JANSSON)

  if (!json_is_object(rootJson))
    return NULL;
  
  tokenJson = NULL;
  
  while (token) {
    token = round_strtok(NULL, ROUND_JSON_PATH_DELIM, &ptr);
  }

  round_json_object_setjanssonobject(json->pathObj, tokenJson);
#endif

  return json->pathObj;
}
