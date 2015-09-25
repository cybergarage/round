/******************************************************************
 *
 * Round for C
 *
 * Copyright (C) Satoshi Konno 2015
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _ROUNDC_UTIL_JSON_INTERNAL_H_
#define _ROUNDC_UTIL_JSON_INTERNAL_H_

#include <round/typedef.h>
#include <round/platform.h>
#include <round/error_internal.h>

#if defined(ROUND_USE_JSON_PARSER_JANSSON)
#include <jansson.h>
#endif

#ifdef  __cplusplus
extern "C" {
#endif

/****************************************
 * Data Type
 ****************************************/

typedef struct {
#if defined(ROUND_USE_JSON_PARSER_JANSSON)
  json_t *jsonObj;
#endif
} RoundJSONObject;
  
typedef struct {
  RoundJSONObject *rootObj;
  RoundJSONObject *pathObj;
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

RoundJSONObject *round_json_map_new(void);
RoundJSONObject *round_json_array_new(void);
RoundJSONObject *round_json_string_new(const char *value);
RoundJSONObject *round_json_integer_new(int value);
RoundJSONObject *round_json_real_new(double value);
RoundJSONObject *round_json_bool_new(bool value);

#if defined(ROUND_USE_JSON_PARSER_JANSSON)
json_t *round_jansson_map_getobject(json_t *jsonMap, const char *name);
json_t *round_jansson_array_getobject(json_t *jsonArray, size_t n);
#endif
  
/****************************************
 * Functions (JSON Path)
 ****************************************/

#define round_json_ismaptoken(token) (!round_isnumeric(token))
#define round_json_isarraytoken(token) round_isnumeric(token)
  
bool round_json_map_setobjectforpath(RoundJSON *json, const char *path, const char *key, RoundJSONObject *obj);

#ifdef  __cplusplus
} /* extern "C" */
#endif

#endif
