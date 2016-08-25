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
#include <round/route.h>

/****************************************
 * round_trigger_manager_settrigger
 ****************************************/

bool round_trigger_manager_settrigger(RoundTriggerManager *mgr, RoundTrigger *trigger)
{
  if (!mgr || !trigger)
    return false;
  
  if (!round_trigger_hasname(trigger))
    return false;

  // Remove a duplicated trigger by the name
  const char *name = round_trigger_getname(trigger);
  if (round_trigger_manager_hastriggerbyname(mgr, name)) {
    round_trigger_manager_removetriggerbyname(mgr, name);
  }

  round_trigger_setroutemanager(trigger, round_trigger_manager_getroutemanager(mgr));
  
  return round_thread_manager_add(mgr, trigger);
}
