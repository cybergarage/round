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
 * round_trigger_manager_new
 ****************************************/

RoundTriggerManager* round_trigger_manager_new()
{
  RoundTriggerManager* mgr;

  mgr = (RoundTriggerManager*)malloc(sizeof(RoundTriggerManager));
  if (!mgr)
    return NULL;

  return mgr;
}

/****************************************
 * round_trigger_manager_delete
 ****************************************/

bool round_trigger_manager_delete(RoundTriggerManager* mgr)
{
  if (!mgr)
    return false;

  free(mgr);

  return true;
}
