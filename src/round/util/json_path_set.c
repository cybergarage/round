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
  return false;
}

/****************************************
 * round_json_setintforpath
 ****************************************/

bool round_json_setintforpath(RoundJSON *json, const char *path, int value)
{
  return false;
}

/****************************************
 * round_json_setrealforpath
 ****************************************/

bool round_json_setrealforpath(RoundJSON *json, const char *path, double value)
{
  return false;
}

/****************************************
 * round_json_setboolforpath
 ****************************************/

bool round_json_setboolforpath(RoundJSON *json, const char *path, bool value)
{
  return false;
}

/****************************************
 * round_json_setobjectforpath
 ****************************************/

bool round_json_map_setobjectforpath(RoundJSON *json, const char *pathStr, const char *key, RoundJSONObject *obj)
{
  char *path, *token, *ptr;
  char **tokens;
  size_t n, tokenCnt;
  bool isAdded;
  
#if defined(ROUND_USE_JSON_PARSER_JANSSON)
  json_t *rootJson, *parentJson;
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

  tokenCnt = 0;
  tokens = NULL;

  while (token) {
    tokenCnt++;
    tokens = (char **)realloc(tokens, (sizeof(char *) * tokenCnt));
    tokens[tokenCnt-1] = round_strdup(token);
    token = round_strtok(NULL, ROUND_JSON_PATH_DELIM, &ptr);
  }

#if defined(ROUND_USE_JSON_PARSER_JANSSON)
  parentJson = rootJson;
#endif
  
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
#endif
    
    if (!parentJson)
      return false;
  }
  
  isAdded = false;
  
#if defined(ROUND_USE_JSON_PARSER_JANSSON)
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
#endif
  
  for (n=0; n<tokenCnt; n++) {
    free(tokens[n]);
  }

  if (tokens) {
    free(tokens);
  }

  return isAdded;
}
