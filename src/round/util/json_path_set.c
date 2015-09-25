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
 * round_json_setstringforpath
 ****************************************/


bool round_json_setstringforpath(RoundJSON *json, const char *path, const char *value)
{
  RoundJSONObject *obj;
  
  obj = round_json_string_new(value);
  if (round_json_map_setobjectforpath(json, path, obj)) {
    obj->jsonObj = NULL;
  }
  
  round_json_object_delete(obj);
  
  return true;
}

/****************************************
 * round_json_setintegerforpath
 ****************************************/

bool round_json_setintegerforpath(RoundJSON *json, const char *path, int value)
{
  RoundJSONObject *obj;
  
  obj = round_json_integer_new(value);
  if (round_json_map_setobjectforpath(json, path, obj)) {
    obj->jsonObj = NULL;
  }
  
  round_json_object_delete(obj);
  
  return true;
}

/****************************************
 * round_json_setrealforpath
 ****************************************/

bool round_json_setrealforpath(RoundJSON *json, const char *path, double value)
{
  RoundJSONObject *obj;

  obj = round_json_real_new(value);
  if (round_json_map_setobjectforpath(json, path, obj)) {
    obj->jsonObj = NULL;
  }
  
  round_json_object_delete(obj);
  
  return true;
}

/****************************************
 * round_json_setboolforpath
 ****************************************/

bool round_json_setboolforpath(RoundJSON *json, const char *path, bool value)
{
  RoundJSONObject *obj;
  
  obj = round_json_bool_new(value);
  if (round_json_map_setobjectforpath(json, path, obj)) {
    obj->jsonObj = NULL;
  }
  
  round_json_object_delete(obj);
  
  return true;
}

/****************************************
 * round_json_object_setobjectforpath
 ****************************************/

bool round_json_object_setobjectforpath(RoundJSONObject *parentObj, const char *pathStr, RoundJSONObject *obj)
{
  char *path, *token, *ptr;
  char **tokens;
  size_t n, tokenCnt;
  bool isAdded;
  
#if defined(ROUND_USE_JSON_PARSER_JANSSON)
  json_t *parentJson;
#endif
  
  if (!parentObj || !pathStr || !obj)
    return false;
  
#if defined(ROUND_USE_JSON_PARSER_JANSSON)
  parentJson = parentObj->jsonObj;
  if (!parentJson)
    return false;
#endif
  
  path = round_strdup(pathStr);
  if (!path)
    return false;
  
  token = round_strtok(path, ROUND_JSON_PATH_DELIM, &ptr);
  if (!token)
    return false;
  
  tokenCnt = 0;
  tokens = NULL;
  
  while (token) {
    tokenCnt++;
    tokens = (char **)realloc(tokens, (sizeof(char *) * tokenCnt));
    tokens[tokenCnt-1] = round_strdup(token);
    token = round_strtok(NULL, ROUND_JSON_PATH_DELIM, &ptr);
  }
  
  for (n=0; n<(tokenCnt-1); n++) {
#if defined(ROUND_USE_JSON_PARSER_JANSSON)
    if (round_json_ismaptoken(tokens[n])) {
      if (json_is_object(parentJson)) {
        parentJson = round_jansson_map_getobject(parentJson, tokens[n]);
        if (!parentJson) {
          json_object_set(parentJson, tokens[n], json_object());
          parentJson = round_jansson_map_getobject(parentJson, tokens[n]);
        }
      }
    }
    else if (round_json_isarraytoken(tokens[n])) {
      if (json_is_array(parentJson)) {
        parentJson = round_jansson_array_getobject(parentJson, round_str2int(tokens[n]));
        if (!parentJson) {
          json_array_set(parentJson, round_str2int(tokens[n]), json_array());
          parentJson = round_jansson_array_getobject(parentJson, round_str2int(tokens[n]));
        }
      }
      else if (json_is_object(parentJson)) {
        parentJson = round_jansson_map_getobject(parentJson, tokens[n]);
        if (!parentJson) {
          json_object_set(parentJson, tokens[n], json_object());
          parentJson = round_jansson_map_getobject(parentJson, tokens[n]);
        }
      }
    }
    if (!parentJson)
      break;
#endif
  }
  
  isAdded = false;
  
#if defined(ROUND_USE_JSON_PARSER_JANSSON)
  if (parentJson) {
    if (json_is_object(parentJson)) {
      if (round_json_ismaptoken(tokens[(tokenCnt - 1)])) {
        json_array_set(parentJson, round_str2int(tokens[n]), obj->jsonObj);
        isAdded = true;
      }
    }
    else if (json_is_array(parentJson)) {
      if (round_json_isarraytoken(tokens[(tokenCnt - 1)])) {
        json_array_set(parentJson, round_str2int(tokens[(tokenCnt - 1)]), obj->jsonObj);
        isAdded = true;
      }
    }
  }
#endif
  
  for (n=0; n<tokenCnt; n++) {
    free(tokens[n]);
  }
  
  if (tokens) {
    free(tokens);
  }
  
  return isAdded;
}

/****************************************
 * round_json_setobjectforpath
 ****************************************/

bool round_json_map_setobjectforpath(RoundJSON *json, const char *pathStr, RoundJSONObject *obj)
{
  if (!json || !pathStr || !obj)
    return false;

  if (!json->rootObj)
    return false;
  
  return round_json_object_setobjectforpath(json->rootObj, pathStr, obj);
}
