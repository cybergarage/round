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
* round_scriptlist_new
****************************************/

RoundScriptList *round_scriptlist_new(void)
{
  RoundScriptList *scriptses;

  scriptses = (RoundScriptList *)malloc(sizeof(RoundScriptList));
  if (!scriptses)
    return NULL;

  round_list_header_init((RoundList *)scriptses);

  return scriptses;
}

/****************************************
* round_scriptlist_delete
****************************************/

bool round_scriptlist_delete(RoundScriptList *scriptses)
{
  if (!scriptses)
    return false;
  
  round_scriptlist_clear(scriptses);

  free(scriptses);

  return true;
}
