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
  
  mgr->scripts = round_scriptlist_new();
  mgr->engines = round_script_enginelist_new();
  
  return mgr;  
}

/****************************************
 * round_script_manager_delete
 ****************************************/

bool round_script_manager_delete(RoundScriptManager *mgr)
{
  if (!mgr)
    return false;
  
  round_scriptlist_delete(mgr->scripts);
  round_script_enginelist_delete(mgr->engines);
  
  free(mgr);
  
  return true;
}

/****************************************
 * round_script_manager_delete
 ****************************************/

bool round_script_manager_addscript(RoundScriptManager *mgr, RoundScript *script)
{
  RoundScript *oldScript;
  
  if (!mgr)
    return false;
  
  if (!round_script_isvalid(script))
    return false;

  oldScript = round_script_manager_getscriptbyname(mgr, round_script_getname(script));
  if (oldScript) {
    round_script_remove(oldScript);
  }

  return round_scriptlist_add(mgr->scripts, script);
}

/****************************************
 * round_script_manager_getscriptbyname
 ****************************************/

RoundScript *round_script_manager_getscriptbyname(RoundScriptManager *mgr, const char *name)
{
  RoundScript *script;
  
  if (!mgr)
    return NULL;
  
  for (script = round_scriptlist_gets(mgr->scripts); script; script = round_script_next(script)) {
  
  }
  
  return NULL;
}
