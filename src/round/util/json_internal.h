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
