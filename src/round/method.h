/******************************************************************
 *
 * Round for C
 *
 * Copyright (C) Satoshi Konno 2015
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _ROUND_METHOD_INTERNAL_H_
#define _ROUND_METHOD_INTERNAL_H_

#ifdef HAVE_CONFIG_H
#  include "config.h"
#endif

#include <round/typedef.h>
#include <round/const.h>
#include <round/util/mutex.h>
#include <round/util/map.h>
#include <round/util/option.h>
#include <round/method.h>
#include <round/script_internal.h>
#include <round/util/json_internal.h>

#ifdef  __cplusplus
extern "C" {
#endif

/****************************************
 * Constants
 ****************************************/

enum {
RoundMethodFinal = 0x01,
RoundMethodStatic = 0x02,
};

/****************************************
 * Data Type
 ****************************************/

typedef struct {
  char *module;
  char *name;
  char *lang;
  byte *code;
  size_t codeSize;
  RoundOption opt;
  void *userData;
} RoundMethod;
  
typedef struct {
  RoundMutex *mutex;
  RoundMap *methodMap;
  RoundMap *engineMap;
} RoundMethodManager;

/****************************************
 * Function (Method)
 ****************************************/
  
RoundMethod *round_method_new();
bool round_method_delete(RoundMethod *method);
  
bool round_method_setmodule(RoundMethod *method, const char *module);
#define round_method_getmodule(method) (method->module)

bool round_method_setname(RoundMethod *method, const char *name);
#define round_method_getname(method) (method->name)

bool round_method_setlanguage(RoundMethod *method, const char *lang);
#define round_method_getlanguage(method) (method->lang)

bool round_method_setcode(RoundMethod *method, byte *code, size_t codeLen);
bool round_method_setstringcode(RoundMethod *method, const char *code);
#define round_method_getcode(method) (method->code)
#define round_method_getstringcode(method) ((const char *)method->code)
#define round_method_getcodesize(method) (method->codeSize)

#define round_method_setoption(method, value) round_option_set(method->opt, value)
#define round_method_getoption(method) round_option_get(method->opt)
#define round_method_setflag(method, flag, value) round_option_setflag(method->opt, flag, value)
#define round_method_isenabled(method, flag) round_option_isenabled(method->opt, flag)
#define round_method_isdisabled(method, flag) round_option_isdisabled(method->opt, flag)
  
#define round_method_setfinal(method, value) round_method_setflag(method, RoundMethodFinal, value)
#define round_method_isfinal(method) round_method_isenabled(method, RoundMethodFinal)

#define round_method_setstatic(method, value) round_method_setflag(method, RoundMethodStatic, value)
#define round_method_isstatic(method) round_method_isenabled(method, RoundMethodStatic)
#define round_method_isdynamic(method) round_method_isdisabled(method, RoundMethodStatic)
  
#define round_method_setuserdata(method, value) (method->userData = (void *)value)
#define round_method_getuserdata(method) (method->userData)

bool round_method_isvalid(RoundMethod *method);
  
/****************************************
 * Function (Method Map)
 ****************************************/
  
RoundMap *round_method_map_new();
  
#define round_method_map_delete(map) round_map_delete(map)
#define round_method_map_size(map) round_map_size(map)
#define round_method_map_set(map, method) round_map_setobject(map, method->name, method)
#define round_method_map_has(map, name) ((RoundMethod*)round_map_haskey(map, name))
#define round_method_map_get(map, name) ((RoundMethod*)round_map_getobjectbykey(map, name))
#define round_method_map_remove(map, name) round_map_removeobjectbykey(map, name)

/****************************************
 * Function (Method Manager)
 ****************************************/
  
RoundMethodManager *round_method_manager_new();
bool round_method_manager_delete(RoundMethodManager *mgr);

bool round_method_manager_addmethod(RoundMethodManager *mgr, RoundMethod *method);
bool round_method_manager_hasmethod(RoundMethodManager *mgr, const char *name);
RoundMethod *round_method_manager_getmethod(RoundMethodManager *mgr, const char *name);
bool round_method_manager_removemethod(RoundMethodManager *mgr, const char *name);
#define round_method_manager_getmethodsize(mgr) round_map_size(mgr->methodMap)

bool round_method_manager_addengine(RoundMethodManager *mgr, RoundScriptEngine *engine);
RoundScriptEngine *round_method_manager_getengine(RoundMethodManager *mgr, const char *name);
bool round_method_manager_removeengine(RoundMethodManager *mgr, const char *name);
#define round_method_manager_getenginsize(mgr) round_map_size(mgr->engineMap)
  
bool round_method_manager_execmethod(RoundMethodManager *mgr, const char *name, const char *params, RoundJSONObject **result, RoundError *err);

#ifdef  __cplusplus
}
#endif

#endif
