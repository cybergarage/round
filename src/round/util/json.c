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
 * round_json_getrootobject
 ****************************************/

RoundJSONObject *round_json_getrootobject(RoundJSON *json)
{
  if (!json)
    return NULL;
  
  return json->rootObj;
}

/****************************************
 * round_json_poprootobject
 ****************************************/

RoundJSONObject *round_json_poprootobject(RoundJSON *json)
{
  RoundJSONObject *rootObj;
  
  if (!json)
    return NULL;
  
  rootObj = json->rootObj;
  json->rootObj = NULL;
  
  return rootObj;
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
    if (err) {
      round_error_setcode(err, jsonErr.line);
      snprintf(errMsg, sizeof(errMsg), "Error : Line %d , Pos %d, %s", jsonErr.line, jsonErr.position, jsonErr.text);
      round_error_setmessage(err, errMsg);
    }
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
  
  return true;
}
