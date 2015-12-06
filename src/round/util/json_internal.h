/******************************************************************
 *
 * Round for C
 *
 * Copyright (C) Satoshi Konno 2015
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _ROUND_UTIL_JSON_INTERNAL_H_
#define _ROUND_UTIL_JSON_INTERNAL_H_

#include <round/typedef.h>
#include <round/platform.h>
#include <round/error_internal.h>
#include <round/util/option.h>

#if defined(ROUND_USE_JSON_PARSER_JANSSON)
#include <jansson.h>
#endif

#ifdef  __cplusplus
extern "C" {
#endif

/****************************************
 * Data Type
 ****************************************/

typedef struct _RoundJSONObject {
#if defined(ROUND_USE_JSON_PARSER_JANSSON)
  json_t *jsonObj;
#endif
  struct _RoundJSONObject *childObj;
  char *dumpedStr;
} RoundJSONObject;
  
typedef struct {
  RoundJSONObject *rootObj;
  RoundJSONObject *pathObj;
  RoundOption opt;
} RoundJSON;

/****************************************
 * Public Header
 ****************************************/

#include <round/util/json.h>

/****************************************
 * Function
 ****************************************/

#define round_json_setrootobject(json, obj) (json->rootObj = obj)

#if defined(ROUND_USE_JSON_PARSER_JANSSON)
#define round_json_object_setjanssonobject(obj, value) (obj->jsonObj = value)
#endif

#if defined(ROUND_USE_JSON_PARSER_JANSSON)
json_t *round_jansson_map_getobject(json_t *jsonMap, const char *name);
json_t *round_jansson_array_getobject(json_t *jsonArray, size_t n);
#endif

/****************************************
 * Functions (JSON Path)
 ****************************************/

#define round_json_ismaptoken(token) (!round_isnumeric(token))
#define round_json_isarraytoken(token) round_isnumeric(token)

bool round_json_object_getobjectforpath(RoundJSONObject *rootObj, const char *pathStr, RoundJSONObject *retObj);

bool round_json_object_setobjectforpath(RoundJSONObject *parentObj, const char *pathStr, RoundJSONObject *obj);
bool round_json_map_setobjectforpath(RoundJSON *json, const char *pathStr, RoundJSONObject *obj);

#ifdef  __cplusplus
} /* extern "C" */
#endif

#endif
