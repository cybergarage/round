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
#include <round/script_internal.h>

/****************************************
 * round_script_manager_new
 ****************************************/

RoundScriptManager *round_script_manager_new()
{
  RoundScriptManager *mgr;
  
  mgr = (RoundScriptManager *)malloc(sizeof(RoundScriptManager));
  if (!mgr)
    return NULL;
  
  mgr->scriptMap  = round_script_map_new();
  mgr->engineMap = round_script_engine_map_new();
  
  return mgr;  
}

/****************************************
 * round_script_manager_delete
 ****************************************/

bool round_script_manager_delete(RoundScriptManager *mgr)
{
  if (!mgr)
    return false;
  
  round_script_map_delete(mgr->scriptMap);
  round_script_engine_map_delete(mgr->engineMap);
  
  free(mgr);
  
  return true;
}

/****************************************
 * round_script_manager_delete
 ****************************************/

bool round_script_manager_addscript(RoundScriptManager *mgr, RoundScript *script)
{
  if (!mgr)
    return false;
  
  if (!round_script_isvalid(script))
    return false;
  
  round_script_map_remove(mgr->scriptMap, round_script_getname(script));

  return round_script_map_set(mgr->scriptMap, script);
}

/****************************************
 * round_script_manager_getscript
 ****************************************/

RoundScript *round_script_manager_getscript(RoundScriptManager *mgr, const char *name)
{
  if (!mgr)
    return NULL;
  
  return round_script_map_get(mgr->scriptMap, name);
}

/****************************************
 * round_script_manager_removescript
 ****************************************/

bool round_script_manager_removescript(RoundScriptManager *mgr, const char *name)
{
  if (!mgr)
    return false;
  
  return round_script_map_remove(mgr->scriptMap, name);
}

/****************************************
 * round_script_manager_addengine
 ****************************************/

bool round_script_manager_addengine(RoundScriptManager *mgr, RoundScriptEngine *engine)
{
  if (!mgr)
    return false;
  
  if (!round_script_engine_isvalid(engine))
    return false;
  
  round_script_engine_map_remove(mgr->engineMap, round_script_engine_getlanguage(engine));
  
  return round_script_engine_map_set(mgr->engineMap, engine);
}

/****************************************
 * round_script_manager_getengine
 ****************************************/

RoundScriptEngine *round_script_manager_getengine(RoundScriptManager *mgr, const char *name)
{
  if (!mgr)
    return NULL;
  
  return round_script_engine_map_get(mgr->engineMap, name);
}

/****************************************
 * round_script_manager_removeengine
 ****************************************/

bool round_script_manager_removeengine(RoundScriptManager *mgr, const char *name)
{
  if (!mgr)
    return false;
  
  return round_script_engine_map_remove(mgr->engineMap, name);
}

/****************************************
 * round_script_manager_execmethod
 ****************************************/

bool round_script_manager_execmethod(RoundScriptManager *mgr, const char *method, const char *param, RoundString *result, RoundError *err)
{
  RoundScript *script;
  RoundScriptEngine *engine;

  if (!mgr)
    return false;
  
  script = round_script_manager_getscript(mgr, method);
  if (!script) {
    round_error_setjsonrpcerrorcode(err, ROUNDC_RPC_ERROR_CODE_METHOD_NOT_FOUND);
    return false;
  }

  engine = round_script_manager_getengine(mgr, round_script_getlanguage(script));
  if (!script) {
    round_error_setjsonrpcerrorcode(err, ROUNDC_RPC_ERROR_CODE_SCRIPT_ENGINE_NOT_FOUND);
    return false;
  }
  
  /*
 }
 
 const ScriptEngine *scriptEngine = this->engines.getEngine(scriptLang);
 if (!scriptEngine) {
 RPC::JSON::ErrorCodeToError(RPC::JSON::ErrorCodeScriptEngineInternalError, error);
 return false;
 }
 
 return scriptEngine->run(script, params, results, error);
*/
 
  return false;
}
