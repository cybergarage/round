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
#include <round/trigger.h>

/****************************************
 * round_trigger_manager_init
 ****************************************/

bool round_trigger_manager_init(RoundTriggerManager* mgr)
{
  mgr->triggerMap = round_map_new();
  if (!mgr->triggerMap)
    return false;
  
  return true;
}

/****************************************
 * round_trigger_manager_new
 ****************************************/

RoundTriggerManager* round_trigger_manager_new()
{
  RoundTriggerManager* mgr;

  mgr = (RoundTriggerManager*)malloc(sizeof(RoundTriggerManager));
  if (!mgr)
    return NULL;

  if (!round_trigger_manager_init(mgr)) {
    round_trigger_manager_delete(mgr);
    return NULL;
  }
  
  return mgr;
}

/****************************************
 * round_trigger_manager_delete
 ****************************************/

bool round_trigger_manager_delete(RoundTriggerManager* mgr)
{
  if (!mgr)
    return false;

  round_map_delete(mgr->triggerMap);

  free(mgr);

  return true;
}

/****************************************
 * round_trigger_manager_settrigger
 ****************************************/

bool round_trigger_manager_settrigger(RoundTriggerManager *mgr, RoundTrigger *trigger)
{
  if (!mgr || !trigger)
    return false;
  
  if (!round_trigger_hasname(trigger))
    return false;

  const char *name = round_trigger_getname(trigger);
  if (round_trigger_manager_hastriggerbyname(mgr, name)) {
    RoundTrigger *oldTrigger = round_trigger_manager_gettriggerbyname(mgr, name);
    round_map_removeobjectbykey(mgr->triggerMap, name);
    if (oldTrigger) {
      round_trigger_delete(oldTrigger);
    }
  }

  return round_map_setobject(mgr->triggerMap, round_trigger_getname(trigger), trigger);
}
