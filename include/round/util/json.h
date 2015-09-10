/******************************************************************
 *
 * Round for C
 *
 * Copyright (C) Satoshi Konno 2015
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _ROUNDC_UTIL_JSON_H_
#define _ROUNDC_UTIL_JSON_H_

#include <round/typedef.h>
#include <round/error.h>

#if defined(ROUND_USE_JSON_PARSER_JANSSON)
#include <jansson.h>
#endif

#ifdef  __cplusplus
extern "C" {
#endif

/****************************************
 * Constant
 ****************************************/

enum {
ROUND_JSON_UNKOWN = 0,
ROUND_JSON_MAP,
ROUND_JSON_ARRAY,
ROUND_JSON_NULL,
ROUND_JSON_STRING,
ROUND_JSON_INTEGER,
ROUND_JSON_REAL,
ROUND_JSON_TRUE,
ROUND_JSON_FALSE,
ROUND_JSON_BOOL,
};
  
#define ROUND_JSON_PATH_DELIM "/"

/****************************************
 * Data Type
 ****************************************/

#if !defined(_ROUNDC_UTIL_JSON_INTERNAL_H_)
typedef void RoundJSONObject;
typedef void RoundJSON;
#endif
  
/****************************************
 * Functions (JSON)
 ****************************************/

RoundJSON *round_json_new(void);
bool round_json_parse(RoundJSON *json, const char *jsonStr, RoundError *err);
bool round_json_clear(RoundJSON *json);
bool round_json_delete(RoundJSON *json);

RoundJSONObject *round_json_getrootobject(RoundJSON *json);
RoundJSONObject *round_json_getobjectforpath(RoundJSON *json, const char *path);

bool round_json_getstringforpath(RoundJSON *json, const char *path, const char **value);
bool round_json_getintforpath(RoundJSON *json, const char *path, int *value);
bool round_json_getrealforpath(RoundJSON *json, const char *path, double *value);
bool round_json_getboolforpath(RoundJSON *json, const char *path, bool *value);

/****************************************
 * Functions (JSON Object)
 ****************************************/

RoundJSONObject *round_json_object_new(void);
bool round_json_object_delete(RoundJSONObject *obj);

int round_json_object_gettype(RoundJSONObject *obj);
bool round_json_object_istype(RoundJSONObject *obj, int type);

#define round_json_object_ismap(obj) round_json_object_istype(obj, ROUND_JSON_MAP)
#define round_json_object_isarray(obj) round_json_object_istype(obj, ROUND_JSON_ARRAY)
#define round_json_object_isstring(obj) round_json_object_istype(obj, ROUND_JSON_STRING)
#define round_json_object_isinteger(obj) round_json_object_istype(obj, ROUND_JSON_INTEGER)
#define round_json_object_isreal(obj) round_json_object_istype(obj, ROUND_JSON_REAL)
#define round_json_object_isbool(obj) round_json_object_istype(obj, ROUND_JSON_BOOL)

bool round_json_object_getstring(RoundJSONObject *obj, const char **value);
bool round_json_object_getinteger(RoundJSONObject *obj, int *value);
bool round_json_object_getreal(RoundJSONObject *obj, double *value);
bool round_json_object_getbool(RoundJSONObject *obj, bool *value);
  
#ifdef  __cplusplus
} /* extern "C" */
#endif

#endif
