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

/****************************************
 * round_trigger_init
 ****************************************/

bool round_trigger_init(RoundTrigger* trigger)
{
  return true;
}

/****************************************
 * round_trigger_new
 ****************************************/

RoundTrigger* round_trigger_new()
{
  RoundTrigger* trigger;

  trigger = (RoundTrigger*)malloc(sizeof(RoundTrigger));
  if (!trigger)
    return NULL;

  if (!round_trigger_init(trigger)) {
    round_trigger_delete(trigger);
    return NULL;
  }

  return trigger;
}

/****************************************
 * round_trigger_clear
 ****************************************/

bool round_trigger_clear(RoundTrigger *trigger)
{
  if (!trigger)
    return false;
  
  return true;
}

/****************************************
 * round_trigger_delete
 ****************************************/

bool round_trigger_delete(RoundTrigger* trigger)
{
  if (!trigger)
    return false;

  free(trigger);

  return true;
}
