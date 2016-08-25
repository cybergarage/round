/******************************************************************
 *
 * Round for C
 *
 * Copyright (C) Satoshi Konno 2015
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <round/trigger.h>
#include <round/route.h>

/****************************************
 * round_trigger_action
 ****************************************/

void round_trigger_action(RoundTrigger *trigger)
{
  if (!trigger)
    return;
  
  RoundRouteManager *mgr = round_trigger_manager_getroutemanager(trigger);
  if (!mgr)
    return;
}

/****************************************
 * round_trigger_new
 ****************************************/

RoundTrigger *round_trigger_new(void)
{
  RoundTrigger *trigger = round_thread_new();
  if (!trigger)
    return NULL;
  
  round_thread_setaction(trigger, round_trigger_action);
  
  return trigger;
}
