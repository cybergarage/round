/******************************************************************
 *
 * Round for C
 *
 * Copyright (C) Satoshi Konno 2015
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <stdlib.h>
#include <round/const.h>
#include <round/error_internal.h>
#include <round/method.h>

/****************************************
 * round_method_manager_new
 ****************************************/

RoundMethodManager* round_method_manager_new()
{
  RoundMethodManager* mgr;

  mgr = (RoundMethodManager*)malloc(sizeof(RoundMethodManager));
  if (!mgr)
    return NULL;

  mgr->methodMap = round_method_map_new();
  mgr->engineMap = round_script_engine_map_new();

  return mgr;
}

/****************************************
 * round_method_manager_delete
 ****************************************/

bool round_method_manager_delete(RoundMethodManager* mgr)
{
  if (!mgr)
    return false;

  round_method_map_delete(mgr->methodMap);
  round_script_engine_map_delete(mgr->engineMap);

  free(mgr);

  return true;
}

/****************************************
 * round_method_manager_delete
 ****************************************/

bool round_method_manager_addmethod(RoundMethodManager* mgr,
                                    RoundMethod* method)
{
  if (!mgr)
    return false;

  if (!round_method_isvalid(method))
    return false;

  round_method_map_remove(mgr->methodMap, round_method_getname(method));

  return round_method_map_set(mgr->methodMap, method);
}

/****************************************
 * round_method_manager_hasmethod
 ****************************************/

bool round_method_manager_hasmethod(RoundMethodManager* mgr, const char* name)
{
  return round_method_map_has(mgr->methodMap, name);
}

/****************************************
 * round_method_manager_getmethod
 ****************************************/

RoundMethod* round_method_manager_getmethod(RoundMethodManager* mgr,
                                            const char* name)
{
  if (!mgr)
    return NULL;

  return round_method_map_get(mgr->methodMap, name);
}

/****************************************
 * round_method_manager_removemethod
 ****************************************/

bool round_method_manager_removemethod(RoundMethodManager* mgr,
                                       const char* name)
{
  if (!mgr)
    return false;

  return round_method_map_remove(mgr->methodMap, name);
}

/****************************************
 * round_method_manager_addengine
 ****************************************/

bool round_method_manager_addengine(RoundMethodManager* mgr,
                                    RoundScriptEngine* engine)
{
  if (!mgr)
    return false;

  if (!round_script_engine_isvalid(engine))
    return false;

  round_script_engine_map_remove(mgr->engineMap,
                                 round_script_engine_getlanguage(engine));

  return round_script_engine_map_set(mgr->engineMap, engine);
}

/****************************************
 * round_method_manager_getengine
 ****************************************/

RoundScriptEngine* round_method_manager_getengine(RoundMethodManager* mgr,
                                                  const char* name)
{
  if (!mgr)
    return NULL;

  return round_script_engine_map_get(mgr->engineMap, name);
}

/****************************************
 * round_method_manager_removeengine
 ****************************************/

bool round_method_manager_removeengine(RoundMethodManager* mgr,
                                       const char* name)
{
  if (!mgr)
    return false;

  return round_script_engine_map_remove(mgr->engineMap, name);
}

/****************************************
 * round_method_manager_execmethod
 ****************************************/

bool round_method_manager_execmethod(RoundMethodManager* mgr, const char* name,
                                     const char* params,
                                     RoundJSONObject** result,
                                     RoundError* err)
{
  RoundMethod* method;
  RoundScriptEngine* engine;
  ROUND_SCRIPT_ENGINE_EXECFUNC execFunc;

  if (!mgr)
    return false;

  method = round_method_manager_getmethod(mgr, name);
  if (!method) {
    round_error_setjsonrpcerrorcode(err, ROUND_RPC_ERROR_CODE_METHOD_NOT_FOUND);
    return false;
  }

  engine = round_method_manager_getengine(mgr, round_method_getlanguage(method));
  if (!method) {
    round_error_setjsonrpcerrorcode(
        err, ROUND_RPC_ERROR_CODE_SCRIPT_ENGINE_NOT_FOUND);
    return false;
  }

  execFunc = round_script_engine_getexecutefunc(engine);
  if (!execFunc) {
    round_error_setjsonrpcerrorcode(
        err, ROUND_RPC_ERROR_CODE_SCRIPT_ENGINE_NOT_FOUND);
    return false;
  }

  return execFunc(engine, method, params, result, err);
}
