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

  tokenJson = rootJson;
  while (token) {
    token = round_strtok(NULL, ROUND_JSON_PATH_DELIM, &ptr);
  }
#endif

  return json->pathObj;
}
