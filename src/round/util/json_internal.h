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

#if defined(HAVE_LIBJANSSON)
#define ROUND_USE_JSON_PARSER_JANSSON 1
#endif

#if defined(ROUND_USE_JSON_PARSER_JANSSON)
#include <jansson.h>
#if !defined(json_boolean_value)
#define json_boolean_value(obj) json_is_true(obj) ? true : false
#endif
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
  char *cachedStr;
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

bool round_json_object_init(RoundJSONObject* obj);
bool round_json_object_initchildobject(RoundJSONObject* obj);

#define round_json_setrootobject(json, obj) (json->rootObj = obj)

#if defined(ROUND_USE_JSON_PARSER_JANSSON)
#define round_json_object_setjanssonobject(obj, value) (obj->jsonObj = value)
#endif

#if defined(ROUND_USE_JSON_PARSER_JANSSON)
json_t *round_jansson_map_getobject(json_t *jsonMap, const char *name);
json_t *round_jansson_array_getobject(json_t *jsonArray, size_t n);
#endif

bool round_json_object_clearcaches(RoundJSONObject *obj);

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
