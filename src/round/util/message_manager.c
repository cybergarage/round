/******************************************************************
 *
 * Round for C
 *
 * Copyright (C) Satoshi Konno 2015
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <round/util/message.h>

/****************************************
* round_message_manager_new
****************************************/

RoundMessageManager *round_message_manager_new(void)
{
  RoundMessageManager *mgr;

  mgr = (RoundMessageManager *)malloc(sizeof(RoundMessageManager));

  if (!mgr)
    return NULL;

  mgr->queue = round_message_queue_new();
  
  return mgr;
}

/****************************************
* round_message_manager_delete
****************************************/

bool round_message_manager_delete(RoundMessageManager *mgr)
{
  if (!mgr)
    return false;
  
  round_message_manager_clear(mgr);

  round_message_queue_delete(mgr->queue);
  
  free(mgr);
  
  return true;
}

/****************************************
 * round_message_manager_delete
 ****************************************/

bool round_message_manager_clear(RoundMessageManager *mgr)
{
  if (!mgr)
    return false;

  round_message_queue_clear(mgr->queue);
  
  return true;
}
