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
 * round_script_manager_getscriptbyname
 ****************************************/

RoundScript *round_script_manager_getscriptbyname(RoundScriptManager *mgr, const char *name)
{
  if (!mgr)
    return NULL;
  
  return round_script_map_get(mgr->scriptMap, name);
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
 * round_script_manager_getenginebyname
 ****************************************/

RoundScriptEngine *round_script_manager_getenginebyname(RoundScriptManager *mgr, const char *name)
{
  if (!mgr)
    return NULL;
  
  return round_script_engine_map_get(mgr->engineMap, name);
}
