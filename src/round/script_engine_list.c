/******************************************************************
 *
 * Round for C
 *
 * Copyright (C) Satoshi Konno 2015
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <round/script_internal.h>

/****************************************
* round_script_enginelist_new
****************************************/

RoundScriptEngineList *round_script_enginelist_new(void)
{
  RoundScriptEngineList *scriptses;

  scriptses = (RoundScriptEngineList *)malloc(sizeof(RoundScriptEngineList));
  if (!scriptses)
    return NULL;

  round_list_header_init((RoundList *)scriptses);

  return scriptses;
}

/****************************************
* round_script_enginelist_delete
****************************************/

bool round_script_enginelist_delete(RoundScriptEngineList *scriptses)
{
  if (!scriptses)
    return false;
  
  round_script_enginelist_clear(scriptses);

  free(scriptses);

  return true;
}
